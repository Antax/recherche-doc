#!/bin/sh

getCurrentApex(){
    CURRENT=$(($CURRENT%$GRAPHSIZE)) 
    if test $CURRENT -eq 0
    then
        CURRENT=$GRAPHSIZE
    fi
}

getFollowingApex(){
    FOLLOWING=$(($FOLLOWING%$GRAPHSIZE)) 
    if test $FOLLOWING -eq 0
    then
        FOLLOWING=$GRAPHSIZE
    fi
}



GRAPHSIZE=$1
read -r firstline<hamiltonv2.out
if test $firstline = 'SAT'
then
    #copie de graph1 dans graph2
    cp 'graph1.txt' 'graph2.txt'
    #change format of the .out
    sed -z -i 's/SAT\n//g;' 'hamiltonv2.out'
    sed -i 's/ /\n/g;' 'hamiltonv2.out'
    sed -i '/^-/d' 'hamiltonv2.out'
    sed -i '/^0/d;' 'hamiltonv2.out'

    #read .out line by line and stores apexes in pathApexes
    for i in $(seq "1" "$(($1-1))");
    do
        read -r CURRENT<hamiltonv2.out
        getCurrentApex
        sed -i '1d' 'hamiltonv2.out'
        read -r FOLLOWING<hamiltonv2.out
        getFollowingApex
        echo "$CURRENT THEN $FOLLOWING"
        sed -i "s/$CURRENT -- $FOLLOWING;/$CURRENT -- $FOLLOWING [color=red]/g;" 'graph2.txt'
        sed -i "s/$FOLLOWING -- $CURRENT;/$FOLLOWING -- $CURRENT [color=red]/g;" 'graph2.txt'
    done
else
    echo 'Erreur le graph n est pas hamiltonien';
    exit;
fi
