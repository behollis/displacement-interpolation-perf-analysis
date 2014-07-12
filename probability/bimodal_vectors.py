import sys

import numpy as np

filename = "vectors"
if len(sys.argv) > 2: filename = sys.argv[2]

meanA = [2, 1]
meanB = [-2, -1]
covarianceA = [[1, 0], [0, 1]]
covarianceB = [[1.5, 0], [0, 1.5]]
count = 100
if len(sys.argv) > 1: count = int(sys.argv[1])

vectorAX, vectorAY = np.random.multivariate_normal(meanA, covarianceA, 3 * count / 5).T
vectorBX, vectorBY = np.random.multivariate_normal(meanB, covarianceB, 2 * count / 5).T

vectorX = np.append(vectorAX, vectorBX)
vectorY = np.append(vectorAY, vectorBY)

out_file = open(filename, 'w')

for i in range(count):
	token_x = "%f" % vectorX[i]
	token_y = "%f" % vectorY[i]
	out_file.write(token_x + " " + token_y + "\n")

out_file.close()

