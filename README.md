# Mouse Water Phantom "2014-EKO"
This phantom was first used in ion beams 2014 at GSI, Darmstadt, then multiple times at IFJ-PAN in Krakow, and later at DCPT in Aarhus.

## General description
- Walls made of PMMA. approx 1 cm thick.
- Isocenter located at entry surface of the water phantom.
- Z postive along beam direction, Y postive upwards, X positive from right to left as seen in beam direction.

## Outer dimensions
- X-width: 449.5 mm Relative to isocenter: [-133.5; +316.0] mm
- Y-width: 249.5 mm Relative to isocenter: [-170.0;  +79.5] mm
- Z-width: 344.5 mm Relative to isocenter: [   0.0; +344.5] mm

## Wall Thickness
- All 0.95 mm, except for YZ wall at positive X, which is 1.05 mm.

## PMMA lid
- A PMMA plate act as a lid which may holds three mice over water.
- The PMMA lid may be displaced in 8 steps of 4.0 mm along the z-axis
- Two PMMA lids were designed:
   - Revision 1 "2014-lid", including 2 holders for additional detectors
   - Revision 2 "2016-lid"
- Thickness of lid: 0.50 mm rev 1 and 2
- In this simulation a solid lid will be modeled
  - X-width: 248.0 mm Relative to isocenter: [ -124.0; +124.0] mm
  - Y-width:   5.0 mm Relative to isocenter: [  +14.5;  +19.5] mm
  - Z-width: 182.5 mm Relative to isocenter: [   +9.5; +192.0] mm

# Water level
- until surface of the PMMA lid, i.e.: Y: [-160.5; +19.5] mm

# Brass collimator:
- X-width: 123.7 mm Relative to isocenter: [-82.0; +41.7] mm can be shifted up to +3 mm, not precise
- Y-width:  46.0 mm Relative to isocenter: [+14.5; +60.5] mm can be adjusted, here matched PMMA lid underside
- Z-width:  19.5 mm Relative to isocenter: [+37.5; +57.0] mm at position 1, follows pos 1-8 in 4 mm steps.

- Top of brass block has a Z-width reduction from 19.5 mm 15.5 mm, to allow space for mouse tail. This extrusion is 89.0 mm wide, 14.0 mm from the bottom of the collimator and 17-18 mm from the two edges of the brass block along X.


## Nominal scoring positions
- Each bin for averaging is 4x4x4 mm wide.
- 8 positions along z axis, measured from phantom surface where beam enters:
  - first bin: [65.0; 69.0] mm  (position 1)
  - last bin: [97.0; 101.0] mm  (position 8)
  - lateral scoring width is 1 cm along X and Y for good statistics and safely assuming lateral equilibrium

## PTV
Noinal PTV extension, relative to isocenter, beam traveling along Z axis. Y is vertical, positive upwards.
- x = [-50.0; 50.0] mm
- y = [-12.5;  7.5] mm
- z = [ 50.0; 85.0] mm

## Directory structure
https://drivendata.github.io/cookiecutter-data-science/
