import sys

from mpl_toolkits.mplot3d import axes3d
import matplotlib.pyplot as plt
import numpy as np

fig = plt.figure()
ax = fig.add_subplot(1, 1, 1, projection='3d')

#re-create positions of points used during interpolation phase

W = 50

X = []
for i in range(W):
	temp = []
	for j in range(W):
		temp.append(i / (W + 0.0))
	X.append(temp)

Y = []
for i in range(W):
	temp = []
	for j in range(W):
		temp.append(j / (W + 0.0))
	Y.append(temp)

#read data file produced from saveFile function

in_file = open(sys.argv[1], 'r');

Z = []
for line in in_file.readlines():
	temp = []
	for token in line.split(' '):
		if "\n" in token:
			break
		temp.append(float(token))
	Z.append(temp)

in_file.close()

ax.plot_wireframe(X, Y, Z)
plt.show()

