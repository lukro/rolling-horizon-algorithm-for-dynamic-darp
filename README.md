# Delay management in the dynamic Dial-a-Ride-Problem

 ## Background
This is a fork of [Rolling Horizon Algorithm for the dynamic DARP](https://git.uni-wuppertal.de/dgaul/rolling-horizon-algorithm-for-dynamic-darp), which is based on: <br>
Gaul, Klamroth, and Stiglmayr, 2021. Solving the dynamic dial-a-ride problem using a rolling-horizon event-based graph; https://doi.org/10.4230/OASICS.ATMOS.2021.8.<br>
Original License: <a rel="license" href="http://creativecommons.org/licenses/by-nc-sa/4.0/">Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License</a>.

For details of the main rolling-horizon algorithm and implementation please refer to the above reference. <br>

 ## Modifications
 **The modifications are currently under review**
 * Add possibility to generate randomized delays during MILP iteration; Currently only fixed delay and probability given as parameters are possible
 * Revised terminal output laying the focus on passenger flow inside the vehicles; Using colors and scaling with terminal window size; Tested in /bin/bash and Z shell

 ## Compilation
 Change the location of your CPLEX directories in the Makefile first. Compile the project using "make". 

## Usage
There are two binaries <br>
 ./bin/darp_cplex_3<br>
 ./bin/darp_cplex_6<br>
 to choose between normal cabs (Q=3) and ridepooling cabs (Q=6). 
 
 Example call:
 ```
 ./bin/darp_cplex_6 [INSTANCE] [-PARAMETERS]
```
### Instances
 Availabe instances are:
 * no6 (short for data/WSW/no_116_6_req.txt); dynamic instances
 * static benchmark instances from [Event-based MILP for DARP](https://git.uni-wuppertal.de/dgaul/event-based-milp-for-darp); These run in instance_mode=1 which transforms them to dynamic instances. <br><br>

 ### Parameters (only tested for Q=6)
* -p or --probability: Probability of a delay occuring during edge fixation in the range [0..1]
* -nd or --node-delay: delay in minutes as double value, e.g. 30 seconds is 0.5
Example:
```
./bin/darp_cplex_6 no6 -p 0.1 -nd 0.75
```

## Output 
The current configuration displays every vehicles events history and (projected) future events (orange/yellow marked). All events have this format:
```
+|-[PASSENGER_NR] [TIME]
```
Where the time is given in mm:ss

## Test instances (see original repository)
 As test instances two different file formats are accepted:<br>
 - First format (this refers to instance_mode = 1): Test instance consists of one file.  <br>
    <pre>
    2 32 480 3 30
    0   0.000   0.000   0   0    0  480
    1  -1.198  -5.164   3   1    0 1440
    2   5.573   7.114   3   1    0 1440
    3  -6.614   0.072   3   1    0 1440
    4  -7.374  -1.107   3   1    0 1440
    5  -9.251   8.321   3   1    0 1440
    6   6.498  -6.036   3   1    0 1440
    7   0.861   6.903   3   1    0 1440
    8   3.904  -5.261   3   1    0 1440
    9   7.976  -9.000   3   1  276  291
    10  -2.610   0.039   3   1   32   47
    ...
    </pre>
    
    First line corresponds to: K 2n T Q L_i, where L_i = 30 for all i=1,...,n<br>
    Column 1: identifies nodes 0,...,2n+1<br>
    Column 2 and 3: x and y coordinates of the nodes<br>
    Column 4: service time <br>
    Column 5: load<br>
    Column 6 and 7: time window<br>


- Second format (this refers to instance_mode = 2): Test instance consists of two files.<br>
    1) One file containing the distance matrix (c_{i,j}), named "instance_name_c_a.txt". The file shoud be formatted like this:<br>
        <pre>
        c_{0,0}  c_{0,1} ... c{0,2n}
        c_{1,0}  c_{1,1} ... c{1,2n}
        .
        .
        .
        c_{2n,0} c_{2n,1} ... c_{2n,2n}
        </pre>
    2) The other file, "instance_name.txt", contains everything else. This file should have the following format: <br>

        <pre>
        8 508 840 3 0
        0 0.0 0 0.0 840.0 840.0
        1 0.75 1 126.0 151.0 22.33
        2 0.75 1 216.0 241.0 15.85
        ...
        507 0.75 -1 833.89 840.0 16.14
        508 0.75 -1 834.62 840.0 15.87
        509 0 0 0 840 840
        </pre>

        First line corresponds to: K 2n T Q 0<br>
        Column 1: identifies nodes 0,...,2n+1<br>
        Column 2: service time<br>
        Column 3: load<br>
        Column 4 and 5: time window<br>
        Column 6: ride time L_i<br>

This repository contains a test instance of the second type in the directory data/WSW. In this instance a vehicle capacity of Q=6 is assumed.

    
 ## Authors
 The main author of the code is Daniela Gaul (gaul@math.uni-wuppertal.de). It was developed at Bergische Universität Wuppertal with her PhD advisors Kathrin Klamroth and Michael Stiglmayr.

 Delay integration and terminal formatting was contributed by Lukas Kröger (LukasPKroeger@web.de).
