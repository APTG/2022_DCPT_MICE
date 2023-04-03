# SHIELD-HIT12A Simulations

`./plan_*` contain input files for shieldhit simulations. They are entirely encapsulated and do not depend on external files.

`./results` contain the results from the SH12A runs.

## How to Run

Requires SHIELD-HIT12A version `v1.0.0` or newer.

### Standalone

From this directory you can simply run:
`$shieldhit ./plan1`

Windows:
`shieldhit.exe plan1`

### On PROMETHEUS computing cluster

using `pro.cyfronet.pl`:

From the same directory as this README file run following command:

`$ generatemc -j100 -p1000000 -s "[ -p plgrid-short --time=0:59:00]" -e "[ -t 00:55:00]"  plan1/`

and do this for every plan. 100 hours is plenty for good statistics.

## Postprocess

Run local script `./postprocess.sh` from same directory as this README file.

## MC Parameter Summary
| Item name | Description | References |
|---|---|---|
| Code, version | SHIELD-HIT12A v.1.0.0 | Bassler et al. |
| Validation | Depth-dose measurements |  |
|  | LET and Q validation agains microdosimetry, Geant4, TOPAS, RayStation, PHITS | (in preparation) |
| Timing | 100 jobs, CPU time 55 minutes each job |  |
| Geometry | Modeled from actual measured dimensions |  |
| Source | Generated with Eclipse TPS, DCPT beam model for MC |  |
| Physics | SH12A Defaults | Bassler et al. |
| Scoring | Dose to water. LETd,t and Qeffd,t in water |  |
| #histories | 100 x 1000000 |  |
