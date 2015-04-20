# Introduction #
Interpolation of 4 bivariate probability distributions was performed in a grid cell which allows interpolation along both alpha and beta "axes" and were timed.  Probability distributions were given in the form of 2D-vector samples and their output was represented by a set of discrete samples at a resolution of 140x140 each.

The distributions themselves had 600 vector samples which follow 2D Gaussian sampling at various means:

### Distribution A ###
At alpha = 0, beta = 0, a unimodal distribution was provided with the following properties:

| mean | | covariance | matrix | | percentage of samples |
|:-----|:|:-----------|:-------|:|:----------------------|
|  0   |  |  1         |  0     |  | 100                   |
| -1   |  |  0         |  1     |  |                       |

### Distribution B ###
At alpha = 1, beta = 0, a bimodal distribution was provided with the following properties:

| mean | | covariance | matrix | | percentage of samples |
|:-----|:|:-----------|:-------|:|:----------------------|
|  2   |  |  1         |  0     |  |  60                   |
|  1   |  |  0         |  1     |  |                       |
| mean |  | covariance | matrix |  | percentage of samples |
| -2   |  | 1.5        |  0     |  |  40                   |
| -1   |  |  0         | 1.5    |  |                       |

### Distribution C ###
At alpha = 0, beta = 1, a trimodal distribution was provided with the following properties:

| mean | | covariance | matrix | | percentage of samples |
|:-----|:|:-----------|:-------|:|:----------------------|
|  2   |  |  1         |  1     |  |  30                   |
|  4   |  |  1         |  1     |  |                       |
| mean |  | covariance | matrix |  | percentage of samples |
| -1   |  | 0.5        |  0     |  |  50                   |
| -3   |  |  0         | 0.5    |  |                       |
| mean |  | covariance | matrix |  | percentage of samples |
| -4   |  |  1         |  0     |  |  20                   |
| -3   |  |  0         |  1     |  |                       |

### Distribution D ###
At alpha = 1, beta = 1, a quadrimodal distribution was provided with the following properties:

| mean | | covariance | matrix | | percentage of samples |
|:-----|:|:-----------|:-------|:|:----------------------|
| -1   |  |  1         |  0     |  |  25                   |
| -1   |  |  0         |  1     |  |                       |
| mean |  | covariance | matrix |  | percentage of samples |
|  0   |  |  1         | -0.5   |  |  30                   |
|  1   |  | -0.5       |  1     |  |                       |
| mean |  | covariance | matrix |  | percentage of samples |
|  3   |  | 1.5        |  0     |  |  25                   |
|  2   |  |  0         | 1.5    |  |                       |
| mean |  | covariance | matrix |  | percentage of samples |
| -4   |  |  1         |  0     |  |  20                   |
|  0   |  |  0         |  1     |  |                       |

# Density Estimates vs Endpoint Interpolation #
The following table is a comparison of Gaussian kernel density estimates of the provided vector samples and the interpolation techniques' outputs at grid cell corners.

| Distribution Type | Kernel Density Estimate | Quantile Interpolation & Surface Reconstruction | Displacement Interpolation |
|:------------------|:------------------------|:------------------------------------------------|:---------------------------|
| Uni-modal<br />alpha = 0, beta = 0 | <a href='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/distA.png'><img width='200' src='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/distA.png' /></a> | <a href='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/resurface0.png'><img width='200' src='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/resurface0.png' /></a> | <a href='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/interpolated0.png'><img width='200' src='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/interpolated0.png' /></a> |
| Bi-modal<br />alpha = 1, beta = 0 | <a href='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/distB.png'><img width='200' src='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/distB.png' /></a> | <a href='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/resurface9.png'><img width='200' src='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/resurface9.png' /></a> | <a href='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/interpolated9.png'><img width='200' src='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/interpolated9.png' /></a> |
| Tri-modal<br />alpha = 0, beta = 1 | <a href='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/distC.png'><img width='200' src='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/distC.png' /></a> | <a href='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/resurface10.png'><img width='200' src='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/resurface10.png' /></a> | <a href='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/interpolated10.png'><img width='200' src='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/interpolated10.png' /></a> |
| Quad-modal<br />alpha = 1, beta = 1 | <a href='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/distD.png'><img width='200' src='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/distD.png' /></a> | <a href='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/resurface19.png'><img width='200' src='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/resurface19.png' /></a> | <a href='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/interpolated19.png'><img width='200' src='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/interpolated19.png' /></a> |

