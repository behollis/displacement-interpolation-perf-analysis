# Introduction #

Beyond just running the toy example provided by the paper, displacement interpolation is also capable of interpolating probability distributions formed from points in ensemble vector fields.  This page presents a method of accomplishing this task.

# Testing an Example #

In order to test this technique, I sampled vectors with the help of the <a href='http://docs.scipy.org/doc/numpy/reference/generated/numpy.random.multivariate_normal.html'>numpy.random.multivariate_normal</a> function in Python according to the following distributions:
  * _the first was a multivariate normal distribution with the following properties_:
**mean**:
|  0 |
|:---|
| -1 |

**covariance matrix**:
| 1 | 0 |
|:--|:--|
| 0 | 1 |

  * _the second was a bimodal multivariate normal distribution which used the following normal distributions and weights_:
**mean A**:
| 2 |
|:--|
| 1 |

**covariance matrix A**:
| 1 | 0 |
|:--|:--|
| 0 | 1 |

**percentage of samples taken from distribution A:** 60%

**mean B**:
| -2 |
|:---|
| -1 |

**covariance matrix B**:
| 1.5 |  0  |
|:----|:----|
|  0  | 1.5 |

**percentage of samples taken from distribution B:** 40%

# Creating Probability Distributions #

Displacement Interpolation can take parts of two probability distribution functions and interpolate to form an intermediate distribution.  Since ensemble vector fields house the possible outcome vectors at each point, one needs to pass the outcome vectors to a kernel density estimation technique.  I used the <a href='http://docs.scipy.org/doc/scipy/reference/generated/scipy.stats.gaussian_kde.html'>scipy.stats.gaussian_kde</a> function in Python to convert a set of vector samples into discrete parts of a probability distribution function.

# Interpolation #

By taking the discrete parts of two probability distribution functions, the Interpolator class from the displacement interpolation paper can form the discrete parts of the interpolated probability distribution.  The discrete parts consist of coordinates as input to the probability distribution function and the output of the function at that location.

# Graphing #

To simplify the graphing of probability distribution functions, the discrete parts of the functions use coordinates aligned to a rectangular grid.  The only information needed to graph the function are the rectangular boundaries, the density of the grid (same for both dimensions), and the outputs/weights of the function at the grid locations.

# Graphing the Example #

After finding approximate probability distribution functions of the example data (normal and bimodal distributions of vectors), discrete parts of the two functions are interpolated at several alpha values:

| alpha = 0.0 | alpha = 0.2 | alpha = 0.4 |
|:------------|:------------|:------------|
| <a href='https://displacement-interpolation-perf-analysis.googlecode.com/git/probability/images/alpha00.png'><img width='200' src='https://displacement-interpolation-perf-analysis.googlecode.com/git/probability/images/alpha00.png' /></a> | <a href='https://displacement-interpolation-perf-analysis.googlecode.com/git/probability/images/alpha02.png'><img width='200' src='https://displacement-interpolation-perf-analysis.googlecode.com/git/probability/images/alpha02.png' /></a> | <a href='https://displacement-interpolation-perf-analysis.googlecode.com/git/probability/images/alpha04.png'><img width='200' src='https://displacement-interpolation-perf-analysis.googlecode.com/git/probability/images/alpha04.png' /></a>|
| alpha = 0.6 | alpha = 0.8 | alpha = 1.0 |
| <a href='https://displacement-interpolation-perf-analysis.googlecode.com/git/probability/images/alpha06.png'><img width='200' src='https://displacement-interpolation-perf-analysis.googlecode.com/git/probability/images/alpha06.png' /></a> | <a href='https://displacement-interpolation-perf-analysis.googlecode.com/git/probability/images/alpha08.png'><img width='200' src='https://displacement-interpolation-perf-analysis.googlecode.com/git/probability/images/alpha08.png' /></a> | <a href='https://displacement-interpolation-perf-analysis.googlecode.com/git/probability/images/alpha10.png'><img width='200' src='https://displacement-interpolation-perf-analysis.googlecode.com/git/probability/images/alpha10.png' /></a> |

# Timing the Example #

In order to measure performance, timings were taken of displacement interpolation running with the example data.  Both input probability distributions had a resolution of 85x85 and were interpolated to various 85x85 distributions.

**Note**: clock timings of precomputation experienced overflow and return nonsensical values.  They are not displayed here.

  * Trial 1:
    * Time of Day:
      * Precomputation Time: 4671279ms (~78 minutes)
      * Average Interpolation Time: 17196.14ms (50 iterations)
    * CPU clock time:
      * Average Interpolation Time: 17190.22ms (50 iterations)

  * Trial 2:
    * Time of Day:
      * Precomputation Time: 4602413ms (~77 minutes)
      * Average Interpolation Time: 16982.04ms (50 iterations)
    * CPU clock time:
      * Average Interpolation Time: 16975.88ms (50 iterations)

  * Trial 3:
    * Time of Day:
      * Precomputation Time: 4654581ms (~78 minutes)
      * Average Interpolation Time: 17005.2ms (50 iterations)
    * CPU clock time:
      * Average Interpolation Time: 16998.9ms (50 iterations)

  * Trial 4:
    * Time of Day:
      * Precomputation Time: 4649856ms (~77 minutes)
      * Average Interpolation Time: 16975.42ms (50 iterations)
    * CPU clock time:
      * Average Interpolation Time: 16969.04ms (50 iterations)

  * Trial 5:
    * Time of Day:
      * Precomputation Time: 4612223ms (~77 minutes)
      * Average Interpolation Time: 17041.3ms (50 iterations)
    * CPU clock time:
      * Average Interpolation Time: 17034.2ms (50 iterations)