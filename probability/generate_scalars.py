import sys

import numpy as np

filename = "scalars"
if len(sys.argv) > 2: filename = sys.argv[2]

mean = [1]
covariance = [[1]]
count = 100
if len(sys.argv) > 1: count = int(sys.argv[1])

scalars = np.random.multivariate_normal(mean, covariance, count)

out_file = open(filename, 'w')

for i in range(count):
	token = "%f" % scalars[i]
	out_file.write(token + "\n")

out_file.close()

