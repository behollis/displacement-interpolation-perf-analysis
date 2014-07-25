import numpy as np
from scipy import stats

def getKernelDensityEstimate(X, Y):
	values = np.vstack([X, Y])
	kernel = stats.gaussian_kde(values)
	return kernel

def calculateBoxIntegral(kernel, minX, minY, maxX, maxY):
	minP = [minX, minY]
	maxP = [maxX, maxY]
	integral = kernel.integrate_box(minP, maxP)
	return integral

def getDensitySurfaceValue(kernel, posX, posY):
	pos = [posX, posY]
	value = kernel.evaluate(pos)[0]
	return float(value)

