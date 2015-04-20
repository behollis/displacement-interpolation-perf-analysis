# Introduction #

As of now, marching squares is being run as a separate program, gen\_quantile\_points.py. CDF data is exported from qInterpolate, passed through gen\_quantile\_points.py, which produces a set of quantile points that is then imported back into qInterpolate for curve generation and interpolation. Since the marching squares implementation used is from VTK, it should not be too difficult to integrate into qInterpolate.


# Image Comparison #

The following images were generated at a low resolution to speed up testing. Some of the images use different bounds which makes it kind of difficult to compare, but I'm working on fixing this.

  * QUANTILE\_Q = 25
  * DIV = 50
  * NUM\_PTS = 150

Curves A

Simple Binning:

<img width='500' src='https://displacement-interpolation-perf-analysis.googlecode.com/git-history/marching-squares/visualization/temp/marching-squares/curvesAOriginal.png'>

Marching Squares:<br>
<br>
<img width='500' src='https://displacement-interpolation-perf-analysis.googlecode.com/git-history/marching-squares-integration/visualization/temp/marching-squares/curvesAMarching.png'>


Curves B<br>
<br>
Simple Binning:<br>
<br>
<img width='500' src='https://displacement-interpolation-perf-analysis.googlecode.com/git-history/marching-squares/visualization/temp/marching-squares/curvesBOriginal.png'>

Marching Squares:<br>
<br>
<img width='500' src='https://displacement-interpolation-perf-analysis.googlecode.com/git-history/marching-squares-integration/visualization/temp/marching-squares/curvesBMarching.png'>


Curves C<br>
<br>
Simple Binning:<br>
<br>
<img width='500' src='https://displacement-interpolation-perf-analysis.googlecode.com/git-history/marching-squares/visualization/temp/marching-squares/curvesCOriginal.png'>

Marching Squares:<br>
<br>
<img width='500' src='https://displacement-interpolation-perf-analysis.googlecode.com/git-history/marching-squares-integration/visualization/temp/marching-squares/curvesCMarching.png'>


Curves D<br>
<br>
Simple Binning:<br>
<br>
<img width='500' src='https://displacement-interpolation-perf-analysis.googlecode.com/git-history/marching-squares/visualization/temp/marching-squares/curvesDOriginal.png'>

Marching Squares:<br>
<br>
<img width='500' src='https://displacement-interpolation-perf-analysis.googlecode.com/git-history/marching-squares-integration/visualization/temp/marching-squares/curvesDMarching.png'>