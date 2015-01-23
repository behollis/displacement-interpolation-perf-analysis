#!/usr/bin/python

import sys
import time

import numpy as np
from scipy.interpolate import LinearNDInterpolator, NearestNDInterpolator

points = []
values = []

minX = 0
maxX = 0
minY = 0
maxY = 0
with open(sys.argv[1], 'r') as in_file:
    # read dimensions and ignore (assume to be 2)
    in_file.readline()
    # read min and max x
    tokens = in_file.readline().split(' ')
    minX = float(tokens[0])
    maxX = float(tokens[1])

    # read min and max y
    tokens = in_file.readline().split(' ')
    minY = float(tokens[0])
    maxY = float(tokens[1])

    lines = in_file.readlines()

    for i, line in enumerate(lines):
        row = line.split(' ')
        y = minY + float(i)/len(lines) * (maxY - minY)

        for j, value in enumerate(row):
            x = minX + float(j)/len(row) * (maxX - minX)

            points.append([x, y])
            values.append(float(value))

density = 100 * 1j

X, Y = np.mgrid[minX:maxX:density, minY:maxY:density]
outPoints = np.array([X, Y]).transpose()

interpolator = LinearNDInterpolator(points, values, fill_value=0.0)
Z = interpolator(outPoints)

print "2"
print "%f %f" % (minX, maxX)
print "%f %f" % (minY, maxY)

for i in range(len(Z)):
    print " ".join([str(x) for x in Z[i]])
