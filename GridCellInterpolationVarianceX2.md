# Introduction #
Interpolation of 4 bivariate probability distributions was performed in a grid cell which allows interpolation along both alpha and beta "axes" and were timed.  Probability distributions were given in the form of 2D-vector samples and their output was represented by a set of discrete samples at a resolution of 140x140 each.  The variance of this input set was doubled to record any potential changes in measurements or outputs.

The distributions themselves had 600 vector samples which follow 2D Gaussian sampling at various means:

### Distribution A ###
At alpha = 0, beta = 0, a unimodal distribution of twice the variance was provided with the following properties:

| mean | | covariance | matrix | | percentage of samples |
|:-----|:|:-----------|:-------|:|:----------------------|
|  0   |  |  2         |  0     |  | 100                   |
| -1   |  |  0         |  2     |  |                       |

### Distribution B ###
At alpha = 1, beta = 0, a bimodal distribution of twice the variance was provided with the following properties:

| mean | | covariance | matrix | | percentage of samples |
|:-----|:|:-----------|:-------|:|:----------------------|
|  2   |  |  2         |  0     |  |  60                   |
|  1   |  |  0         |  2     |  |                       |
| mean |  | covariance | matrix |  | percentage of samples |
| -2   |  |  3         |  0     |  |  40                   |
| -1   |  |  0         |  3     |  |                       |

### Distribution C ###
At alpha = 0, beta = 1, a trimodal distribution of twice the variance was provided with the following properties:

| mean | | covariance | matrix | | percentage of samples |
|:-----|:|:-----------|:-------|:|:----------------------|
|  2   |  |  2         |  2     |  |  30                   |
|  4   |  |  2         |  2     |  |                       |
| mean |  | covariance | matrix |  | percentage of samples |
| -1   |  |  1         |  0     |  |  50                   |
| -3   |  |  0         |  1     |  |                       |
| mean |  | covariance | matrix |  | percentage of samples |
| -4   |  |  2         |  0     |  |  20                   |
| -3   |  |  0         |  2     |  |                       |

### Distribution D ###
At alpha = 1, beta = 1, a quadrimodal distribution of twice the variance was provided with the following properties:

| mean | | covariance | matrix | | percentage of samples |
|:-----|:|:-----------|:-------|:|:----------------------|
| -1   |  |  2         |  0     |  |  25                   |
| -1   |  |  0         |  2     |  |                       |
| mean |  | covariance | matrix |  | percentage of samples |
|  0   |  |  2         | -1     |  |  30                   |
|  1   |  | -1         |  2     |  |                       |
| mean |  | covariance | matrix |  | percentage of samples |
|  3   |  |  3         |  0     |  |  25                   |
|  2   |  |  0         |  3     |  |                       |
| mean |  | covariance | matrix |  | percentage of samples |
| -4   |  |  2         |  0     |  |  20                   |
|  0   |  |  0         |  2     |  |                       |

# Density Estimates vs Endpoint Interpolation #
The following table is a comparison of Gaussian kernel density estimates of the provided vector samples and the interpolation techniques' outputs at grid cell corners.

