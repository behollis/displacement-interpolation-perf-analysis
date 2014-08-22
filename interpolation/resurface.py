import sys
import time

import numpy as np
from scipy.interpolate import LinearNDInterpolator, NearestNDInterpolator

in_file = open(sys.argv[1], 'r')
points = []
values = []

while True:
	line = in_file.readline()
	if not line: break

	tokens = line.split(' ')
	x = float(tokens[0])
	y = float(tokens[1])
	z = float(tokens[2])

	points.append([x, y])
	values.append(z)

in_file.close()

dim_file = open("interpolated0", 'r') #assumed to exist

line = dim_file.readline()

line = dim_file.readline()
tokens = line.split(' ')
minX = float(tokens[0])
maxX = float(tokens[1])

line = dim_file.readline()
tokens = line.split(' ')
minY = float(tokens[0])
maxY = float(tokens[1])

line = dim_file.readline()
tokens = line.split(' ')
dim = len(tokens)

dim_file.close()

density = dim * 1j

X, Y = np.mgrid[minX:maxX:density, minY:maxY:density]
outPoints = np.array([X, Y]).transpose()

start = time.time()

interpolator = LinearNDInterpolator(points, values, fill_value=0.0)
Z = interpolator(outPoints)

print repr(time.time() - start)

out_file = open(sys.argv[2], 'w')

out_file.write("2\n")

token_min = "%f" % minX
token_max = "%f" % maxX
out_file.write(token_min + " " + token_max + "\n")

token_min = "%f" % minY
token_max = "%f" % maxY
out_file.write(token_min + " " + token_max + "\n")

for i in range(len(Z)):
	for j in range(len(Z[i])):
		if j != 0: out_file.write(" ")

		token_weight = "%f" % Z[j][i]
		out_file.write(token_weight)
	if i != len(Z) - 1: out_file.write("\n")

out_file.close()
