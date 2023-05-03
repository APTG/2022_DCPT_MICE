import numpy as np
from scipy.interpolate import CubicSpline

d = np.loadtxt("kQ.dat")

cs1 = CubicSpline(d[1:, 0], d[1:, 1])
cs2 = CubicSpline(d[:, 0], d[:, 2])

rres1 = (2.10, 2.10, 2.10, 2.10, 1.70, 1.30, 0.90, 0.50, 0.10, -0.30, -0.70, 1.70, 1.70, 1.70, 1.70)
rres2 = (7.80, 6.80, 5.80, 4.80, 3.80, 3.30, 2.80, 2.30, 1.80, 1.30, 0.80, 0.30, 0.60, 0.40, 0.50, 0.10, 0.10, -0.20)

result1 = np.column_stack([rres1, cs1(rres1)])
result2 = np.column_stack([rres2, cs2(rres2)])

np.savetxt('kQ_semiflex.dat', result1, fmt="%.4f")
np.savetxt('kQ_advmarkus.dat', result2, fmt="%.4f")
