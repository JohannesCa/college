#!/bin/bash

# Autor: Johannes Cavalcante

declare -a method=("selection" "insertion" "merge" "quick" "heap" "default")
declare -a entropy=("10" "50" "90")
declare -a elements=("100000" "500000" "1000000")
declare -a ex=("1" "2" "3" "4" "5")


## now loop through the arrays
for i in "${method[@]}"
do
  for j in "${entropy[@]}"
  do
    for k in "${elements[@]}"
    do
      for l in "${ex[@]}"
      do
        echo "$i $j.$k.$l.in"
        ./apa-t1 "$i" "$j.$k.$l.in"
      done
    done
  done
done
