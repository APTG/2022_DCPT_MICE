import numpy as np
from scipy.interpolate import CubicSpline

d1 = np.loadtxt("Water0.txt", comments='*')
d2 = np.loadtxt("icru90.dat", comments='#')

e1 = d1[:, 0]  # old energy grid in MeV/nucl

hw2 = d1[:, 2]  # old data will be used to overwrite missing He high energy data

e2 = d2[:, 0]  # ICRU90 energy grid in MeV
ep = e1 * 1    # translate old energy grid MeV/nucl to MeV
eh = e1 * 4
ec = e1 * 12

# extract columns for protons, helium and carbon in liquid water
pw90 = d2[:, 9]
hw90 = d2[:, 12]
cw90 = d2[:, 15]

# splines are all in MeV
cs_p = CubicSpline(e2, pw90)
cs_h = CubicSpline(e2[:-8], hw90[:-8])
cs_h2 = CubicSpline(eh[-8:], hw2[-8:])  # interpolation of old high energy He data in MeV
cs_c = CubicSpline(e2, cw90)


# Build a new helium ion data set, containing the ICRU90 data, and use data from Water0.txt beyond ICRU90 energies.
hh = np.concatenate([cs_h(eh[:-8]), cs_h2(eh[-8:])])

# stack all columns in proper order: energy, proton, helium, lithium,...
result = np.column_stack([e1, cs_p(ep), hh, d1[:, 3:6], cs_c(ec), d1[:, 7:]])

np.savetxt('Water90.dat', result, fmt="%.4E")
