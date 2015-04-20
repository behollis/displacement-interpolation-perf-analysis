# Introduction #
Interpolation of 4 bivariate probability distributions was performed in a grid cell which allows interpolation along both alpha and beta "axes" and were timed.  Probability distributions were given in the form of 2D-vector samples and their output was represented by a set of discrete samples at a resolution of 140x140 each.  The variance of this input set was quadrupled to record any potential changes in measurements or outputs.

The distributions themselves had 600 vector samples which follow 2D Gaussian sampling at various means:

### Distribution A ###
At alpha = 0, beta = 0, a unimodal distribution of four times the variance was provided with the following properties:

| mean | | covariance | matrix | | percentage of samples |
|:-----|:|:-----------|:-------|:|:----------------------|
|  0   |  |  4         |  0     |  | 100                   |
| -1   |  |  0         |  4     |  |                       |

### Distribution B ###
At alpha = 1, beta = 0, a bimodal distribution of four times the variance was provided with the following properties:

| mean | | covariance | matrix | | percentage of samples |
|:-----|:|:-----------|:-------|:|:----------------------|
|  2   |  |  4         |  0     |  |  60                   |
|  1   |  |  0         |  4     |  |                       |
| mean |  | covariance | matrix |  | percentage of samples |
| -2   |  |  6         |  0     |  |  40                   |
| -1   |  |  0         |  6     |  |                       |

### Distribution C ###
At alpha = 0, beta = 1, a trimodal distribution of four times the variance was provided with the following properties:

| mean | | covariance | matrix | | percentage of samples |
|:-----|:|:-----------|:-------|:|:----------------------|
|  2   |  |  4         |  4     |  |  30                   |
|  4   |  |  4         |  4     |  |                       |
| mean |  | covariance | matrix |  | percentage of samples |
| -1   |  |  2         |  0     |  |  50                   |
| -3   |  |  0         |  2     |  |                       |
| mean |  | covariance | matrix |  | percentage of samples |
| -4   |  |  4         |  0     |  |  20                   |
| -3   |  |  0         |  4     |  |                       |

### Distribution D ###
At alpha = 1, beta = 1, a quadrimodal distribution of four times the variance was provided with the following properties:

| mean | | covariance | matrix | | percentage of samples |
|:-----|:|:-----------|:-------|:|:----------------------|
| -1   |  |  4         |  0     |  |  25                   |
| -1   |  |  0         |  4     |  |                       |
| mean |  | covariance | matrix |  | percentage of samples |
|  0   |  |  4         | -2     |  |  30                   |
|  1   |  | -2         |  4     |  |                       |
| mean |  | covariance | matrix |  | percentage of samples |
|  3   |  |  6         |  0     |  |  25                   |
|  2   |  |  0         |  6     |  |                       |
| mean |  | covariance | matrix |  | percentage of samples |
| -4   |  |  4         |  0     |  |  20                   |
|  0   |  |  0         |  4     |  |                       |

# Density Estimates vs Endpoint Interpolation #
The following table is a comparison of Gaussian kernel density estimates of the provided vector samples and the interpolation techniques' outputs at grid cell corners.

