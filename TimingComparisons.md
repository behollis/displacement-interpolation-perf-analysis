# Introduction #

For this comparison test, both displacement interpolation and bivariate quantile interpolation were tasked with interpolating a normal distribution of 600 vectors to a bimodal distribution of 600 vectors.

The testing took place on the compute cluster campusrocks2 at UCSC.  Displacement interpolation was given two 100x100 grids of values representing the probability distribution functions to interpolate.  Bivariate quantile interpolation was directly given the 600 vector samples from both distributions and instructed to use a 100x100 grid when calculating the CDF.  An additional run of quantile interpolation was performed to show the change in timings at a higher CDF resolution with more quantile curves.

NOTE: For bivariate quantile interpolation, 150 points-per-curve was used.  These timings do not currently include surface interpolation.

# Timings #

Displacement Interpolation (100x100):
  * **Precomputation**: 11780018ms (~196 minutes)
  * **Precomputation(CPU clock)**: 21513795ms (~359 minutes)
  * **Average Interpolation**: 22791.2ms (10 iteration)
  * **Average Interpolation(CPU clock)**: 22786.6ms (10 iterations)

Bivariate Quantile Interpolation (100x100, 50-quantile):
  * **Precomputation**: 59954ms (~1 minute)
    * CDF calculation of distribution A: 23646ms
    * quantile parameterization of distribution A: 1ms
    * CDF calculation of distribution B: 36306ms
    * quantile parameterization of distribution B: 1ms
  * **Precomputation(CPU clock)**: 59944ms (~1 minute)
    * CDF calculation of distribution A: 23642ms
    * quantile parameterization of distribution A: 1ms
    * CDF calculation of distribution B: 36299ms
    * quantile parameterization of distribution B: 2ms
  * **Average Interpolation**: 544.3ms (10 iterations)
    * Average quantile interpolation: 0ms
    * Average PDF evaluation: 544.3ms
  * **Average Interpolation(CPU clock)**: 543.7ms (10 iterations)
    * Average quantile interpolation: 0ms
    * Average PDF evaluation: 543.7ms

Bivariate Quantile Interpolation (400x400, 200-quantile):
  * **Precomputation**: 1076026ms (~18 minutes)
    * CDF calculation of distribution A: 433567ms
    * quantile parameterization of distribution A: 30ms
    * CDF calculation of distribution B: 642399ms
    * quantile parameterization of distribution B: 30ms
  * **Precomputation(CPU clock)**: 1075845ms (~18 minutes)
    * CDF calculation of distribution A: 433497ms
    * quantile parameterization of distribution A: 28ms
    * CDF calculation of distribution B: 642291ms
    * quantile parameterization of distribution B: 29ms
  * **Average Interpolation**: 2655.8ms (10 iterations)
    * Average quantile interpolation: 4ms
    * Average PDF evaluation: 2651.8ms
  * **Average Interpolation(CPU clock)**: 2654.9ms (10 iterations)
    * Average quantile interpolation: 3.5ms
    * Average PDF evaluation: 2651.4ms