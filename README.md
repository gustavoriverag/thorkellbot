# thorkellbot



## Table of contents

1. [Introduction](#intro)
2. [CAD files](#cad)
3. [Bill of materials](#bom)
4. [Manufacturing processes](#manufacturing-processes)
5. [Wiring](#wiring)

## Introduction<a name="intro"> <a/>

This repository serves as documentation for a Sumobot Project, developed for the 'Fabricacióon Digital' course, of the Department of Mechanical Engineering, Universidad de Chile.

This project consists on the design and fabrication of a robot for Robot-Sumo competitions, specifically 1kg class ones. You can read more about these competitions [here](https://www.fsi.co.jp/sumo-e/out/outc0000.html).

In this repo we showcase our design, indicate everything needed to replicate it, comment on the fabrication process of our prototype and explain the robot's routine.

## CAD Files<a name="cad"> <a/>

You can access the current version of our CAD files on GrabCAD, on the following link: 

## Bill of materials<a name="bom"> <a/>


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

## Wiring

In the following picture, you can see a diagram of our project's electronics: 

![wiring_diagram](img/diagram.png)

In order to optimize ground and 5v pin usage, we used a breadboard, but since we needed to stay within 1kg, we cut a standard breadboard to just 10 rows with a saw.

We also used a 11.1V LiPo Battery, in order to maximize the motor's power capacity.

## Assembly

For assembly we reccomend going from the bottom up. First mounting the DC Motor brackets, and aligning them as good as you can. Then, mounting the caster wheel with its adapter, and also the IR Sensor with its spacer. 
Then, we secured the l298n motor driver with cable ties to the chassis, and did the same to the battery. 

If you include a switch, you need to solder the female battery connector's positive wire to it, and the other end insert it into the l298N's 12V port. The ground you connect to the chip's gnd port, and from that same port connect a gnd that will go to the arduino. From the chip's 5V port you get the positive power wire for the arduino. Here you can use a dc plug, or connect to the Vin pin. 

Then, we mount the bodykit's lateral supports, wire the tracker sensor, and wire the ultrasonic sensor, after you mount it to the weapon's included support.

With that done, all that's left is install the weapon, install the arduino and protoboard support plates and wire the rest of the system up. 

For the wheels, press fit the hex couplings into the wheel cores, and install the other end to the motor shafts, tightening the set screw on the flat side. 

## Code explanation