| Distribution Type | Kernel Density Estimate | Quantile Interpolation & Surface Reconstruction | Displacement Interpolation |
|:------------------|:------------------------|:------------------------------------------------|:---------------------------|
| Uni-modal<br />alpha = 0, beta = 0 | <a href='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/varianceX4/distAx4.png'><img width='200' src='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/varianceX4/distAx4.png' /></a> | <a href='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/varianceX4/resurface0.png'><img width='200' src='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/varianceX4/resurface0.png' /></a> | <a href='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/varianceX4/interpolated0.png'><img width='200' src='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/varianceX4/interpolated0.png' /></a> |
| Bi-modal<br />alpha = 1, beta = 0 | <a href='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/varianceX4/distBx4.png'><img width='200' src='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/varianceX4/distBx4.png' /></a> | <a href='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/varianceX4/resurface9.png'><img width='200' src='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/varianceX4/resurface9.png' /></a> | <a href='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/varianceX4/interpolated9.png'><img width='200' src='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/varianceX4/interpolated9.png' /></a> |
| Tri-modal<br />alpha = 0, beta = 1 | <a href='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/varianceX4/distCx4.png'><img width='200' src='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/varianceX4/distCx4.png' /></a> | <a href='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/varianceX4/resurface10.png'><img width='200' src='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/varianceX4/resurface10.png' /></a> | <a href='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/varianceX4/interpolated10.png'><img width='200' src='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/varianceX4/interpolated10.png' /></a> |
| Quad-modal<br />alpha = 1, beta = 1 | <a href='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/varianceX4/distDx4.png'><img width='200' src='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/varianceX4/distDx4.png' /></a> | <a href='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/varianceX4/resurface19.png'><img width='200' src='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/varianceX4/resurface19.png' /></a> | <a href='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/varianceX4/interpolated19.png'><img width='200' src='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/varianceX4/interpolated19.png' /></a> |

# Interpolation Along Grid Cell Edges #
Interpolation of the 4 probability distributions along the edges of the grid cell allowed for focus on interpolation between pairs of probability distributions.  The edges were between distribution pairs A-B, C-D, A-C, and B-D.

_Earth Mover's Distance calculations will be provided soon_

### Interpolation Along Edge A-B ###
For the grid cell edge in which beta = 0, the following table shows 10 interpolation steps with 2 being at the endpoints (alpha = 0 and alpha = 1).

| Interpolation Coordinates | Displacement Interpolation | Quantile Interpolation & Surface Reconstruction |
|:--------------------------|:---------------------------|:------------------------------------------------|
| alpha=0.000, beta=0 | <a href='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/varianceX4/interpolated0.png'><img width='200' src='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/varianceX4/interpolated0.png' /></a> | <a href='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/varianceX4/resurface0.png'><img width='200' src='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/varianceX4/resurface0.png' /></a> |
| alpha=0.111, beta=0 | <a href='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/varianceX4/interpolated1.png'><img width='200' src='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/varianceX4/interpolated1.png' /></a> | <a href='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/varianceX4/resurface1.png'><img width='200' src='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/varianceX4/resurface1.png' /></a> |
| alpha=0.222, beta=0 | <a href='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/varianceX4/interpolated2.png'><img width='200' src='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/varianceX4/interpolated2.png' /></a> | <a href='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/varianceX4/resurface2.png'><img width='200' src='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/varianceX4/resurface2.png' /></a> |
| alpha=0.333, beta=0 | <a href='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/varianceX4/interpolated3.png'><img width='200' src='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/varianceX4/interpolated3.png' /></a> | <a href='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/varianceX4/resurface3.png'><img width='200' src='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/varianceX4/resurface3.png' /></a> |
| alpha=0.444, beta=0 | <a href='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/varianceX4/interpolated4.png'><img width='200' src='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/varianceX4/interpolated4.png' /></a> | <a href='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/varianceX4/resurface4.png'><img width='200' src='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/varianceX4/resurface4.png' /></a> |
| alpha=0.556, beta=0 | <a href='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/varianceX4/interpolated5.png'><img width='200' src='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/varianceX4/interpolated5.png' /></a> | <a href='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/varianceX4/resurface5.png'><img width='200' src='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/varianceX4/resurface5.png' /></a> |
| alpha=0.667, beta=0 | <a href='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/varianceX4/interpolated6.png'><img width='200' src='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/varianceX4/interpolated6.png' /></a> | <a href='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/varianceX4/resurface6.png'><img width='200' src='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/varianceX4/resurface6.png' /></a> |
| alpha=0.778, beta=0 | <a href='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/varianceX4/interpolated7.png'><img width='200' src='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/varianceX4/interpolated7.png' /></a> | <a href='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/varianceX4/resurface7.png'><img width='200' src='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/varianceX4/resurface7.png' /></a> |
| alpha=0.889, beta=0 | <a href='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/varianceX4/interpolated8.png'><img width='200' src='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/varianceX4/interpolated8.png' /></a> | <a href='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/varianceX4/resurface8.png'><img width='200' src='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/varianceX4/resurface8.png' /></a> |
| alpha=1.000, beta=0 | <a href='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/varianceX4/interpolated9.png'><img width='200' src='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/varianceX4/interpolated9.png' /></a> | <a href='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/varianceX4/resurface9.png'><img width='200' src='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/varianceX4/resurface9.png' /></a> |

