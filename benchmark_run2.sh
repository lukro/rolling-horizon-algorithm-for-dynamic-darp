#!/bin/bash

# Maximum number of processes to run at once
max_processes=4

for p in $(LANG=en_US seq 0.05 0.05 1)
do
    # Nested loop for -td values from 0.05 to 0.25 with steps of 0.05, skipping 0
    for delay in $(LANG=en_US seq 0.20 0.05 0.25)
    do
        # Run each configuration 10 times
        for run in $(seq 1 10)
        do
            echo " ./bin/darp_cplex_6 no6 -p $p --node-delay $delay > output/benchmarks/${delay}MIN${p}P_run${run}.txt"
            ./bin/darp_cplex_6 no6 -p $p --node-delay $delay > output/benchmarks/${delay}MIN${p}P_run${run}.txt &

            # If the number of background processes has reached $max_processes, wait until one finishes
            while [ $(jobs -p | wc -l) -ge $max_processes ]; do
                wait -n
            done
        done
    done
done

# Wait for any remaining background processes to finish
wait