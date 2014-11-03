#include "interp.h"

#include <vector>
#include <iostream>
#include <string>

#include <cstdlib>
#include <cmath>
#include <limits>

#include "libqhull/qset.h"
#include "libqhull/libqhull.h"

#define NPY_MAXDIMS 32
#define NPY_MAXDIMS_PLUS1 33
#define NPY_MAXDIMS_MULT4 128

const double eps = 2.2204460492503131e-14;
const double eps_broad = 1.4901161193847656e-08;

#ifdef __cplusplus // import fortran subroutines
extern "C" {
    void dgecon_(char*, int*, double*, int*, double*, double*, double*, int*, int*);
    void dgetrf_(int*, int*, double*, int*, int*, int*);
    void dgetrs_(char*, int*, int*, double*, int*, int*, double*, int*, int*);
}
#endif
/*
struct Vector2 {
    double x, y;
};

void error(const std::string& message) {
    std::cerr << "ERROR: " << message << std::endl;
    exit(1);
}
*/
class Qhull {
    const std::vector<Vector2>& points;
    int ndim, numpoints;

public:
    Qhull(const std::vector<Vector2>& _points):
            points(_points) {
        numpoints = _points.size();
        ndim = 2;

        char* options = (char*)"qhull d Qbb Qc Qz Qt";

        int exitcode = qh_new_qhull(ndim, numpoints, (double*)(&_points[0]),
            0, options, NULL, stderr);

        if (exitcode != 0) error("qh_new_qhull failed");
    }

    ~Qhull() {
        qh_freeqhull(qh_ALL);
    }

    void triangulate() {
        qh_triangulate();
    }

    double get_paraboloid_scale() {
        double scale = 1.0;

        if (qh_qh.SCALElast) {
            scale = qh_qh.last_newhigh / (qh_qh.last_high - qh_qh.last_low);
        }

        return scale;
    }

    double get_paraboloid_shift() {
        double shift = 0.0;

        if (qh_qh.SCALElast) {
            shift = qh_qh.last_newhigh / (qh_qh.last_high - qh_qh.last_low);
            shift *= -qh_qh.last_low;
        }

        return shift;
    }

    void get_simplex_facet_array(std::vector<int>& facets,
            std::vector<int>& neighbors,
            std::vector<int>& coplanar,
            std::vector<double>& equations) {

        int facet_ndim = ndim + 1;
        std::vector<int> id_map(qh_qh.facet_id, -1); // correct size?

        facetT* facet = qh_qh.facet_list;
        int j = 0;

        while (facet && facet->next) {
            if (facet->upperdelaunay == qh_qh.UPPERdelaunay) {
                if ( !(facet->simplicial) ) {
                    int test = 0;

                    if (qh_setsize(facet->vertices) != facet_ndim) test = 1;
                    if (qh_setsize(facet->neighbors) != facet_ndim) test = 1;

                    if (test) error("non-simplicial facet encountered");
                }

                id_map[facet->id] = j;
                j += 1;
            }

            facet= facet->next;
        }

        facets.clear();
        facets.resize( (j) * (facet_ndim), 0 );

        neighbors.clear();
        neighbors.resize( (j) * (facet_ndim), 0 );

        equations.clear();
        equations.resize( (j) * (facet_ndim+1), 0.0 );

        int ncoplanar = 0;

        coplanar.clear();
        coplanar.resize( (10) * (3), 0 );

        facet = qh_qh.facet_list;
        j = 0;

        while (facet && facet->next) {
            if (facet->upperdelaunay != qh_qh.UPPERdelaunay) {
                facet = facet->next;
                continue;
            }

            unsigned lower_bound = 0;
            vertexT* vertex;
            facetT* neighbor;
            pointT* point;
            int ipoint;
            double dist;

            if (facet->toporient == qh_ORIENTclock && facet_ndim == 3) {
                for (int i = 0; i < 2; i++) {
                    int swapped_index = 1 ^ i;
                    vertex = (vertexT*)facet->vertices->e[i].p;
                    ipoint = qh_pointid(vertex->point);
                    facets[j * (facet_ndim) + swapped_index] = ipoint;

                    neighbor = (facetT*)facet->neighbors->e[i].p;
                    neighbors[j * (facet_ndim) + swapped_index] = id_map[neighbor->id];
                }

                lower_bound = 2;
            }

            for (int i = lower_bound; i < facet_ndim; i++) {
                vertex = (vertexT*)facet->vertices->e[i].p;
                ipoint = qh_pointid(vertex->point);
                facets[j * (facet_ndim) + i] = ipoint;

                neighbor = (facetT*)facet->neighbors->e[i].p;
                neighbors[j * (facet_ndim) + i] = id_map[neighbor->id];
            }

            for (int i = 0; i < facet_ndim; i++) {
                equations[j * (facet_ndim+1) + i] = facet->normal[i];
            }
            equations[j * (facet_ndim+1) + facet_ndim] = facet->offset;

            if (facet->coplanarset) {
                for (int i = 0; i < qh_setsize(facet->coplanarset); i++) {
                    point = (pointT*)facet->coplanarset->e[i].p;
                    vertex = qh_nearvertex(facet, point, &dist);

                    if (ncoplanar >= coplanar.size()) {
                        coplanar.resize( (2 * ncoplanar + 1) * (3), 0 );
                    }

                    coplanar[ncoplanar * (3) + 0] = qh_pointid(point);
                    coplanar[ncoplanar * (3) + 1] = id_map[facet->id];
                    coplanar[ncoplanar * (3) + 2] = qh_pointid(vertex->point);
                    ncoplanar += 1;
                }
            }

            j += 1;
            facet = facet->next;
        }

    coplanar.resize( (ncoplanar) * (3) );
    }
};

