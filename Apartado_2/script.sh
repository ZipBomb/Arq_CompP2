#!/bin/bash

N=(10000 10000 10000 100000 100000 100000 1000000 1000000 1000000 10000000 10000000 10000000)

for i in "${N[@]}"; do
	./test $i
done