| Distribution Type | Kernel Density Estimate | Quantile Interpolation & Surface Reconstruction | Displacement Interpolation |
|:------------------|:------------------------|:------------------------------------------------|:---------------------------|
| Uni-modal<br />alpha = 0, beta = 0 | <a href='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/varianceX2/distAx2.png'><img width='200' src='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/varianceX2/distAx2.png' /></a> | <a href='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/varianceX2/resurface0.png'><img width='200' src='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/varianceX2/resurface0.png' /></a> | <a href='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/varianceX2/interpolated0.png'><img width='200' src='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/varianceX2/interpolated0.png' /></a> |
| Bi-modal<br />alpha = 1, beta = 0 | <a href='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/varianceX2/distBx2.png'><img width='200' src='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/varianceX2/distBx2.png' /></a> | <a href='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/varianceX2/resurface9.png'><img width='200' src='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/varianceX2/resurface9.png' /></a> | <a href='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/varianceX2/interpolated9.png'><img width='200' src='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/varianceX2/interpolated9.png' /></a> |
| Tri-modal<br />alpha = 0, beta = 1 | <a href='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/varianceX2/distCx2.png'><img width='200' src='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/varianceX2/distCx2.png' /></a> | <a href='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/varianceX2/resurface10.png'><img width='200' src='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/varianceX2/resurface10.png' /></a> | <a href='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/varianceX2/interpolated10.png'><img width='200' src='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/varianceX2/interpolated10.png' /></a> |
| Quad-modal<br />alpha = 1, beta = 1 | <a href='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/varianceX2/distDx2.png'><img width='200' src='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/varianceX2/distDx2.png' /></a> | <a href='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/varianceX2/resurface19.png'><img width='200' src='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/varianceX2/resurface19.png' /></a> | <a href='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/varianceX2/interpolated19.png'><img width='200' src='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/varianceX2/interpolated19.png' /></a> |

# Interpolation Along Grid Cell Edges #
Interpolation of the 4 probability distributions along the edges of the grid cell allowed for focus on interpolation between pairs of probability distributions.  The edges were between distribution pairs A-B, C-D, A-C, and B-D.

_Earth Mover's Distance calculations will be provided soon_

### Interpolation Along Edge A-B ###
For the grid cell edge in which beta = 0, the following table shows 10 interpolation steps with 2 being at the endpoints (alpha = 0 and alpha = 1).

| Interpolation Coordinates | Displacement Interpolation | Quantile Interpolation & Surface Reconstruction |
|:--------------------------|:---------------------------|:------------------------------------------------|
| alpha=0.000, beta=0 | <a href='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/varianceX2/interpolated0.png'><img width='200' src='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/varianceX2/interpolated0.png' /></a> | <a href='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/varianceX2/resurface0.png'><img width='200' src='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/varianceX2/resurface0.png' /></a> |
| alpha=0.111, beta=0 | <a href='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/varianceX2/interpolated1.png'><img width='200' src='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/varianceX2/interpolated1.png' /></a> | <a href='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/varianceX2/resurface1.png'><img width='200' src='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/varianceX2/resurface1.png' /></a> |
| alpha=0.222, beta=0 | <a href='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/varianceX2/interpolated2.png'><img width='200' src='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/varianceX2/interpolated2.png' /></a> | <a href='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/varianceX2/resurface2.png'><img width='200' src='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/varianceX2/resurface2.png' /></a> |
| alpha=0.333, beta=0 | <a href='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/varianceX2/interpolated3.png'><img width='200' src='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/varianceX2/interpolated3.png' /></a> | <a href='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/varianceX2/resurface3.png'><img width='200' src='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/varianceX2/resurface3.png' /></a> |
| alpha=0.444, beta=0 | <a href='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/varianceX2/interpolated4.png'><img width='200' src='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/varianceX2/interpolated4.png' /></a> | <a href='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/varianceX2/resurface4.png'><img width='200' src='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/varianceX2/resurface4.png' /></a> |
| alpha=0.556, beta=0 | <a href='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/varianceX2/interpolated5.png'><img width='200' src='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/varianceX2/interpolated5.png' /></a> | <a href='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/varianceX2/resurface5.png'><img width='200' src='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/varianceX2/resurface5.png' /></a> |
| alpha=0.667, beta=0 | <a href='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/varianceX2/interpolated6.png'><img width='200' src='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/varianceX2/interpolated6.png' /></a> | <a href='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/varianceX2/resurface6.png'><img width='200' src='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/varianceX2/resurface6.png' /></a> |
| alpha=0.778, beta=0 | <a href='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/varianceX2/interpolated7.png'><img width='200' src='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/varianceX2/interpolated7.png' /></a> | <a href='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/varianceX2/resurface7.png'><img width='200' src='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/varianceX2/resurface7.png' /></a> |
| alpha=0.889, beta=0 | <a href='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/varianceX2/interpolated8.png'><img width='200' src='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/varianceX2/interpolated8.png' /></a> | <a href='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/varianceX2/resurface8.png'><img width='200' src='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/varianceX2/resurface8.png' /></a> |
| alpha=1.000, beta=0 | <a href='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/varianceX2/interpolated9.png'><img width='200' src='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/varianceX2/interpolated9.png' /></a> | <a href='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/varianceX2/resurface9.png'><img width='200' src='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/varianceX2/resurface9.png' /></a> |

