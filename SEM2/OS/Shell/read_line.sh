#!/bin/bash

for FISIER in $@
do
        #echo $FISIER
        while read LINIE
        do
                echo $LINIE
        done <"$FISIER"
done

exit 0