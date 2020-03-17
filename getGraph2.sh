#!/bin/sh
GRAPHSIZE=$1
read -r firstline<hamiltonv2.out
if test $firstline = 'SAT'
then
    #change format of the .out
    sed -z -i 's/SAT\n//g;' 'hamiltonv2.out'
    sed -i 's/ /\n/g;' 'hamiltonv2.out'
    sed -i '/^-/d' 'hamiltonv2.out'
    sed -i '/^0/d;' 'hamiltonv2.out'

    #read .out line by line and stores apexes in pathApexes
    for i in $(seq "1" "$1");
    do
        
    done

fi