### Interpolation Along Edge C-D ###
For the grid cell edge in which beta = 1, the following table shows 10 interpolation steps with 2 being at the endpoints (alpha = 0 and alpha = 1).

| Interpolation Coordinates | Displacement Interpolation | Quantile Interpolation & Surface Reconstruction |
|:--------------------------|:---------------------------|:------------------------------------------------|
| alpha=0.000, beta=1 | <a href='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/varianceX4/interpolated10.png'><img width='200' src='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/varianceX4/interpolated10.png' /></a> | <a href='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/varianceX4/resurface10.png'><img width='200' src='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/varianceX4/resurface10.png' /></a> |
| alpha=0.111, beta=1 | <a href='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/varianceX4/interpolated11.png'><img width='200' src='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/varianceX4/interpolated11.png' /></a> | <a href='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/varianceX4/resurface11.png'><img width='200' src='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/varianceX4/resurface11.png' /></a> |
| alpha=0.222, beta=1 | <a href='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/varianceX4/interpolated12.png'><img width='200' src='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/varianceX4/interpolated12.png' /></a> | <a href='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/varianceX4/resurface12.png'><img width='200' src='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/varianceX4/resurface12.png' /></a> |
| alpha=0.333, beta=1 | <a href='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/varianceX4/interpolated13.png'><img width='200' src='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/varianceX4/interpolated13.png' /></a> | <a href='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/varianceX4/resurface13.png'><img width='200' src='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/varianceX4/resurface13.png' /></a> |
| alpha=0.444, beta=1 | <a href='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/varianceX4/interpolated14.png'><img width='200' src='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/varianceX4/interpolated14.png' /></a> | <a href='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/varianceX4/resurface14.png'><img width='200' src='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/varianceX4/resurface14.png' /></a> |
| alpha=0.556, beta=1 | <a href='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/varianceX4/interpolated15.png'><img width='200' src='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/varianceX4/interpolated15.png' /></a> | <a href='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/varianceX4/resurface15.png'><img width='200' src='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/varianceX4/resurface15.png' /></a> |
| alpha=0.667, beta=1 | <a href='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/varianceX4/interpolated16.png'><img width='200' src='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/varianceX4/interpolated16.png' /></a> | <a href='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/varianceX4/resurface16.png'><img width='200' src='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/varianceX4/resurface16.png' /></a> |
| alpha=0.778, beta=1 | <a href='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/varianceX4/interpolated17.png'><img width='200' src='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/varianceX4/interpolated17.png' /></a> | <a href='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/varianceX4/resurface17.png'><img width='200' src='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/varianceX4/resurface17.png' /></a> |
| alpha=0.889, beta=1 | <a href='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/varianceX4/interpolated18.png'><img width='200' src='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/varianceX4/interpolated18.png' /></a> | <a href='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/varianceX4/resurface18.png'><img width='200' src='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/varianceX4/resurface18.png' /></a> |
| alpha=1.000, beta=1 | <a href='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/varianceX4/interpolated19.png'><img width='200' src='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/varianceX4/interpolated19.png' /></a> | <a href='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/varianceX4/resurface19.png'><img width='200' src='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/varianceX4/resurface19.png' /></a> |

### Interpolation Along Edge A-C ###
For the grid cell edge in which alpha = 0, the following table shows 10 interpolation steps with 2 being at the endpoints (beta = 0 and beta = 1).