class Delaunay {
    Qhull qhull;
    const std::vector<Vector2>& points;
    double paraboloid_scale, paraboloid_shift;
    std::vector<int> simplices, neighbors, coplanar;
    std::vector<double> equations, transform;
    int ndim, npoints, nsimplex;
    Vector2 min_bound, max_bound;

    void _get_barycentric_transforms() {
        double nan = std::numeric_limits<double>::quiet_NaN();
        double rcond_limit = 1000.0 * eps;

        int ipiv[NPY_MAXDIMS_PLUS1];
        int iwork[NPY_MAXDIMS];
        double work[NPY_MAXDIMS_MULT4];

        std::vector<double> T( (ndim) * (ndim), 0.0 );

        transform.clear();
        transform.resize( (nsimplex) * (ndim+1) * (ndim), 0.0 );

        for (int isimplex = 0; isimplex < nsimplex; isimplex++) {
            transform[isimplex*(ndim+1)*(ndim) + ndim*(ndim) + 0]
                = points[simplices[isimplex*(ndim+1) + ndim]].x;
            T[0 * (ndim) + 0] = (points[simplices[isimplex*(ndim+1) + 0]].x
                - transform[isimplex*(ndim+1)*(ndim) + ndim*(ndim) + 0]);
            T[0 * (ndim) + 1] = (points[simplices[isimplex*(ndim+1) + 1]].x
                - transform[isimplex*(ndim+1)*(ndim) + ndim*(ndim) + 0]);
            transform[isimplex*(ndim+1)*(ndim) + 0*(ndim) + 0] = 1.0;

            transform[isimplex*(ndim+1)*(ndim) + ndim*(ndim) + 1]
                = points[simplices[isimplex*(ndim+1) + ndim]].y;
            T[1 * (ndim) + 0] = (points[simplices[isimplex*(ndim+1) + 0]].y
                - transform[isimplex*(ndim+1)*(ndim) + ndim*(ndim) + 1]);
            T[1 * (ndim) + 1] = (points[simplices[isimplex*(ndim+1) + 1]].y
                - transform[isimplex*(ndim+1)*(ndim) + ndim*(ndim) + 1]);
            transform[isimplex*(ndim+1)*(ndim) + 1*(ndim) + 1] = 1.0;

            double A1 = fabs(T[0*(ndim) + 0]) + fabs(T[0*(ndim) + 1]); // may need to be transposed
            double A2 = fabs(T[1*(ndim) + 0]) + fabs(T[1*(ndim) + 1]);
            double anorm = A1 > A2 ? A1 : A2;

            double rcond;

            int n, nrhs, lda, ldb, info;
            n = nrhs = lda = ldb = ndim;
            dgetrf_(&n, &n, &T[0], &lda, ipiv, &info);

            if (info == 0) {
                dgecon_("1", &n, &T[0], &lda, &anorm, &rcond, work, iwork, &info);
                if (rcond < rcond_limit) info = 1;
            }

            if (info == 0) {
                dgetrs_("N", &n, &nrhs, &T[0], &lda, ipiv,
                   &transform[0] + ndim*(ndim+1)*isimplex, &ldb, &info);
            }

            if (info != 0) {
                for (int i = 0; i < ndim+1; i++) {
                    for (int j = 0; j < ndim; j++) {
                        transform[isimplex*(ndim+1)*(ndim) + i*(ndim) + j] = nan;
                    }
                }
            }
        }
    }

