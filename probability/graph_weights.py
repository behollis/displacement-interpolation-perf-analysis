import sys

from mpl_toolkits.mplot3d import axes3d
import matplotlib.pyplot as plt
import numpy as np

fig = plt.figure()

in_file = open(sys.argv[1], 'r')

line = in_file.readline()
dimensions = int(line)
weights = []

line = in_file.readline()
tokens = line.split(' ')
minX = float(tokens[0])
maxX = float(tokens[1])

if dimensions == 1:
	while True:
		line = in_file.readline()
		if not line: break
		weights.append(float(line))

	print "density: " + repr(len(weights))

	ax = fig.add_subplot(1, 1, 1)

	density = len(weights) * 1j
	X = np.mgrid[minX:maxX:density]
	ax.plot(X, weights)
	

if dimensions == 2:
	line = in_file.readline()
	tokens = line.split(' ')
	minY = float(tokens[0])
	maxY = float(tokens[1])

	while True:
		line = in_file.readline()
		if not line: break
		temp = []
		for token in line.split(' '):
			temp.append(float(token))
		weights.append(temp)

	print "density: " + repr(len(weights))

	ax = fig.add_subplot(1, 1, 1, projection='3d')
	ax.invert_xaxis()
	density = len(weights) * 1j
	X, Y = np.mgrid[minX:maxX:density, minY:maxY:density]
	#ax.plot_wireframe(X, Y, weights)
	ax.plot_wireframe(X, Y, weights, rstride=4, cstride=4)

in_file.close()

plt.show()