# Interpolation Along Grid Cell Edges #
Interpolation of the 4 probability distributions along the edges of the grid cell allowed for focus on interpolation between pairs of probability distributions.  The edges were between distribution pairs A-B, C-D, A-C, and B-D.

_Earth Mover's Distance calculations will be provided soon_

### Interpolation Along Edge A-B ###
For the grid cell edge in which beta = 0, the following table shows 10 interpolation steps with 2 being at the endpoints (alpha = 0 and alpha = 1).

| Interpolation Coordinates | Displacement Interpolation | Quantile Interpolation & Surface Reconstruction |
|:--------------------------|:---------------------------|:------------------------------------------------|
| alpha=0.000, beta=0 | <a href='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/interpolated0.png'><img width='200' src='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/interpolated0.png' /></a> | <a href='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/resurface0.png'><img width='200' src='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/resurface0.png' /></a> |
| alpha=0.111, beta=0 | <a href='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/interpolated1.png'><img width='200' src='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/interpolated1.png' /></a> | <a href='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/resurface1.png'><img width='200' src='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/resurface1.png' /></a> |
| alpha=0.222, beta=0 | <a href='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/interpolated2.png'><img width='200' src='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/interpolated2.png' /></a> | <a href='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/resurface2.png'><img width='200' src='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/resurface2.png' /></a> |
| alpha=0.333, beta=0 | <a href='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/interpolated3.png'><img width='200' src='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/interpolated3.png' /></a> | <a href='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/resurface3.png'><img width='200' src='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/resurface3.png' /></a> |
| alpha=0.444, beta=0 | <a href='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/interpolated4.png'><img width='200' src='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/interpolated4.png' /></a> | <a href='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/resurface4.png'><img width='200' src='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/resurface4.png' /></a> |
| alpha=0.556, beta=0 | <a href='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/interpolated5.png'><img width='200' src='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/interpolated5.png' /></a> | <a href='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/resurface5.png'><img width='200' src='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/resurface5.png' /></a> |
| alpha=0.667, beta=0 | <a href='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/interpolated6.png'><img width='200' src='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/interpolated6.png' /></a> | <a href='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/resurface6.png'><img width='200' src='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/resurface6.png' /></a> |
| alpha=0.778, beta=0 | <a href='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/interpolated7.png'><img width='200' src='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/interpolated7.png' /></a> | <a href='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/resurface7.png'><img width='200' src='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/resurface7.png' /></a> |
| alpha=0.889, beta=0 | <a href='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/interpolated8.png'><img width='200' src='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/interpolated8.png' /></a> | <a href='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/resurface8.png'><img width='200' src='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/resurface8.png' /></a> |
| alpha=1.000, beta=0 | <a href='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/interpolated9.png'><img width='200' src='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/interpolated9.png' /></a> | <a href='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/resurface9.png'><img width='200' src='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/resurface9.png' /></a> |

### Interpolation Along Edge C-D ###
For the grid cell edge in which beta = 1, the following table shows 10 interpolation steps with 2 being at the endpoints (alpha = 0 and alpha = 1).