| Interpolation Coordinates | Displacement Interpolation | Quantile Interpolation & Surface Reconstruction |
|:--------------------------|:---------------------------|:------------------------------------------------|
| alpha=0, beta=0.000 | <a href='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/varianceX4/interpolated20.png'><img width='200' src='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/varianceX4/interpolated20.png' /></a> | <a href='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/varianceX4/resurface20.png'><img width='200' src='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/varianceX4/resurface20.png' /></a> |
| alpha=0, beta=0.111 | <a href='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/varianceX4/interpolated21.png'><img width='200' src='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/varianceX4/interpolated21.png' /></a> | <a href='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/varianceX4/resurface21.png'><img width='200' src='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/varianceX4/resurface21.png' /></a> |
| alpha=0, beta=0.222 | <a href='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/varianceX4/interpolated22.png'><img width='200' src='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/varianceX4/interpolated22.png' /></a> | <a href='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/varianceX4/resurface22.png'><img width='200' src='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/varianceX4/resurface22.png' /></a> |
| alpha=0, beta=0.333 | <a href='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/varianceX4/interpolated23.png'><img width='200' src='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/varianceX4/interpolated23.png' /></a> | <a href='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/varianceX4/resurface23.png'><img width='200' src='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/varianceX4/resurface23.png' /></a> |
| alpha=0, beta=0.444 | <a href='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/varianceX4/interpolated24.png'><img width='200' src='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/varianceX4/interpolated24.png' /></a> | <a href='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/varianceX4/resurface24.png'><img width='200' src='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/varianceX4/resurface24.png' /></a> |
| alpha=0, beta=0.556 | <a href='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/varianceX4/interpolated25.png'><img width='200' src='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/varianceX4/interpolated25.png' /></a> | <a href='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/varianceX4/resurface25.png'><img width='200' src='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/varianceX4/resurface25.png' /></a> |
| alpha=0, beta=0.667 | <a href='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/varianceX4/interpolated26.png'><img width='200' src='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/varianceX4/interpolated26.png' /></a> | <a href='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/varianceX4/resurface26.png'><img width='200' src='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/varianceX4/resurface26.png' /></a> |
| alpha=0, beta=0.778 | <a href='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/varianceX4/interpolated27.png'><img width='200' src='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/varianceX4/interpolated27.png' /></a> | <a href='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/varianceX4/resurface27.png'><img width='200' src='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/varianceX4/resurface27.png' /></a> |
| alpha=0, beta=0.889 | <a href='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/varianceX4/interpolated28.png'><img width='200' src='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/varianceX4/interpolated28.png' /></a> | <a href='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/varianceX4/resurface28.png'><img width='200' src='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/varianceX4/resurface28.png' /></a> |
| alpha=0, beta=1.000 | <a href='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/varianceX4/interpolated29.png'><img width='200' src='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/varianceX4/interpolated29.png' /></a> | <a href='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/varianceX4/resurface29.png'><img width='200' src='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/varianceX4/resurface29.png' /></a> |

### Interpolation Along Edge B-D ###
For the grid cell edge in which alpha = 1, the following table shows 10 interpolation steps with 2 being at the endpoints (beta = 0 and beta = 1).

