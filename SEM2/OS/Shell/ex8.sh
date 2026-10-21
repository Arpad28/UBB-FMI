#!/bin/bash

while [ $# -gt 0 ]
do
        FILE=$1
        shift
        CUVANT=$1
        shift
        K=$1
        shift
        echo 'Fisier: '$FILE' Cuvant '$CUVANT' K: '$K''
done

exit 0
