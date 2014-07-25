import sys

import matplotlib.pyplot as plt

fig = plt.figure()
ax = fig.add_subplot(1, 1, 1)

in_file = open(sys.argv[1], 'r')

X = []
Y = []

for line in in_file.readlines():
	tokens = line.split(' ')
	for i in range(len(tokens)/2):
		X.append(float(tokens[2*i+0]))
		Y.append(float(tokens[2*i+1]))

ax.scatter(X, Y, s=0.1)
#ax.plot(X, Y)
plt.show()

