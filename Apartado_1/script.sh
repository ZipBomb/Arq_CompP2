#!/bin/bash

N=(100 10000 1000000 10000000)

if [ -f "datosNormales.txt" ]; then
    rm "datosNormales.txt";
fi

for i in "${N[@]}"; do
    for ((j=0; j<3; j++)); do    
        ./test $i
    done
done