### Interpolation Along Edge C-D ###
For the grid cell edge in which beta = 1, the following table shows 10 interpolation steps with 2 being at the endpoints (alpha = 0 and alpha = 1).

| Interpolation Coordinates | Displacement Interpolation | Quantile Interpolation & Surface Reconstruction |
|:--------------------------|:---------------------------|:------------------------------------------------|
| alpha=0.000, beta=1 | <a href='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/varianceX2/interpolated10.png'><img width='200' src='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/varianceX2/interpolated10.png' /></a> | <a href='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/varianceX2/resurface10.png'><img width='200' src='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/varianceX2/resurface10.png' /></a> |
| alpha=0.111, beta=1 | <a href='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/varianceX2/interpolated11.png'><img width='200' src='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/varianceX2/interpolated11.png' /></a> | <a href='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/varianceX2/resurface11.png'><img width='200' src='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/varianceX2/resurface11.png' /></a> |
| alpha=0.222, beta=1 | <a href='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/varianceX2/interpolated12.png'><img width='200' src='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/varianceX2/interpolated12.png' /></a> | <a href='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/varianceX2/resurface12.png'><img width='200' src='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/varianceX2/resurface12.png' /></a> |
| alpha=0.333, beta=1 | <a href='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/varianceX2/interpolated13.png'><img width='200' src='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/varianceX2/interpolated13.png' /></a> | <a href='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/varianceX2/resurface13.png'><img width='200' src='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/varianceX2/resurface13.png' /></a> |
| alpha=0.444, beta=1 | <a href='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/varianceX2/interpolated14.png'><img width='200' src='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/varianceX2/interpolated14.png' /></a> | <a href='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/varianceX2/resurface14.png'><img width='200' src='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/varianceX2/resurface14.png' /></a> |
| alpha=0.556, beta=1 | <a href='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/varianceX2/interpolated15.png'><img width='200' src='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/varianceX2/interpolated15.png' /></a> | <a href='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/varianceX2/resurface15.png'><img width='200' src='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/varianceX2/resurface15.png' /></a> |
| alpha=0.667, beta=1 | <a href='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/varianceX2/interpolated16.png'><img width='200' src='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/varianceX2/interpolated16.png' /></a> | <a href='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/varianceX2/resurface16.png'><img width='200' src='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/varianceX2/resurface16.png' /></a> |
| alpha=0.778, beta=1 | <a href='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/varianceX2/interpolated17.png'><img width='200' src='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/varianceX2/interpolated17.png' /></a> | <a href='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/varianceX2/resurface17.png'><img width='200' src='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/varianceX2/resurface17.png' /></a> |
| alpha=0.889, beta=1 | <a href='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/varianceX2/interpolated18.png'><img width='200' src='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/varianceX2/interpolated18.png' /></a> | <a href='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/varianceX2/resurface18.png'><img width='200' src='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/varianceX2/resurface18.png' /></a> |
| alpha=1.000, beta=1 | <a href='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/varianceX2/interpolated19.png'><img width='200' src='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/varianceX2/interpolated19.png' /></a> | <a href='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/varianceX2/resurface19.png'><img width='200' src='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/varianceX2/resurface19.png' /></a> |

### Interpolation Along Edge A-C ###
For the grid cell edge in which alpha = 0, the following table shows 10 interpolation steps with 2 being at the endpoints (beta = 0 and beta = 1).

