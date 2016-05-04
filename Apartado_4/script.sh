#!/bin/bash

N=(100 10000 1000000 10000000)

if [ -f "datosOptimizados.txt" ]; then
    rm "datosOptimizados.txt";
fi

for i in "${N[@]}"; do
    for ((j=0; j<10; j++)); do    
        ./test $i
    done
done
