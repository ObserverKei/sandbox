#!/bin/bash

mkdir -p space

for i in $(seq 1 10) 
do
	touch space/`date +%Y%m%d_%H%M%S_%N`
done
