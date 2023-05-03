"""foobar"""

import os
import numpy as np
import matplotlib.pyplot as plt

#
# Output
#         Filename NB_Z_narrow_LET_water.bdo
#         Geo Z_narrow
#         Quantity DLET in_Water                  # __p1
#         Quantity DLET Primary in_Water
#         Quantity DLET Protons in_Water
#         Quantity TLET in_Water                  # __p4
#         Quantity TLET Primary in_Water
#         Quantity TLET Protons in_Water
#
# Output
#         Filename NB_Z_narrow_QEFF.bdo
#         Geo Z_narrow
#         Quantity DQEFF                          # __p1
#         Quantity DQEFF Primary
#         Quantity DQEFF Protons
#         Quantity TQEFF                          # __p4
#         Quantity TQEFF Primary
#         Quantity TQEFF Protons
rdir = "results/plan1"
fdw = "NB_Z_narrow_dose_water__p2.dat"
flw = ("NB_Z_narrow_LET_water__p1.dat",
       "NB_Z_narrow_LET_water__p2.dat",
       "NB_Z_narrow_LET_water__p3.dat",
       "NB_Z_narrow_LET_water__p4.dat",
       "NB_Z_narrow_LET_water__p5.dat",
       "NB_Z_narrow_LET_water__p6.dat")

fq = ("NB_Z_narrow_QEFF__p1.dat",
      "NB_Z_narrow_QEFF__p2.dat",
      "NB_Z_narrow_QEFF__p3.dat",
      "NB_Z_narrow_QEFF__p4.dat",
      "NB_Z_narrow_QEFF__p5.dat",
      "NB_Z_narrow_QEFF__p6.dat")

ftg = ("NB_target__p01.txt",
       "NB_target__p02.txt",
       "NB_target__p03.txt",
       "NB_target__p04.txt",
       "NB_target__p05.txt",
       "NB_target__p06.txt",
       "NB_target__p07.txt",
       "NB_target__p08.txt",
       "NB_target__p09.txt",
       "NB_target__p10.txt",
       "NB_target__p11.txt",
       "NB_target__p12.txt")

ftgw = ("NB_target_water__p1.txt",
        "NB_target_water__p2.txt",
        "NB_target_water__p3.txt",
        "NB_target_water__p4.txt",
        "NB_target_water__p5.txt",
        "NB_target_water__p6.txt")

ql = ("DQeff all", "DQeff prim", "DQeff prot", "TQeff all", "TQeff prim", "TQeff prot")
ll = ("DLETeff all", "DLET prim", "DLET prot", "TLET all", "TLET prim", "TLET prot")

path_ic_s = "../resources/measurements/20230426_Semiflex.dat"
path_ic_m = "../resources/measurements/20230428_AdvMarkus.dat"

ptv_z_nominal = (5.5, 8.5)
ptv_z = (5.5, 8.4)
z_max = 10.0  # cm
d_max = 100.0  # max y scale for dose in %
dq_max = 400
dl_max = 20

# ic_semiflex_zshift = -0.20625 # [cm] = -0.275 * 0.75 cm radius of sens.vol: 2.75 mm. 0.75 Palmans et al 2022.
# ic_semiflex_zshift = -0.175  # [cm] half of mean cord length: 4*r/pi * 0.5 = 1.75 mm
ic_semiflex_zshift = -0.12  # [cm] best fit
ic_semiflex_dscale = 1.008
ic_markus_dscale = 1.020

majticks = 5
minticks = majticks*2
ff = 1.1  # extend y axis by this factor to make it fit in frame

z_majticks = np.arange(0, z_max+1, z_max/majticks)
d_majticks = np.arange(0, d_max+1, d_max/majticks)
l_majticks = np.arange(0, dl_max+1, dl_max/majticks)
q_majticks = np.arange(0, dq_max+1, dq_max/majticks)

z_minticks = np.arange(0, z_max+1, z_max/minticks)
d_minticks = np.arange(0, d_max+1, d_max/minticks)
l_minticks = np.arange(0, dl_max+1, dl_max/minticks)
q_minticks = np.arange(0, dq_max+1, dq_max/minticks)

dw = np.loadtxt(os.path.join(rdir, fdw))
d_ic_s = np.loadtxt(path_ic_s)
d_ic_m = np.loadtxt(path_ic_m)

z = dw[:, 0]
z_ic_m = d_ic_m[:, 0]
z_ic_s = d_ic_s[:, 0] + ic_semiflex_zshift

dose_w = dw[:, 1]
dose_w_err = dw[:, 2]
dose_ic_m = d_ic_m[:, 1] * ic_markus_dscale
dose_ic_s = d_ic_s[:, 1] * ic_semiflex_dscale