| Interpolation Coordinates | Displacement Interpolation | Quantile Interpolation & Surface Reconstruction |
|:--------------------------|:---------------------------|:------------------------------------------------|
| alpha=0.000, beta=1 | <a href='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/interpolated10.png'><img width='200' src='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/interpolated10.png' /></a> | <a href='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/resurface10.png'><img width='200' src='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/resurface10.png' /></a> |
| alpha=0.111, beta=1 | <a href='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/interpolated11.png'><img width='200' src='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/interpolated11.png' /></a> | <a href='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/resurface11.png'><img width='200' src='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/resurface11.png' /></a> |
| alpha=0.222, beta=1 | <a href='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/interpolated12.png'><img width='200' src='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/interpolated12.png' /></a> | <a href='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/resurface12.png'><img width='200' src='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/resurface12.png' /></a> |
| alpha=0.333, beta=1 | <a href='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/interpolated13.png'><img width='200' src='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/interpolated13.png' /></a> | <a href='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/resurface13.png'><img width='200' src='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/resurface13.png' /></a> |
| alpha=0.444, beta=1 | <a href='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/interpolated14.png'><img width='200' src='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/interpolated14.png' /></a> | <a href='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/resurface14.png'><img width='200' src='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/resurface14.png' /></a> |
| alpha=0.556, beta=1 | <a href='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/interpolated15.png'><img width='200' src='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/interpolated15.png' /></a> | <a href='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/resurface15.png'><img width='200' src='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/resurface15.png' /></a> |
| alpha=0.667, beta=1 | <a href='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/interpolated16.png'><img width='200' src='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/interpolated16.png' /></a> | <a href='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/resurface16.png'><img width='200' src='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/resurface16.png' /></a> |
| alpha=0.778, beta=1 | <a href='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/interpolated17.png'><img width='200' src='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/interpolated17.png' /></a> | <a href='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/resurface17.png'><img width='200' src='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/resurface17.png' /></a> |
| alpha=0.889, beta=1 | <a href='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/interpolated18.png'><img width='200' src='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/interpolated18.png' /></a> | <a href='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/resurface18.png'><img width='200' src='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/resurface18.png' /></a> |
| alpha=1.000, beta=1 | <a href='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/interpolated19.png'><img width='200' src='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/interpolated19.png' /></a> | <a href='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/resurface19.png'><img width='200' src='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/resurface19.png' /></a> |

### Interpolation Along Edge A-C ###
For the grid cell edge in which alpha = 0, the following table shows 10 interpolation steps with 2 being at the endpoints (beta = 0 and beta = 1).

| Interpolation Coordinates | Displacement Interpolation | Quantile Interpolation & Surface Reconstruction |
|:--------------------------|:---------------------------|:------------------------------------------------|
| alpha=0, beta=0.000 | <a href='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/interpolated20.png'><img width='200' src='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/interpolated20.png' /></a> | <a href='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/resurface20.png'><img width='200' src='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/resurface20.png' /></a> |
| alpha=0, beta=0.111 | <a href='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/interpolated21.png'><img width='200' src='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/interpolated21.png' /></a> | <a href='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/resurface21.png'><img width='200' src='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/resurface21.png' /></a> |
| alpha=0, beta=0.222 | <a href='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/interpolated22.png'><img width='200' src='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/interpolated22.png' /></a> | <a href='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/resurface22.png'><img width='200' src='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/resurface22.png' /></a> |
| alpha=0, beta=0.333 | <a href='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/interpolated23.png'><img width='200' src='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/interpolated23.png' /></a> | <a href='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/resurface23.png'><img width='200' src='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/resurface23.png' /></a> |
| alpha=0, beta=0.444 | <a href='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/interpolated24.png'><img width='200' src='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/interpolated24.png' /></a> | <a href='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/resurface24.png'><img width='200' src='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/resurface24.png' /></a> |
| alpha=0, beta=0.556 | <a href='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/interpolated25.png'><img width='200' src='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/interpolated25.png' /></a> | <a href='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/resurface25.png'><img width='200' src='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/resurface25.png' /></a> |
| alpha=0, beta=0.667 | <a href='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/interpolated26.png'><img width='200' src='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/interpolated26.png' /></a> | <a href='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/resurface26.png'><img width='200' src='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/resurface26.png' /></a> |
| alpha=0, beta=0.778 | <a href='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/interpolated27.png'><img width='200' src='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/interpolated27.png' /></a> | <a href='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/resurface27.png'><img width='200' src='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/resurface27.png' /></a> |
| alpha=0, beta=0.889 | <a href='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/interpolated28.png'><img width='200' src='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/interpolated28.png' /></a> | <a href='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/resurface28.png'><img width='200' src='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/resurface28.png' /></a> |
| alpha=0, beta=1.000 | <a href='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/interpolated29.png'><img width='200' src='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/interpolated29.png' /></a> | <a href='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/resurface29.png'><img width='200' src='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/resurface29.png' /></a> |

### Interpolation Along Edge B-D ###
For the grid cell edge in which alpha = 1, the following table shows 10 interpolation steps with 2 being at the endpoints (beta = 0 and beta = 1).

