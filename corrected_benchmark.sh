#!/bin/bash

max_processes=4

dir="output/final_benchmark"

for delay in $(LANG=en_US seq 0.1 0.1 0.5)
do
    for p in $(LANG=en_US seq 0.1 0.1 1)
    do
        for run in $(seq 1 5)
        do
            echo " ./bin/darp_cplex_6 no6 -p $p --node-delay $delay &> ${dir}/dl${delay}p${p}_run${run}.txt"
            ./bin/darp_cplex_6 no6 -p $p --node-delay $delay &> ${dir}/${delay}min${p}pr_run${run}.txt &

            # If the number of background processes has reached $max_processes, wait until one finishes
            while [ $(jobs -p | wc -l) -ge $max_processes ]; do
                wait -n
            done
        done
    done 
done

wait