fill_x = [ptv_z[0], ptv_z[1]]
fill_y = [d_max*ff, d_max*ff]

ptw_mean_d = dose_w[(z > ptv_z[0]) & (z < ptv_z[1])]
dnorm = 1.0 / ptw_mean_d.mean() * 100.0
dose_w_rel = dose_w * dnorm

let_mask = (dose_w_rel > 1.0)
z_lim = z[let_mask]

dlw = []
for i, fn in enumerate(flw):
    dlw.append(np.loadtxt(os.path.join(rdir, fn)))

dq = []
for i, fn in enumerate(fq):
    p = os.path.join(rdir, fn)
    dq.append(np.loadtxt(p))

dtg = []
for i, fn in enumerate(ftg):
    p = os.path.join(rdir, fn)
    dtg.append(np.loadtxt(p))

dtgw = []
for i, fn in enumerate(ftgw):
    p = os.path.join(rdir, fn)
    dtgw.append(np.loadtxt(p))

# ---------------------------------- Qeff plot
fig = plt.figure()
ax = fig.subplots()
ax.fill_between(fill_x, fill_y, 0, alpha=.2)

# nominal mouse leg positions
for i in range(8):
    mxx = [6.5+i*0.4 + 0.03, 6.5+(i+1)*0.4 - 0.03]
    myy = [103.0, 103.0]
    myy2 = [104.0, 104.0]
    ax.fill_between(mxx, myy, myy2, alpha=.2, color='r')
    ax.text(6.5+i*0.4+0.12, 105, str(i+1), alpha=0.2)

ax.grid(True)
ax.grid(which='minor', alpha=0.2)
# ax.tick_params(axis='x', which='minor')
ax.set_xlabel('Depth [cm]')
ax.set_xticks(z_majticks)
ax.set_xticks(z_minticks, minor=True)
ax.set_xlim([0, z_max])

ax.set_ylabel('Relative dose [%]')
ax.set_ylim([0, d_max*ff])
ax.set_yticks(d_majticks)
ax.set_yticks(d_minticks, minor=True)
ax.plot(z, dose_w_rel, linewidth=0.5, label="Dose")

ax2 = ax.twinx()
ax2.set_ylabel('Qeff [nil]')
ax2.set_ylim([0, dq_max*ff])
ax2.set_yticks(q_majticks)
ax2.set_yticks(q_minticks, minor=True)
ax2.grid(which='minor', alpha=0.2)

for i, y in enumerate(dq):
    ax2.plot(z_lim, y[:, 1][let_mask], label=ql[i])
fig.legend(loc=(0.15, 0.6))
fig.savefig("proton_qeff.png")

# LET

# ---------------------------------- LET plot
fig = plt.figure()
ax = fig.subplots()
ax.fill_between(fill_x, fill_y, 0, alpha=.2)

ax.grid(True)
ax.grid(which='minor', alpha=0.2)
ax.set_xlabel('Depth [cm]')
ax.set_xticks(z_majticks)
ax.set_xticks(z_minticks, minor=True)
ax.set_xlim([0, z_max])

ax.set_ylabel('Relative dose [%]')
ax.set_yticks(d_majticks)
ax.set_yticks(d_minticks, minor=True)
ax.set_ylim([0, d_max*ff])
ax.plot(z, dose_w_rel, linewidth=0.5, label="MC Dose")

ax2 = ax.twinx()
ax2.set_ylabel('LET [keV/um]')
ax2.set_ylim([0, dl_max*ff])
ax2.set_yticks(l_majticks)
ax2.set_yticks(l_minticks, minor=True)
ax2.grid(which='minor', alpha=0.2)

for i, y in enumerate(dlw):
    yy = y[:, 1][let_mask]*0.1
    ye = y[:, 2][let_mask]*0.1
    ax2.plot(z_lim, yy, label=ll[i])
    ax2.fill_between(z_lim, yy-ye, yy+ye, alpha=0.2)

# nominal mouse leg positions
for i in range(8):
    mxx = [6.5+i*0.4 + 0.03, 6.5+(i+1)*0.4 - 0.03]
    myy = [103.0, 103.0]
    myy2 = [104.0, 104.0]
    ax.fill_between(mxx, myy, myy2, alpha=.2, color='r')
    ax.text(6.5+i*0.4+0.12, 105, str(i+1), alpha=0.2)


fig.legend(loc=(0.15, 0.6))
fig.savefig("proton_let.png")