| Interpolation Coordinates | Displacement Interpolation | Quantile Interpolation & Surface Reconstruction |
|:--------------------------|:---------------------------|:------------------------------------------------|
| alpha=1, beta=0.000 | <a href='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/interpolated30.png'><img width='200' src='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/interpolated30.png' /></a> | <a href='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/resurface30.png'><img width='200' src='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/resurface30.png' /></a> |
| alpha=1, beta=0.111 | <a href='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/interpolated31.png'><img width='200' src='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/interpolated31.png' /></a> | <a href='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/resurface31.png'><img width='200' src='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/resurface31.png' /></a> |
| alpha=1, beta=0.222 | <a href='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/interpolated32.png'><img width='200' src='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/interpolated32.png' /></a> | <a href='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/resurface32.png'><img width='200' src='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/resurface32.png' /></a> |
| alpha=1, beta=0.333 | <a href='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/interpolated33.png'><img width='200' src='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/interpolated33.png' /></a> | <a href='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/resurface33.png'><img width='200' src='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/resurface33.png' /></a> |
| alpha=1, beta=0.444 | <a href='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/interpolated34.png'><img width='200' src='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/interpolated34.png' /></a> | <a href='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/resurface34.png'><img width='200' src='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/resurface34.png' /></a> |
| alpha=1, beta=0.556 | <a href='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/interpolated35.png'><img width='200' src='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/interpolated35.png' /></a> | <a href='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/resurface35.png'><img width='200' src='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/resurface35.png' /></a> |
| alpha=1, beta=0.667 | <a href='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/interpolated36.png'><img width='200' src='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/interpolated36.png' /></a> | <a href='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/resurface36.png'><img width='200' src='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/resurface36.png' /></a> |
| alpha=1, beta=0.778 | <a href='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/interpolated37.png'><img width='200' src='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/interpolated37.png' /></a> | <a href='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/resurface37.png'><img width='200' src='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/resurface37.png' /></a> |
| alpha=1, beta=0.889 | <a href='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/interpolated38.png'><img width='200' src='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/interpolated38.png' /></a> | <a href='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/resurface38.png'><img width='200' src='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/resurface38.png' /></a> |
| alpha=1, beta=1.000 | <a href='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/interpolated39.png'><img width='200' src='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/interpolated39.png' /></a> | <a href='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/resurface39.png'><img width='200' src='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/resurface39.png' /></a> |

# Interpolation To The Grid Cell Center #
An additional interpolation was performed at the grid cell's center (alpha = 0.5 and beta = 0.5).  This is an interpolation of all four distributions rather than a pair of distributions.

| Interpolation Coordinates | Displacement Interpolation | Quantile Interpolation & Surface Reconstruction |
|:--------------------------|:---------------------------|:------------------------------------------------|
| alpha=0.5, beta=0.5 | <a href='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/interpolated40.png'><img width='200' src='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/interpolated40.png' /></a> | <a href='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/resurface40.png'><img width='200' src='https://displacement-interpolation-perf-analysis.googlecode.com/git/visualization/temp/resurface40.png' /></a> |

# Timings #
The time was recorded throughout the interpolations, both in terms of wall-clock time and processor clock time.  More information about the computer which performed the interpolations will be provided soon.  The timings are divided into interpolations along each edge and a final interpolation to the grid cell center.

### Edge A-B Interpolation Timings ###
Displacement Interpolation:
  * **Construction of Probability Density A:**
    * wall-clock: 723ms
    * processor clock: 721ms
  * **Construction of Probability Density B:**
    * wall-clock: 721ms
    * processor clock: 721ms
  * **Precomputation:**
    * wall-clock: 67504821ms (~18.75 hours)
    * processor clock: 129435226ms (~35.95 hours)
  * **Average Interpolation (10 iterations):**
    * wall-clock: 70500.9ms (~1.18 minutes)
    * processor clock: 70489.0ms (~1.17 minutes)