| Interpolation Coordinates | Displacement Interpolation | Quantile Interpolation & Surface Reconstruction |
|:--------------------------|:---------------------------|:------------------------------------------------|
| alpha=0, beta=0.000 | <a href='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/varianceX2/interpolated20.png'><img width='200' src='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/varianceX2/interpolated20.png' /></a> | <a href='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/varianceX2/resurface20.png'><img width='200' src='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/varianceX2/resurface20.png' /></a> |
| alpha=0, beta=0.111 | <a href='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/varianceX2/interpolated21.png'><img width='200' src='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/varianceX2/interpolated21.png' /></a> | <a href='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/varianceX2/resurface21.png'><img width='200' src='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/varianceX2/resurface21.png' /></a> |
| alpha=0, beta=0.222 | <a href='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/varianceX2/interpolated22.png'><img width='200' src='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/varianceX2/interpolated22.png' /></a> | <a href='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/varianceX2/resurface22.png'><img width='200' src='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/varianceX2/resurface22.png' /></a> |
| alpha=0, beta=0.333 | <a href='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/varianceX2/interpolated23.png'><img width='200' src='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/varianceX2/interpolated23.png' /></a> | <a href='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/varianceX2/resurface23.png'><img width='200' src='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/varianceX2/resurface23.png' /></a> |
| alpha=0, beta=0.444 | <a href='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/varianceX2/interpolated24.png'><img width='200' src='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/varianceX2/interpolated24.png' /></a> | <a href='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/varianceX2/resurface24.png'><img width='200' src='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/varianceX2/resurface24.png' /></a> |
| alpha=0, beta=0.556 | <a href='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/varianceX2/interpolated25.png'><img width='200' src='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/varianceX2/interpolated25.png' /></a> | <a href='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/varianceX2/resurface25.png'><img width='200' src='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/varianceX2/resurface25.png' /></a> |
| alpha=0, beta=0.667 | <a href='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/varianceX2/interpolated26.png'><img width='200' src='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/varianceX2/interpolated26.png' /></a> | <a href='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/varianceX2/resurface26.png'><img width='200' src='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/varianceX2/resurface26.png' /></a> |
| alpha=0, beta=0.778 | <a href='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/varianceX2/interpolated27.png'><img width='200' src='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/varianceX2/interpolated27.png' /></a> | <a href='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/varianceX2/resurface27.png'><img width='200' src='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/varianceX2/resurface27.png' /></a> |
| alpha=0, beta=0.889 | <a href='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/varianceX2/interpolated28.png'><img width='200' src='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/varianceX2/interpolated28.png' /></a> | <a href='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/varianceX2/resurface28.png'><img width='200' src='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/varianceX2/resurface28.png' /></a> |
| alpha=0, beta=1.000 | <a href='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/varianceX2/interpolated29.png'><img width='200' src='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/varianceX2/interpolated29.png' /></a> | <a href='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/varianceX2/resurface29.png'><img width='200' src='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/varianceX2/resurface29.png' /></a> |

### Interpolation Along Edge B-D ###
For the grid cell edge in which alpha = 1, the following table shows 10 interpolation steps with 2 being at the endpoints (beta = 0 and beta = 1).

