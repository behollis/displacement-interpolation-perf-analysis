#ifndef _INTERP_H
#define _INTERP_H

#include <vector>
#include <iostream>
#include <cstdlib>

#include "Vector2.h"
#include "error.h"

//void error(const std::string& message);

class Delaunay;

class LinearNDInterpolator {
    const std::vector<Vector2>& points;
    const std::vector<double>& values;
    Delaunay* tri;
    double fill_value;

public:
    LinearNDInterpolator(const std::vector<Vector2>& _points,
            const std::vector<double>& _values, double _fill_value);

    ~LinearNDInterpolator();

    void _do_evaluate(const std::vector<Vector2>& xi, std::vector<double>& out);
};

#endif