Quantile Interpolation:
  * **Calculation of Cumulative Distribution A:**
    * wall-clock: 45988ms (~0.77 minutes)
    * processor clock: 45981ms (~0.77 minutes)
  * **Parameterizing Quantile Curves of Distribution A:**
    * wall-clock: 3ms
    * processor clock: 3ms
  * **Calculation of Cumulative Distribution B:**
    * wall-clock: 71214ms (~1.19 minutes)
    * processor clock: 71203ms (~1.19 minutes)
  * **Parameterizing Quantile Curves of Distribution B:**
    * wall-clock: 3ms
    * processor clock: 2ms
  * **Average Interpolation of Quantiles (10 iterations):**
    * wall-clock: 1.0ms
    * processor clock: 0.6ms
  * **Average Interpolant PDF Evaluation (10 iterations):**
    * wall-clock: 2255.5ms
    * processor clock: 2254.6ms
  * **Average PDF Surface Reconstruction (10 iterations):**
    * wall-clock: 319.1ms
    * processor clock: 317.7ms

### Edge C-D Interpolation Timings ###
Displacement Interpolation:
  * **Construction of Probability Density C:**
    * wall-clock: 722ms
    * processor clock: 722ms
  * **Construction of Probability Density D:**
    * wall-clock: 723ms
    * processor clock: 721ms
  * **Precomputation:**
    * wall-clock: 66008949ms (~18.34 hours)
    * processor clock: 129229168ms (~35.90 hours)
  * **Average Interpolation (10 iterations):**
    * wall-clock: 71675.6ms (~1.19 minutes)
    * processor clock: 71663.6ms (~1.19 minutes)

Quantile Interpolation:
  * **Calculation of Cumulative Distribution C:**
    * wall-clock: 46243ms (~0.77 minutes)
    * processor clock: 46236ms (~0.77 minutes)
  * **Parameterizing Quantile Curves of Distribution C:**
    * wall-clock: 3ms
    * processor clock: 3ms
  * **Calculation of Cumulative Distribution D:**
    * wall-clock: 70899ms (~1.18 minutes)
    * processor clock: 70887ms (~1.18 minutes)
  * **Parameterizing Quantile Curves of Distribution D:**
    * wall-clock: 3ms
    * processor clock: 3ms
  * **Average Interpolation of Quantiles (10 iterations):**
    * wall-clock: 1.0ms
    * processor clock: 0.7ms
  * **Average Interpolant PDF Evaluation (10 iterations):**
    * wall-clock: 2255.4ms
    * processor clock: 2254.8ms
  * **Average PDF Surface Reconstruction (10 iterations):**
    * wall-clock: 332.0ms
    * processor clock: 330.2ms

### Edge A-C Interpolation Timings ###
Displacement Interpolation:
  * **Construction of Probability Density A:**
    * wall-clock: 723ms
    * processor clock: 721ms
  * **Construction of Probability Density C:**
    * wall-clock: 722ms
    * processor clock: 722ms
  * **Precomputation:**
    * wall-clock: 68915728ms (~19.14 hours)
    * processor clock: 132406226ms (~36.78 hours)
  * **Average Interpolation (10 iterations):**
    * wall-clock: 71784.3ms (~1.20 minutes)
    * processor clock: 71772.0ms (~1.20 minutes)

Quantile Interpolation:
  * **Calculation of Cumulative Distribution A:**
    * wall-clock: 45988ms (~0.77 minutes)
    * processor clock: 45981ms (~0.77 minutes)
  * **Parameterizing Quantile Curves of Distribution A:**
    * wall-clock: 3ms
    * processor clock: 3ms
  * **Calculation of Cumulative Distribution C:**
    * wall-clock: 46243ms (~0.77 minutes)
    * processor clock: 46236ms (~0.77 minutes)
  * **Parameterizing Quantile Curves of Distribution C:**
    * wall-clock: 3ms
    * processor clock: 3ms
  * **Average Interpolation of Quantiles (10 iterations):**
    * wall-clock: 1.0ms
    * processor clock: 0.6ms
  * **Average Interpolant PDF Evaluation (10 iterations):**
    * wall-clock: 2255.3ms
    * processor clock: 2254.7ms
  * **Average PDF Surface Reconstruction (10 iterations):**
    * wall-clock: 322.6ms
    * processor clock: 321.1ms

