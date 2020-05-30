#!/bin/bash
# 5) Utiliser graphviz dot (demander au bro bapt lpzer)

printHelp(){
    echo 'Erreur : Syntax : ./launch.sh numberOfApexes --graph existingGraph.txt';
}

fileExists(){
    FILE=$1
    if test -f "$FILE"; then
        return 1
    fi
    return 0
}

if test $# -ne 3 && test 1 -ne $# 
then
    printHelp
    exit
fi

#Verif que le premier argument soit bien un entier
if [ -n "$1" ] && [ "$1" -eq "$1" ] 2>/dev/null; then
    if test $1 -lt 2
    then
        printHelp
        exit
    fi
else
    printHelp
    exit
fi

#verif que le graph entree existe
if test $# -eq 3 
then
    if test $2 = '--graph'
    then
        if fileExists $3
        then
            printHelp
            exit
        fi
    else
        printHelp
        exit
    fi
fi

gcc -Wall -std=c99 -g -O2 -o hamiltonv2 hamiltonv2.c 2>/dev/null
if test $# -eq 3
then
    ./hamiltonv2 $1 $3
    minisat hamiltonv2.cnf hamiltonv2.out
    ./getGraph2.sh $1 $3
    dot -Tpng "$3" -o graph1.png

else
    ./hamiltonv2 $1
    minisat hamiltonv2.cnf hamiltonv2.out
    ./getGraph2.sh $1
    dot -Tpng graph1.txt -o graph1.png
fi

dot -Tpng graph2.txt -o graph2.png