| Interpolation Coordinates | Displacement Interpolation | Quantile Interpolation & Surface Reconstruction |
|:--------------------------|:---------------------------|:------------------------------------------------|
| alpha=1, beta=0.000 | <a href='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/varianceX4/interpolated30.png'><img width='200' src='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/varianceX4/interpolated30.png' /></a> | <a href='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/varianceX4/resurface30.png'><img width='200' src='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/varianceX4/resurface30.png' /></a> |
| alpha=1, beta=0.111 | <a href='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/varianceX4/interpolated31.png'><img width='200' src='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/varianceX4/interpolated31.png' /></a> | <a href='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/varianceX4/resurface31.png'><img width='200' src='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/varianceX4/resurface31.png' /></a> |
| alpha=1, beta=0.222 | <a href='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/varianceX4/interpolated32.png'><img width='200' src='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/varianceX4/interpolated32.png' /></a> | <a href='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/varianceX4/resurface32.png'><img width='200' src='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/varianceX4/resurface32.png' /></a> |
| alpha=1, beta=0.333 | <a href='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/varianceX4/interpolated33.png'><img width='200' src='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/varianceX4/interpolated33.png' /></a> | <a href='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/varianceX4/resurface33.png'><img width='200' src='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/varianceX4/resurface33.png' /></a> |
| alpha=1, beta=0.444 | <a href='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/varianceX4/interpolated34.png'><img width='200' src='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/varianceX4/interpolated34.png' /></a> | <a href='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/varianceX4/resurface34.png'><img width='200' src='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/varianceX4/resurface34.png' /></a> |
| alpha=1, beta=0.556 | <a href='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/varianceX4/interpolated35.png'><img width='200' src='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/varianceX4/interpolated35.png' /></a> | <a href='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/varianceX4/resurface35.png'><img width='200' src='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/varianceX4/resurface35.png' /></a> |
| alpha=1, beta=0.667 | <a href='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/varianceX4/interpolated36.png'><img width='200' src='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/varianceX4/interpolated36.png' /></a> | <a href='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/varianceX4/resurface36.png'><img width='200' src='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/varianceX4/resurface36.png' /></a> |
| alpha=1, beta=0.778 | <a href='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/varianceX4/interpolated37.png'><img width='200' src='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/varianceX4/interpolated37.png' /></a> | <a href='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/varianceX4/resurface37.png'><img width='200' src='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/varianceX4/resurface37.png' /></a> |
| alpha=1, beta=0.889 | <a href='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/varianceX4/interpolated38.png'><img width='200' src='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/varianceX4/interpolated38.png' /></a> | <a href='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/varianceX4/resurface38.png'><img width='200' src='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/varianceX4/resurface38.png' /></a> |
| alpha=1, beta=1.000 | <a href='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/varianceX4/interpolated39.png'><img width='200' src='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/varianceX4/interpolated39.png' /></a> | <a href='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/varianceX4/resurface39.png'><img width='200' src='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/varianceX4/resurface39.png' /></a> |

# Interpolation To The Grid Cell Center #
An additional interpolation was performed at the grid cell's center (alpha = 0.5 and beta = 0.5).  This is an interpolation of all four distributions rather than a pair of distributions.

| Interpolation Coordinates | Displacement Interpolation | Quantile Interpolation & Surface Reconstruction |
|:--------------------------|:---------------------------|:------------------------------------------------|
| alpha=0.5, beta=0.5 | <a href='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/varianceX4/interpolated40.png'><img width='200' src='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/varianceX4/interpolated40.png' /></a> | <a href='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/varianceX4/resurface40.png'><img width='200' src='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/varianceX4/resurface40.png' /></a> |

# Timings #
The time was recorded throughout the interpolations, both in terms of wall-clock time and processor clock time.  More information about the computer which performed the interpolations will be provided soon.  The timings are divided into interpolations along each edge and a final interpolation to the grid cell center.

### Edge A-B Interpolation Timings ###
Displacement Interpolation:
  * **Construction of Probability Density A:**
    * wall-clock: 716ms
    * processor clock: 716ms
  * **Construction of Probability Density B:**
    * wall-clock: 718ms
    * processor clock: 718ms
  * **Precomputation:**
    * wall-clock: 68014750ms (~18.89 hours)
    * processor clock: 131858869ms (~36.63 hours)
  * **Average Interpolation (10 iterations):**
    * wall-clock: 72162.1ms (~1.20 minutes)
    * processor clock: 72150.0ms (~1.20 minutes)

