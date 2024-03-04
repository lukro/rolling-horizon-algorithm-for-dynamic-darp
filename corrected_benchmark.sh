#!/bin/bash

max_processes=4

dir="output/final_benchmark"

for run in $(seq 21 50)
do
    for delay in $(LANG=en_US seq 0.1 0.1 0.5)
    do
        for p in $(LANG=en_US seq 0.1 0.1 1)
        do

            output_file="${dir}/${delay}min${p}pr_run${run}.txt"
            if [ ! -f "$output_file" ]; then
                echo " ./bin/darp_cplex_6 no6 -p $p --node-delay $delay &> $output_file"
                ./bin/darp_cplex_6 no6 -p $p --node-delay $delay &> $output_file &
            else
                echo "Output file $output_file already exists, skipping..."
            fi

            # If the number of background processes has reached $max_processes, wait until one finishes
            while [ $(jobs -p | wc -l) -ge $max_processes ]; do
                wait -n
            done
        done
    done 
done

wait