| Interpolation Coordinates | Displacement Interpolation | Quantile Interpolation & Surface Reconstruction |
|:--------------------------|:---------------------------|:------------------------------------------------|
| alpha=1, beta=0.000 | <a href='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/varianceX2/interpolated30.png'><img width='200' src='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/varianceX2/interpolated30.png' /></a> | <a href='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/varianceX2/resurface30.png'><img width='200' src='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/varianceX2/resurface30.png' /></a> |
| alpha=1, beta=0.111 | <a href='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/varianceX2/interpolated31.png'><img width='200' src='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/varianceX2/interpolated31.png' /></a> | <a href='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/varianceX2/resurface31.png'><img width='200' src='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/varianceX2/resurface31.png' /></a> |
| alpha=1, beta=0.222 | <a href='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/varianceX2/interpolated32.png'><img width='200' src='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/varianceX2/interpolated32.png' /></a> | <a href='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/varianceX2/resurface32.png'><img width='200' src='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/varianceX2/resurface32.png' /></a> |
| alpha=1, beta=0.333 | <a href='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/varianceX2/interpolated33.png'><img width='200' src='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/varianceX2/interpolated33.png' /></a> | <a href='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/varianceX2/resurface33.png'><img width='200' src='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/varianceX2/resurface33.png' /></a> |
| alpha=1, beta=0.444 | <a href='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/varianceX2/interpolated34.png'><img width='200' src='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/varianceX2/interpolated34.png' /></a> | <a href='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/varianceX2/resurface34.png'><img width='200' src='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/varianceX2/resurface34.png' /></a> |
| alpha=1, beta=0.556 | <a href='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/varianceX2/interpolated35.png'><img width='200' src='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/varianceX2/interpolated35.png' /></a> | <a href='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/varianceX2/resurface35.png'><img width='200' src='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/varianceX2/resurface35.png' /></a> |
| alpha=1, beta=0.667 | <a href='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/varianceX2/interpolated36.png'><img width='200' src='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/varianceX2/interpolated36.png' /></a> | <a href='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/varianceX2/resurface36.png'><img width='200' src='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/varianceX2/resurface36.png' /></a> |
| alpha=1, beta=0.778 | <a href='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/varianceX2/interpolated37.png'><img width='200' src='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/varianceX2/interpolated37.png' /></a> | <a href='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/varianceX2/resurface37.png'><img width='200' src='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/varianceX2/resurface37.png' /></a> |
| alpha=1, beta=0.889 | <a href='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/varianceX2/interpolated38.png'><img width='200' src='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/varianceX2/interpolated38.png' /></a> | <a href='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/varianceX2/resurface38.png'><img width='200' src='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/varianceX2/resurface38.png' /></a> |
| alpha=1, beta=1.000 | <a href='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/varianceX2/interpolated39.png'><img width='200' src='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/varianceX2/interpolated39.png' /></a> | <a href='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/varianceX2/resurface39.png'><img width='200' src='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/varianceX2/resurface39.png' /></a> |

# Interpolation To The Grid Cell Center #
An additional interpolation was performed at the grid cell's center (alpha = 0.5 and beta = 0.5).  This is an interpolation of all four distributions rather than a pair of distributions.

| Interpolation Coordinates | Displacement Interpolation | Quantile Interpolation & Surface Reconstruction |
|:--------------------------|:---------------------------|:------------------------------------------------|
| alpha=0.5, beta=0.5 | <a href='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/varianceX2/interpolated40.png'><img width='200' src='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/varianceX2/interpolated40.png' /></a> | <a href='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/varianceX2/resurface40.png'><img width='200' src='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/varianceX2/resurface40.png' /></a> |

# Timings #
The time was recorded throughout the interpolations, both in terms of wall-clock time and processor clock time.  More information about the computer which performed the interpolations will be provided soon.  The timings are divided into interpolations along each edge and a final interpolation to the grid cell center.

### Edge A-B Interpolation Timings ###
Displacement Interpolation:
  * **Construction of Probability Density A:**
    * wall-clock: 722ms
    * processor clock: 720ms
  * **Construction of Probability Density B:**
    * wall-clock: 721ms
    * processor clock: 722ms
  * **Precomputation:**
    * wall-clock: 68546766ms (~19.04 hours)
    * processor clock: 129527229ms (~35.98 hours)
  * **Average Interpolation (10 iterations):**
    * wall-clock: 70690.7ms (~1.18 minutes)
    * processor clock: 70679.1ms (~1.18 minutes)

