import sys

import numpy as np

filename = "vectors"
if len(sys.argv) > 2: filename = sys.argv[2]

mean = [0, 1]
covariance = [[1, 0], [0, 1]]
count = 100
if len(sys.argv) > 1: count = int(sys.argv[1])

vectorX, vectorY = np.random.multivariate_normal(mean, covariance, count).T

out_file = open("vectors", 'w')

for i in range(count):
	token_x = "%f" % vectorX[i]
	token_y = "%f" % vectorY[i]
	out_file.write(token_x + " " + token_y + "\n")

out_file.close()

