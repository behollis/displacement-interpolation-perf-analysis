import sys

import numpy as np

filename = "scalars"
if len(sys.argv) > 2: filename = sys.argv[2]

meanA = [2]
meanB = [-2]
covarianceA = [[1]]
covarianceB = [[1]]
count = 100
if len(sys.argv) > 1: count = int(sys.argv[1])

scalarsA = np.random.multivariate_normal(meanA, covarianceA, count/2)
scalarsB = np.random.multivariate_normal(meanB, covarianceB, count/2)

scalars = np.append(scalarsA, scalarsB)

out_file = open(filename, 'w')

for i in range(count):
	token = "%f" % scalars[i]
	out_file.write(token + "\n")

out_file.close()

