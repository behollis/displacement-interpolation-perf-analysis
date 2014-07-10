import sys

import numpy as np
from scipy import stats

grid_density = 50
if (len(sys.argv) > 2: grid_density = int(sys.argv[2])

filename = "probability"
if len(sys.argv) > 3: filename = sys.argv[3]

def error(message):
	print "Error: " + message
	exit()

def writeData1D(arr, minX, maxX):
	out_file = open(filename, 'w')

	token_dimension = "%d" % dimensions
	out_file.write(token_dimension + "\n")

	token_min = "%f" % minX
	token_max = "%f" % maxX
	out_file.write(token_min + " " + token_max + "\n")

	for i in range(len(arr)):
		token_weight = "%f" % arr[i]
		out_file.write(token_weight + "\n")

	out_file.close()

def writeData2D(arr, minX, maxX, minY, maxY):
	out_file = open(filename, 'w')

	token_dimension = "%d" % dimensions
	out_file.write(token_dimension + "\n")

	token_min = "%f" % minX
	token_max = "%f" % maxX
	out_file.write(token_min + " " + token_max + "\n")

	token_min = "%f" % minY
	token_max = "%f" % maxY
	out_file.write(token_min + " " + token_max + "\n")

	for i in range(len(arr)):
		for j in range(len(arr[i])):
			if j != 0: out_file.write(" ")

			token_weight = "%f" % arr[i][j]
			out_file.write(token_weight)
		if i != len(arr) - 1: out_file.write("\n")

	out_file.close()

dimensions = 0
inputX = []
inputY = []

if len(sys.argv) <= 1: error("must provide data file")
in_file = open(sys.argv[1], 'r')

for line in in_file.readlines():
	tokens = line.split(' ')

	if dimensions == 0:
		dimensions = len(tokens)

	if dimensions != len(tokens):
		error("inconsistent dimensions")

	if dimensions < 1:
		error("dimensions cannot be determined")

	if dimensions >= 1:
		inputX.append(float(tokens[0]))

	if dimensions >= 2:
		inputY.append(float(tokens[1]))

	if dimensions > 2:
		error("number of dimensions currently unsupported")

in_file.close()

density = grid_density * 1j
minX = min(inputX)
maxX = max(inputX)

if dimensions == 1:
	gridX = np.mgrid[minX:maxX:density]
	kernel = stats.gaussian_kde(inputX)
	output = np.reshape(kernel(gridX).T, gridX.shape)
	writeData1D(output, minX, maxX)

if dimensions == 2:
	minY = min(inputY)
	maxY = max(inputY)

	gridX, gridY = np.mgrid[minX:maxX:density, minY:maxY:density]
	positions = np.vstack([gridX.ravel(), gridY.ravel()])
	values = np.vstack([inputX, inputY])
	kernel = stats.gaussian_kde(values)
	output = np.reshape(kernel(positions).T, gridX.shape)
	writeData2D(output, minX, maxX, minY, maxY)