### Edge B-D Interpolation Timings ###
Displacement Interpolation:
  * **Construction of Probability Density B:**
    * wall-clock: 721ms
    * processor clock: 721ms
  * **Construction of Probability Density D:**
    * wall-clock: 723ms
    * processor clock: 721ms
  * **Precomputation:**
    * wall-clock: 63788491ms (~17.72 hours)
    * processor clock: 126291064ms (~35.08 hours)
  * **Average Interpolation (10 iterations):**
    * wall-clock: 70629.1ms (~1.18 minutes)
    * processor clock: 70617.1ms (~1.18 minutes)

Quantile Interpolation:
  * **Calculation of Cumulative Distribution B:**
    * wall-clock: 71214ms (~1.19 minutes)
    * processor clock: 71203ms (~1.19 minutes)
  * **Parameterizing Quantile Curves of Distribution B:**
    * wall-clock: 3ms
    * processor clock: 2ms
  * **Calculation of Cumulative Distribution D:**
    * wall-clock: 70899ms (~1.18 minutes)
    * processor clock: 70887ms (~1.18 minutes)
  * **Parameterizing Quantile Curves of Distribution D:**
    * wall-clock: 3ms
    * processor clock: 3ms
  * **Average Interpolation of Quantiles (10 iterations):**
    * wall-clock: 1.0ms
    * processor clock: 0.9ms
  * **Average Interpolant PDF Evaluation (10 iterations):**
    * wall-clock: 2255.4ms
    * processor clock: 2254.6ms
  * **Average PDF Surface Reconstruction (10 iterations):**
    * wall-clock: 327.9ms
    * processor clock: 326.5ms

### Grid Cell Center Interpolation Timings ###
Displacement Interpolation:
  * **Construction of Probability Density A:**
    * wall-clock: 723ms
    * processor clock: 721ms
  * **Construction of Probability Density B:**
    * wall-clock: 721ms
    * processor clock: 721ms
  * **Construction of Probability Density C:**
    * wall-clock: 722ms
    * processor clock: 722ms
  * **Construction of Probability Density D:**
    * wall-clock: 723ms
    * processor clock: 721ms
  * **Find Halfway-Interpolated Distribution on Edge A-B:**
    * wall-clock: 70394ms (~1.17 minutes)
    * processor clock: 70384ms (~1.17 minutes)
  * **Find Halfway-Interpolated Distribution on Edge C-D:**
    * wall-clock: 71974ms (~1.20 minutes)
    * processor clock: 71963ms (~1.20 minutes)
  * **Precomputation:**
    * wall-clock: 52125422ms (~14.48 hours)
    * processor clock: 63340719ms (~17.59 hours)
  * **Interpolation:**
    * wall-clock: 45927ms (~0.77 minutes)
    * processor clock: 45919ms (~0.77 minutes)

Quantile Interpolation:
  * **Calculation of Cumulative Distribution A:**
    * wall-clock: 45988ms (~0.77 minutes)
    * processor clock: 45981ms (~0.77 minutes)
  * **Parameterizing Quantile Curves of Distribution A:**
    * wall-clock: 3ms
    * processor clock: 3ms
  * **Calculation of Cumulative Distribution B:**
    * wall-clock: 71214ms (~1.19 minutes)
    * processor clock: 71203ms (~1.19 minutes)
  * **Parameterizing Quantile Curves of Distribution B:**
    * wall-clock: 3ms
    * processor clock: 2ms
  * **Calculation of Cumulative Distribution C:**
    * wall-clock: 46243ms (~0.77 minutes)
    * processor clock: 46236ms (~0.77 minutes)
  * **Parameterizing Quantile Curves of Distribution C:**
    * wall-clock: 3ms
    * processor clock: 3ms
  * **Calculation of Cumulative Distribution D:**
    * wall-clock: 70899ms (~1.18 minutes)
    * processor clock: 70887ms (~1.18 minutes)
  * **Parameterizing Quantile Curves of Distribution D:**
    * wall-clock: 3ms
    * processor clock: 3ms
  * **Interpolation of Quantiles:**
    * wall-clock: 1ms
    * processor clock: ~0ms
  * **Interpolant PDF Evaluation:**
    * wall-clock: 2255ms
    * processor clock: 2255ms
  * **PDF Surface Reconstruction:**
    * wall-clock: 312ms
    * processor clock: 311ms