    int _barycentric_inside(double* transformAddr, const Vector2& point, double* c) {
        c[ndim] = 1.0;

        for (int i = 0; i < ndim; i++) {
            c[i] = 0.0;
            c[i] += transformAddr[ndim*i + 0] * (point.x - transformAddr[ndim*ndim + 0]);
            c[i] += transformAddr[ndim*i + 1] * (point.y - transformAddr[ndim*ndim + 1]);
            c[ndim] -= c[i];

            if (-eps > c[i] || c[i] > 1.0 + eps) return 0;
        }

        if (-eps > c[ndim] || c[ndim] > 1.0 + eps) return 0;
        return 1;
    }

    void _barycentric_coordinate_single(double* transformAddr, const Vector2& point, double* c, int i) {
        if (i == ndim) {
            c[ndim] = 1.0;
            for (int j = 0; j < ndim; j++) c[ndim] -= c[j];
        } else {
            c[i] = 0.0;
            c[i] += transformAddr[ndim*i + 0] * (point.x - transformAddr[ndim*ndim + 0]);
            c[i] += transformAddr[ndim*i + 1] * (point.y - transformAddr[ndim*ndim + 1]);
        }
    }

    void _barycentric_coordinates(double* transformAddr, const Vector2& point, double* c) {
        c[ndim] = 1.0;
        for (int i = 0; i < ndim; i++) {
            c[i] = 0.0;
            c[i] += transformAddr[ndim*i + 0] * (point.x - transform[ndim*ndim + 0]);
            c[i] += transformAddr[ndim*i + 1] * (point.y - transform[ndim*ndim + 1]);
            c[ndim] -= c[i];
        }
    }

    void _lift_point(const Vector2& point, double* z) {
        z[ndim] = 0.0;

        z[0] = point.x;
        z[ndim] += point.x * point.x;

        z[1] = point.y;
        z[ndim] += point.y * point.y;

        z[ndim] *= paraboloid_scale;
        z[ndim] += paraboloid_shift;
    }

    double _distplane(int isimplex, double* point) {
        double dist = equations[isimplex * (ndim+2) + ndim+1];

        for (int k = 0; k < ndim+2; k++) {
            dist += equations[isimplex * (ndim+2) + k] * point[k];
        }

        return dist;
    }

    int _is_point_fully_outside(const Vector2& point) {
        if (point.x < min_bound.x - eps || point.x > max_bound.x + eps) return 1;
        if (point.y < min_bound.y - eps || point.y > max_bound.y + eps) return 1;
        return 0;
    }

    int _find_simplex_bruteforce(double* c, const Vector2& point) {
        double* transformAddr;
        int inside;

        if (_is_point_fully_outside(point)) return -1;

        for (int isimplex = 0; isimplex < nsimplex; isimplex++) {
            transformAddr = &transform[0] + isimplex*(ndim)*(ndim+1);

            if (transformAddr[0] == transformAddr[0]) { // is not nan
                inside = _barycentric_inside(transformAddr, point, c);
                if (inside) return isimplex;
            } else {
                for (int k = 0; k < ndim+1; k++) {
                    int ineighbor = neighbors[(ndim+1)*isimplex + k];
                    if (ineighbor == -1) continue;

                    transformAddr = &transform[0] + ineighbor*ndim*(ndim+1);
                    if (transformAddr[0] == transformAddr[0]) continue;

                    _barycentric_coordinates(transformAddr, point, c);
                    inside = 1;

                    for (int m = 0; m < ndim+1; m++) {
                        if (neighbors[(ndim+1)*ineighbor + m] == isimplex) {
                            if (-eps_broad > c[m] || c[m] > 1.0 + eps) {
                                inside = 0;
                                break;
                            }
                        } else {
                            if (-eps > c[m] || c[m] > 1.0 + eps) {
                                inside = 0;
                                break;
                            }
                        }
                    }

                    if (inside) return ineighbor;
                }
            }
        }

        return -1;
    }

