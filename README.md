# thorkellbot



## Table of contents

1. [Introduction](#intro)


## Introduction<a name="intro"> <a/>

This repository serves as documentation for a Sumobot Project, developed for the 'Fabricacióon Digital' course, of the Department of Mechanical Engineering, Universidad de Chile.

This project consists on the design and fabrication of a robot for Robot-Sumo competitions, specifically 1kg class ones. You can read more about these competitions [here](https://www.fsi.co.jp/sumo-e/out/outc0000.html).

In this repo you will find a Bill of Materials, as well as CAD files and the basic code implemented for it. 

## CAD Files

You can access the current version of our CAD files on GrabCAD, on the following link: 

## Bill of materials


## Manufacturing processes

3 main manufacturing processes were used in this project: CNC Machining, 3D Printing and Polyurethane Casting. 

### CNC Machining
Using Fusion 360's Manufacturing Environment, a CAM Program was made for cutting the ACP Chassis, using a slotting bit and different drill bits for 2D Contours and Drilling operations. 
If you don't have access to this material, it can also be made out of wood or 3D Printed, taking into account the weight differences. 

The following operation parameters were used on a ShopBot PRSAlpha CNC Router:

#### Contouring:
Tool: 3/16'' 2 flute straight router bit.
| Parameter                 | Value  |
|---------------------------|--------|
| Spindle RPM               | 6000   |
| Cutting Feedrate [mm/min] | 690    |
| Feed per tooth [mm]       | 0.0575 |
| Ramp Feedrate [mm/min]    | 230    |

#### Drilling:
Tool: 3 mm drill bit
| Parameter                 | Value  |
|---------------------------|--------|
| Spindle RPM               | 6000   |
| Plunge feedrate [mm/min]  | 300    |


### 3D Printing
3D Printing was used for manufacturing the robot's body kit, the adapter for mounting the omni-wheel, as well as the main wheel's molds and 'cores'. 


### Casting
Finally, the wheels were casted using polyurethane, but there's cheaper ways of doing this, as seen [here](https://www.instructables.com/Grippy-Hollow-Silicone-Tires-for-Robots-and-RC/) and [here](https://www.youtube.com/watch?v=_7dLUU1tf58). There's many other resources found on the internet about casting custom wheels with readily available materials. 

The mould was designed to be reusable, and also to secure alignment of the wheel during the casting process, and also maintaining the casted tire in place with the included slots in the wheel, considering the poor adhesion of silicone to PLA. 

## Assembly