Quantile Interpolation:
  * **Calculation of Cumulative Distribution A:**
    * wall-clock: 47559ms (~0.79 minutes)
    * processor clock: 47551ms (~0.79 minutes)
  * **Parameterizing Quantile Curves of Distribution A:**
    * wall-clock: 3ms
    * processor clock: 4ms
  * **Calculation of Cumulative Distribution B:**
    * wall-clock: 70576ms (~1.18 minutes)
    * processor clock: 70567ms (~1.18 minutes)
  * **Parameterizing Quantile Curves of Distribution B:**
    * wall-clock: 3ms
    * processor clock: 3ms
  * **Average Interpolation of Quantiles (10 iterations):**
    * wall-clock: 1.0ms
    * processor clock: 1.0ms
  * **Average Interpolant PDF Evaluation (10 iterations):**
    * wall-clock: 2278.7ms
    * processor clock: 2278.3ms

### Edge C-D Interpolation Timings ###
Displacement Interpolation:
  * **Construction of Probability Density C:**
    * wall-clock: 721ms
    * processor clock: 720ms
  * **Construction of Probability Density D:**
    * wall-clock: 722ms
    * processor clock: 721ms
  * **Precomputation:**
    * wall-clock: 64711920ms (~17.98 hours)
    * processor clock: 127333160ms (~35.37 hours)
  * **Average Interpolation (10 iterations):**
    * wall-clock: 71375.3ms (~1.19 minutes)
    * processor clock: 71363.7ms (~1.19 minutes)

Quantile Interpolation:
  * **Calculation of Cumulative Distribution C:**
    * wall-clock: 45795ms (~0.76 minutes)
    * processor clock: 45788ms (~0.76 minutes)
  * **Parameterizing Quantile Curves of Distribution C:**
    * wall-clock: 3ms
    * processor clock: 3ms
  * **Calculation of Cumulative Distribution D:**
    * wall-clock: 68938ms (~1.15 minutes)
    * processor clock: 68926ms (~1.15 minutes)
  * **Parameterizing Quantile Curves of Distribution D:**
    * wall-clock: 3ms
    * processor clock: 3ms
  * **Average Interpolation of Quantiles (10 iterations):**
    * wall-clock: 1.0ms
    * processor clock: 0.8ms
  * **Average Interpolant PDF Evaluation (10 iterations):**
    * wall-clock: 2278.8ms
    * processor clock: 2278.2ms

### Edge A-C Interpolation Timings ###
Displacement Interpolation:
  * **Construction of Probability Density A:**
    * wall-clock: 722ms
    * processor clock: 720ms
  * **Construction of Probability Density C:**
    * wall-clock: 721ms
    * processor clock: 720ms
  * **Precomputation:**
    * wall-clock: 67920822ms (~18.87 hours)
    * processor clock: 132406226ms (~36.73 hours)
  * **Average Interpolation (10 iterations):**
    * wall-clock: 71447.1ms (~1.19 minutes)
    * processor clock: 71435.4ms (~1.19 minutes)

Quantile Interpolation:
  * **Calculation of Cumulative Distribution A:**
    * wall-clock: 47559ms (~0.79 minutes)
    * processor clock: 47551ms (~0.79 minutes)
  * **Parameterizing Quantile Curves of Distribution A:**
    * wall-clock: 3ms
    * processor clock: 4ms
  * **Calculation of Cumulative Distribution C:**
    * wall-clock: 45795ms (~0.76 minutes)
    * processor clock: 45788ms (~0.76 minutes)
  * **Parameterizing Quantile Curves of Distribution C:**
    * wall-clock: 3ms
    * processor clock: 3ms
  * **Average Interpolation of Quantiles (10 iterations):**
    * wall-clock: 1.0ms
    * processor clock: 1.0ms
  * **Average Interpolant PDF Evaluation (10 iterations):**
    * wall-clock: 2278.3ms
    * processor clock: 2278.0ms