    int _find_simplex_directed(double* c, const Vector2& point, int* start) {
        double* transformAddr;

        int isimplex = start[0];
        if (isimplex < 0 || isimplex >= nsimplex) isimplex = 0;

        for (int cycle_k = 0; cycle_k < 1+nsimplex/4; cycle_k++) {
            if (isimplex == -1) break;

            transformAddr = &transform[0] + isimplex*ndim*(ndim+1);

            int inside = 1;
            for (int k = 0; k < ndim+1; k++) {
                _barycentric_coordinate_single(transformAddr, point, c, k);

                if (c[k] < -eps) {
                    int m = neighbors[(ndim+1)*isimplex + k];
                    if (m == -1) {
                        start[0] = isimplex;
                        return -1;
                    }

                    isimplex = m;
                    inside = -1;
                    break;
                } else if (c[k] <= 1.0 + eps) {
                    ;
                } else inside = 0;
            }

            if (inside == -1) continue;
            else if (inside == 1) break;
            else {
                isimplex = _find_simplex_bruteforce(c, point);
                break;
            }
        }
        // else bruteforce?

        start[0] = isimplex;
        return isimplex;
    }

public:
    Delaunay(const std::vector<Vector2>& _points):
            points(_points), qhull(_points) {
        update();
    }

    void update() {
        qhull.triangulate();

        paraboloid_scale = qhull.get_paraboloid_scale();
        paraboloid_shift = qhull.get_paraboloid_shift();

        qhull.get_simplex_facet_array(simplices, neighbors, coplanar, equations);

        ndim = 2;
        npoints = points.size();
        nsimplex = simplices.size() / (ndim+1);

        _get_barycentric_transforms();

        min_bound.x = max_bound.x = points[0].x;
        min_bound.y = max_bound.y = points[0].y;

        for (int i = 1; i < npoints; i++) {
            if (min_bound.x > points[i].x) min_bound.x = points[i].x;
            if (max_bound.x < points[i].x) max_bound.x = points[i].x;
            if (min_bound.y > points[i].y) min_bound.y = points[i].y;
            if (max_bound.y < points[i].y) max_bound.y = points[i].y;
        }
    }

    int _find_simplex(double* c, const Vector2& point, int* start) {
        if (_is_point_fully_outside(point)) return -1;
        if (nsimplex <= 0) return -1;

        double z[NPY_MAXDIMS_PLUS1];

        int isimplex = start[0];
        if (isimplex < 0 || isimplex >= nsimplex) isimplex = 0;

        _lift_point(point, z);
        double best_dist = _distplane(isimplex, z);
        int changed = 1;

        while (changed) {
            if (best_dist > 0.0) break;

            changed = 0;
            for (int k = 0; k < ndim+1; k++) {
                int ineigh = neighbors[(ndim+1)*isimplex + k];
                if (ineigh == -1) continue;

                double dist = _distplane(ineigh, z);
                if (dist > best_dist + eps * (1.0 + fabs(best_dist))) {
                    isimplex = ineigh;
                    best_dist = dist;
                    changed = 1;
                }
            }
        }

        start[0] = isimplex;
        return _find_simplex_directed(c, point, start);
    }

    const std::vector<int>& get_simplices() const {
        return simplices;
    }
};

LinearNDInterpolator::LinearNDInterpolator(const std::vector<Vector2>& _points,
        const std::vector<double>& _values, double _fill_value):
        points(_points), values(_values) {
    tri = new Delaunay(_points);
    fill_value = _fill_value;
}

LinearNDInterpolator::~LinearNDInterpolator() {
    delete tri;
}

void LinearNDInterpolator::_do_evaluate(const std::vector<Vector2>& xi, std::vector<double>& out) {
    int ndim = 2;
    int start = 0;
    double c[NPY_MAXDIMS];

    out.clear();
    out.resize(xi.size(), 0.0);
    int nvalues = 1;

    for (int i = 0; i < xi.size(); i++) {
        int isimplex = tri->_find_simplex(c, xi[i], &start);

        if (isimplex == -1) {
            out[i] = fill_value;
            continue;
        }

        out[i] = 0.0;

        for (int j = 0; j < ndim+1; j++) {
            int m = tri->get_simplices()[isimplex*(ndim+1) + j];
            out[i] += c[j] * values[m];
        }
    }
}
