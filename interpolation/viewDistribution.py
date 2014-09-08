import sys

from mpl_toolkits.mplot3d import axes3d
import matplotlib.pyplot as plt

fig = plt.figure()
ax = fig.add_subplot(1, 1, 1, projection='3d')
ax.invert_xaxis()

in_file = open(sys.argv[1], 'r')

X = []
Y = []
Z = []

for line in in_file.readlines():
	tokens = line.split(' ')
	X.append(float(tokens[0]))
	Y.append(float(tokens[1]))
	Z.append(float(tokens[2]))

ax.scatter(X, Y, Z, s=0.1)
plt.show()