Quantile Interpolation:
  * **Calculation of Cumulative Distribution A:**
    * wall-clock: 47145ms (~0.79 minutes)
    * processor clock: 47136ms (~0.79 minutes)
  * **Parameterizing Quantile Curves of Distribution A:**
    * wall-clock: 3ms
    * processor clock: 3ms
  * **Calculation of Cumulative Distribution B:**
    * wall-clock: 71616ms (~1.19 minutes)
    * processor clock: 71603ms (~1.19 minutes)
  * **Parameterizing Quantile Curves of Distribution B:**
    * wall-clock: 3ms
    * processor clock: 3ms
  * **Average Interpolation of Quantiles (10 iterations):**
    * wall-clock: 1.0ms
    * processor clock: 0.4ms
  * **Average Interpolant PDF Evaluation (10 iterations):**
    * wall-clock: 2296.0ms
    * processor clock: 2295.8ms

### Edge C-D Interpolation Timings ###
Displacement Interpolation:
  * **Construction of Probability Density C:**
    * wall-clock: 718ms
    * processor clock: 717ms
  * **Construction of Probability Density D:**
    * wall-clock: 720ms
    * processor clock: 718ms
  * **Precomputation:**
    * wall-clock: 65735729ms (~18.26 hours)
    * processor clock: 124668008ms (~34.63 hours)
  * **Average Interpolation (10 iterations):**
    * wall-clock: 70483.1ms (~1.17 minutes)
    * processor clock: 70471.1ms (~1.17 minutes)

Quantile Interpolation:
  * **Calculation of Cumulative Distribution C:**
    * wall-clock: 70451ms (~1.17 minutes)
    * processor clock: 70441ms (~1.17 minutes)
  * **Parameterizing Quantile Curves of Distribution C:**
    * wall-clock: 4ms
    * processor clock: 3ms
  * **Calculation of Cumulative Distribution D:**
    * wall-clock: 46553ms (~0.78 minutes)
    * processor clock: 46545ms (~0.78 minutes)
  * **Parameterizing Quantile Curves of Distribution D:**
    * wall-clock: 3ms
    * processor clock: 3ms
  * **Average Interpolation of Quantiles (10 iterations):**
    * wall-clock: 1.0ms
    * processor clock: 0.9ms
  * **Average Interpolant PDF Evaluation (10 iterations):**
    * wall-clock: 2296.5ms
    * processor clock: 2295.9ms

### Edge A-C Interpolation Timings ###
Displacement Interpolation:
  * **Construction of Probability Density A:**
    * wall-clock: 716ms
    * processor clock: 716ms
  * **Construction of Probability Density C:**
    * wall-clock: 718ms
    * processor clock: 717ms
  * **Precomputation:**
    * wall-clock: 68044064ms (~18.90 hours)
    * processor clock: 127000784ms (~35.28 hours)
  * **Average Interpolation (10 iterations):**
    * wall-clock: 69897.4ms (~1.16 minutes)
    * processor clock: 69885.4ms (~1.16 minutes)

Quantile Interpolation:
  * **Calculation of Cumulative Distribution A:**
    * wall-clock: 47145ms (~0.79 minutes)
    * processor clock: 47136ms (~0.79 minutes)
  * **Parameterizing Quantile Curves of Distribution A:**
    * wall-clock: 3ms
    * processor clock: 3ms
  * **Calculation of Cumulative Distribution C:**
    * wall-clock: 70451ms (~1.17 minutes)
    * processor clock: 70441ms (~1.17 minutes)
  * **Parameterizing Quantile Curves of Distribution C:**
    * wall-clock: 4ms
    * processor clock: 3ms
  * **Average Interpolation of Quantiles (10 iterations):**
    * wall-clock: 1.0ms
    * processor clock: 0.6ms
  * **Average Interpolant PDF Evaluation (10 iterations):**
    * wall-clock: 2296.4ms
    * processor clock: 2295.8ms