# target bins
# Output
#         Filename NB_target_water.bdo
#         Geo TARGET
#         Quantity DOSE in_Water                  # __p1
#         Quantity DLET in_Water                  # __p2
#         Quantity DLET Primary in_Water
#         Quantity DLET Protons in_Water
#         Quantity TLET in_Water                  # __p5
#         Quantity TLET Primary in_Water
#         Quantity TLET Protons in_Water
#
# Output
#         Filename NB_target.bdo
#         Geo TARGET
#         Quantity FLUENCE                        # __p1
#         Quantity DOSE                           # __p2
#         Quantity DLET                           # __p3
#         Quantity DLET Primary
#         Quantity DLET Protons
#         Quantity TLET                           # __p6
#         Quantity TLET Primary
#         Quantity TLET Protons
#         Quantity DQEFF                          # __p9
#         Quantity DQEFF Primary
#         Quantity DQEFF Protons
#         Quantity TQEFF                          # __p12
#         Quantity TQEFF Primary
#         Quantity TQEFF Protons

zt = dtg[0][:, 2]        # extract center bin positions
zw = zt[1] - zt[0]       # bin width
z0 = zt - zw * 0.5       # bin leading edges


tg_dw = dtgw[0][:, 3] * 0.1    # dose to water
tg_dw_rel = tg_dw / ((tg_dw[0]+tg_dw[1])*0.5) * 100.0
tg_mask = tg_dw_rel > 1

z0_lim = z0[tg_mask]

tg_dlw0 = dtgw[1][:, 3][tg_mask] * 0.1  # dlet to water all
tg_dlw1 = dtgw[3][:, 3][tg_mask] * 0.1  # dlet to water protons

tg_dq0 = dtg[8][:, 3][tg_mask]   # qeff all
tg_tq0 = dtg[11][:, 3][tg_mask]   # qeff all

# make a table with position results
pos = np.arange(1, 9, dtype=int)
res = np.vstack([pos, zt, tg_dw_rel, dtgw[1][:, 3]*0.1, dtgw[3][:, 3]*0.1, dtg[8][:, 3], dtg[11][:, 3]])
lab = ["Position #", "Position [cm]", "Dose [%]",
       "dLET,w,all [keV/um]", "dLET,w,prot [keV/um]",
       "dQeff,all", "tQeff,all"]
np.set_printoptions(precision=2, suppress=True)

for i, d in enumerate(res):
    print("{:} {:}".format(lab[i], d))

# ---------------------------------- Mouse positions
fig = plt.figure()
ax = fig.subplots()
ax.step(z0, tg_dw_rel, label="Dose")
ax.fill_between(z0, tg_dw_rel, 0, alpha=0.2, step='pre')

# nominal mouse leg positions
for i in range(8):
    mxx = [6.5+i*0.4 + 0.03, 6.5+(i+1)*0.4 - 0.03]
    myy = [103.0, 103.0]
    myy2 = [104.0, 104.0]
    ax.fill_between(mxx, myy, myy2, alpha=.2, color='r')
    ax.text(6.5+i*0.4+0.12, 105, str(i+1), alpha=0.2)

ax.grid(True)
ax.set_xlabel('Depth [cm]')
ax.set_ylabel('Relative dose [%]')

ax2 = ax.twinx()
ax2.set_ylabel('LET [keV/um]')
ax2.step(z0_lim, tg_dlw0, label="dLET,w,all", color="tab:orange")
ax2.fill_between(z0_lim, tg_dlw0, 0, alpha=0.1, step='pre', color="tab:orange")
fig.legend(loc=(0.65, 0.7))
fig.savefig("mouse_positions.png")


# ---------------------------------- measured dose plot
fig = plt.figure()
ax = fig.subplots()
ax.fill_between(fill_x, fill_y, 0, alpha=.2)

# nominal mouse leg positions
for i in range(8):
    mxx = [6.5+i*0.4 + 0.03, 6.5+(i+1)*0.4 - 0.03]
    myy = [103.0, 103.0]
    myy2 = [104.0, 104.0]
    ax.fill_between(mxx, myy, myy2, alpha=.2, color='r')
    ax.text(6.5+i*0.4+0.12, 105, str(i+1), alpha=0.2)


ax.grid(True)
ax.grid(which='minor', alpha=0.2)
# ax.tick_params(axis='x', which='minor')
ax.set_xlabel('Depth [cm]')
ax.set_xticks(z_majticks)
ax.set_xticks(z_minticks, minor=True)
ax.set_xlim([0, z_max])

ax.set_ylabel('Relative dose [%]')
ax.set_ylim([0, d_max*ff])
ax.set_yticks(d_majticks)
ax.set_yticks(d_minticks, minor=True)
ax.plot(z, dose_w_rel, linewidth=0.5, label="MC Dose")
ax.scatter(z_ic_m, dose_ic_m, marker='+', label="IC Adv.Markus")
ax.scatter(z_ic_s, dose_ic_s, marker='x', label="IC Semiflex")

fig.legend(loc=(0.15, 0.7))
fig.savefig("proton_dose.png")
