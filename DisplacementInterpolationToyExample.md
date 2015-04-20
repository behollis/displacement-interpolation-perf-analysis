# Introduction #

The displacement interpolation paper web page ([http://www.cs.ubc.ca/nest/imager/tr/2011/DisplacementInterpolation/](http://www.cs.ubc.ca/nest/imager/tr/2011/DisplacementInterpolation/)) provides a toy example which shows the interpolation of a square into a circle.  This page presents both timings and visualizations of this program.


# Timing #

The timing was performed on the following platform:
  * Ubuntu 14.04 LTS (64-bit)
  * running on an external harddrive via USB
  * 2GB of RAM
  * Intel Core 2 duo CPU E4500 @ 2.20GHz (x2 cores)

**Note:** previous timing records have been replaced to account for the updated platform OS and the use of pthreads on Ubuntu.

## Results ##

  * Trial 1:
    * Time of Day:
      * Precomputation Time: 81877ms
      * Average Interpolation Time: 1250.68ms (50 iterations)
    * CPU clock time:
      * Precompuation Time: 151818ms
      * Average Interpolation Time: 1250.02ms (50 iterations)

  * Trial 2:
    * Time of Day:
      * Precomputation Time: 81942ms
      * Average Interpolation Time: 1285.7ms (50 iterations)
    * CPU clock time:
      * Precompuation Time: 151927ms
      * Average Interpolation Time: 1284.94ms (50 iterations)

  * Trial 3:
    * Time of Day:
      * Precomputation Time: 81801ms
      * Average Interpolation Time: 1250.68ms (50 iterations)
    * CPU clock time:
      * Precompuation Time: 151836ms
      * Average Interpolation Time: 1249.98ms (50 iterations)

  * Trial 4:
    * Time of Day:
      * Precomputation Time: 81854ms
      * Average Interpolation Time: 1251.26ms (50 iterations)
    * CPU clock time:
      * Precompuation Time: 151855ms
      * Average Interpolation Time: 1250.6ms (50 iterations)

  * Trial 5:
    * Time of Day:
      * Precomputation Time: 81833ms
      * Average Interpolation Time: 1251.26ms (50 iterations)
    * CPU clock time:
      * Precompuation Time: 151851ms
      * Average Interpolation Time: 1250.58ms (50 iterations)

# Visualization #

Graphs produced with the help of matplotlib can be found in the repository in the following location: [https://code.google.com/p/displacement-interpolation-perf-analysis/source/browse/timing/images/](https://code.google.com/p/displacement-interpolation-perf-analysis/source/browse/timing/images/).

The toy example uses displacement interpolation to morph a square shape to a circle shape.  The square is produced by assigning a set of points a weight of 1 (as is the circle).  To interpolate, an alpha value is used to go somewhere between the square (alpha of 0) and the circle (alpha of 1).  The images in the repository are at alpha values of 0, 0.25, 0.5, 0.75, and 1:

| <a href='https://displacement-interpolation-perf-analysis.googlecode.com/git/timing/images/alpha0.png'><img src='https://displacement-interpolation-perf-analysis.googlecode.com/git/timing/images/alpha0.png' width='200></a'> <table><thead><th> <a href='https://displacement-interpolation-perf-analysis.googlecode.com/git/timing/images/alpha025.png'><img src='https://displacement-interpolation-perf-analysis.googlecode.com/git/timing/images/alpha025.png' width='200></a'> </th><th> <a href='https://displacement-interpolation-perf-analysis.googlecode.com/git/timing/images/alpha05.png'><img src='https://displacement-interpolation-perf-analysis.googlecode.com/git/timing/images/alpha05.png' width='200></a'> </th><th> <a href='https://displacement-interpolation-perf-analysis.googlecode.com/git/timing/images/alpha075.png'><img src='https://displacement-interpolation-perf-analysis.googlecode.com/git/timing/images/alpha075.png' width='200></a'> </th><th> <a href='https://displacement-interpolation-perf-analysis.googlecode.com/git/timing/images/alpha1.png'><img src='https://displacement-interpolation-perf-analysis.googlecode.com/git/timing/images/alpha1.png' width='200></a'> </th></thead><tbody></tbody></table>

Each intersection of graph lines represents an equally spaced location within the unit square.  The height of the points represents interpolatable values at these locations.