### Edge B-D Interpolation Timings ###
Displacement Interpolation:
  * **Construction of Probability Density B:**
    * wall-clock: 718ms
    * processor clock: 718ms
  * **Construction of Probability Density D:**
    * wall-clock: 720ms
    * processor clock: 718ms
  * **Precomputation:**
    * wall-clock: 65749462ms (~18.26 hours)
    * processor clock: 130082459ms (~36.13 hours)
  * **Average Interpolation (10 iterations):**
    * wall-clock: 72952.0ms (~1.22 minutes)
    * processor clock: 72939.0ms (~1.22 minutes)

Quantile Interpolation:
  * **Calculation of Cumulative Distribution B:**
    * wall-clock: 71616ms (~1.19 minutes)
    * processor clock: 71603ms (~1.19 minutes)
  * **Parameterizing Quantile Curves of Distribution B:**
    * wall-clock: 3ms
    * processor clock: 3ms
  * **Calculation of Cumulative Distribution D:**
    * wall-clock: 46553ms (~0.78 minutes)
    * processor clock: 46545ms (~0.78 minutes)
  * **Parameterizing Quantile Curves of Distribution D:**
    * wall-clock: 3ms
    * processor clock: 3ms
  * **Average Interpolation of Quantiles (10 iterations):**
    * wall-clock: 1.0ms
    * processor clock: 0.9ms
  * **Average Interpolant PDF Evaluation (10 iterations):**
    * wall-clock: 2296.4ms
    * processor clock: 2296.2ms

### Grid Cell Center Interpolation Timings ###
Displacement Interpolation:
  * **Construction of Probability Density A:**
    * wall-clock: 716ms
    * processor clock: 716ms
  * **Construction of Probability Density B:**
    * wall-clock: 718ms
    * processor clock: 718ms
  * **Construction of Probability Density C:**
    * wall-clock: 718ms
    * processor clock: 717ms
  * **Construction of Probability Density D:**
    * wall-clock: 720ms
    * processor clock: 718ms
  * **Find Halfway-Interpolated Distribution on Edge A-B:**
    * wall-clock: 71991ms (~1.20 minutes)
    * processor clock: 71980ms (~1.20 minutes)
  * **Find Halfway-Interpolated Distribution on Edge C-D:**
    * wall-clock: 70384ms (~1.17 minutes)
    * processor clock: 70371ms (~1.17 minutes)
  * **Precomputation:**
    * wall-clock: 48882993ms (~13.58 hours)
    * processor clock: 71799387ms (~19.94 hours)
  * **Interpolation:**
    * wall-clock: 51447ms (~0.86 minutes)
    * processor clock: 51439ms (~0.86 minutes)

Quantile Interpolation:
  * **Calculation of Cumulative Distribution A:**
    * wall-clock: 47145ms (~0.79 minutes)
    * processor clock: 47136ms (~0.79 minutes)
  * **Parameterizing Quantile Curves of Distribution A:**
    * wall-clock: 3ms
    * processor clock: 3ms
  * **Calculation of Cumulative Distribution B:**
    * wall-clock: 71616ms (~1.19 minutes)
    * processor clock: 71603ms (~1.19 minutes)
  * **Parameterizing Quantile Curves of Distribution B:**
    * wall-clock: 3ms
    * processor clock: 3ms
  * **Calculation of Cumulative Distribution C:**
    * wall-clock: 70451ms (~1.17 minutes)
    * processor clock: 70441ms (~1.17 minutes)
  * **Parameterizing Quantile Curves of Distribution C:**
    * wall-clock: 4ms
    * processor clock: 3ms
  * **Calculation of Cumulative Distribution D:**
    * wall-clock: 46553ms (~0.78 minutes)
    * processor clock: 46545ms (~0.78 minutes)
  * **Parameterizing Quantile Curves of Distribution D:**
    * wall-clock: 3ms
    * processor clock: 3ms
  * **Interpolation of Quantiles:**
    * wall-clock: 1ms
    * processor clock: 1ms
  * **Interpolant PDF Evaluation:**
    * wall-clock: 2296ms
    * processor clock: 2296ms