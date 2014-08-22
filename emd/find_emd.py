import sys

from cv2 import *
import numpy as np

def readPoints(in_file):
	points = []

	line = in_file.readline()
	tokens = line.split(' ')

	if len(tokens) == 1:
		line = in_file.readline()
		tokens = line.split(' ')
		minX = float(tokens[0])
		maxX = float(tokens[1])

		line = in_file.readline()
		tokens = line.split(' ')
		minY = float(tokens[0])
		maxY = float(tokens[1])

		Z = []

		while True:
			line = in_file.readline()
			if not line: break
			temp = []
			for token in line.split(' '):
				temp.append(float(token))
			Z.append(temp)

		density = len(Z) * 1j
		X, Y = np.mgrid[minX:maxX:density, minY:maxY:density]

		for i in range(0, len(Z)):
			for j in range(0, len(Z[0])):
				temp = [(Z[i][j]), (X[i][j]), (Y[i][j])]
				points.append(temp)

	else:
		temp = [float(tokens[2]), float(tokens[0]), float(tokens[1])]
		points.append(temp)

		while True:
			line = in_file.readline()
			if not line: break

			tokens = line.split(' ')
			x = float(tokens[0])
			y = float(tokens[1])
			z = float(tokens[2])

			temp = [z, x, y]
			points.append(temp)

	return points

fileA = open(sys.argv[1], 'r')
distributionA = readPoints(fileA)

fileB = open(sys.argv[2], 'r')
distributionB = readPoints(fileB)

a = np.array(distributionA)
b = np.array(distributionB)

# Convert from numpy array to CV_32FC1 Mat
a64 = cv.fromarray(a)
a32 = cv.CreateMat(a64.rows, a64.cols, cv.CV_32FC1)
cv.Convert(a64, a32)

b64 = cv.fromarray(b)
b32 = cv.CreateMat(b64.rows, b64.cols, cv.CV_32FC1)
cv.Convert(b64, b32)

# Calculate Earth Mover's
print cv.CalcEMD2(a32,b32,cv.CV_DIST_L2)