### Edge B-D Interpolation Timings ###
Displacement Interpolation:
  * **Construction of Probability Density B:**
    * wall-clock: 721ms
    * processor clock: 722ms
  * **Construction of Probability Density D:**
    * wall-clock: 722ms
    * processor clock: 721ms
  * **Precomputation:**
    * wall-clock: 63754527ms (~17.71 hours)
    * processor clock: 124709873ms (~34.64 hours)
  * **Average Interpolation (10 iterations):**
    * wall-clock: 70695.8ms (~1.18 minutes)
    * processor clock: 70684.3ms (~1.18 minutes)

Quantile Interpolation:
  * **Calculation of Cumulative Distribution B:**
    * wall-clock: 70576ms (~1.18 minutes)
    * processor clock: 70567ms (~1.18 minutes)
  * **Parameterizing Quantile Curves of Distribution B:**
    * wall-clock: 3ms
    * processor clock: 3ms
  * **Calculation of Cumulative Distribution D:**
    * wall-clock: 68938ms (~1.15 minutes)
    * processor clock: 68926ms (~1.15 minutes)
  * **Parameterizing Quantile Curves of Distribution D:**
    * wall-clock: 3ms
    * processor clock: 3ms
  * **Average Interpolation of Quantiles (10 iterations):**
    * wall-clock: 1.0ms
    * processor clock: 0.9ms
  * **Average Interpolant PDF Evaluation (10 iterations):**
    * wall-clock: 2278.5ms
    * processor clock: 2278.3ms

### Grid Cell Center Interpolation Timings ###
Displacement Interpolation:
  * **Construction of Probability Density A:**
    * wall-clock: 722ms
    * processor clock: 720ms
  * **Construction of Probability Density B:**
    * wall-clock: 721ms
    * processor clock: 722ms
  * **Construction of Probability Density C:**
    * wall-clock: 721ms
    * processor clock: 720ms
  * **Construction of Probability Density D:**
    * wall-clock: 722ms
    * processor clock: 721ms
  * **Find Halfway-Interpolated Distribution on Edge A-B:**
    * wall-clock: 70723ms (~1.18 minutes)
    * processor clock: 70712ms (~1.18 minutes)
  * **Find Halfway-Interpolated Distribution on Edge C-D:**
    * wall-clock: 71452ms (~1.19 minutes)
    * processor clock: 71440ms (~1.19 minutes)
  * **Precomputation:**
    * wall-clock: 54573155ms (~15.16 hours)
    * processor clock: 74698141ms (~20.75 hours)
  * **Interpolation:**
    * wall-clock: 52309ms (~0.87 minutes)
    * processor clock: 52302ms (~0.87 minutes)

Quantile Interpolation:
  * **Calculation of Cumulative Distribution A:**
    * wall-clock: 47559ms (~0.79 minutes)
    * processor clock: 47551ms (~0.79 minutes)
  * **Parameterizing Quantile Curves of Distribution A:**
    * wall-clock: 3ms
    * processor clock: 4ms
  * **Calculation of Cumulative Distribution B:**
    * wall-clock: 70576ms (~1.18 minutes)
    * processor clock: 70567ms (~1.18 minutes)
  * **Parameterizing Quantile Curves of Distribution B:**
    * wall-clock: 3ms
    * processor clock: 3ms
  * **Calculation of Cumulative Distribution C:**
    * wall-clock: 45795ms (~0.76 minutes)
    * processor clock: 45788ms (~0.76 minutes)
  * **Parameterizing Quantile Curves of Distribution C:**
    * wall-clock: 3ms
    * processor clock: 3ms
  * **Calculation of Cumulative Distribution D:**
    * wall-clock: 68938ms (~1.15 minutes)
    * processor clock: 68926ms (~1.15 minutes)
  * **Parameterizing Quantile Curves of Distribution D:**
    * wall-clock: 3ms
    * processor clock: 3ms
  * **Interpolation of Quantiles:**
    * wall-clock: 1ms
    * processor clock: 1ms
  * **Interpolant PDF Evaluation:**
    * wall-clock: 2279ms
    * processor clock: 2278ms