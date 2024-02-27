#!/bin/bash

# Maximum number of processes to run at once
max_processes=4

# Loop for -p values from 0 to 1 with steps of 0.2
for p in $(LANG=en_US seq 0 0.2 1)
do
    # Nested loop for -td values from 0 to 1 with steps of 0.01
    for td in $(LANG=en_US seq 0 0.05 0.25)
    do
        # Run each configuration 10 times
        for run in $(seq 1 10)
        do
            echo " ./bin/darp_cplex_6 no6 -p $p --node-delay $td > output/delay_probability_run/${td}min_${p}_td_run${run}.txt"
            ./bin/darp_cplex_6 no6 -p $p --node-delay $td > output/delay_probability_run/${td}min_${p}_td_run${run}.txt &

            # If the number of background processes has reached $max_processes, wait until one finishes
            while [ $(jobs -p | wc -l) -ge $max_processes ]; do
                wait -n
            done
        done
    done
done

# Wait for any remaining background processes to finish
wait