#!/bin/bash

>numar_aparitii

for FISIER in $@
do
        if [ ! -f $FISIER ]
        then
                echo $FISIER nu exista
                continue
        fi
        while read LINIE
        do
                echo $LINIE
                NA=$(grep -Ec "$LINIE" $FISIER)
                echo $NA "$LINIE" >>numar_aparitii
        done < <(cat file1 | sort | uniq)
done

while read N LINIE
do
        echo Linia "\"$LINIE\"" apare de $N ori
done< <(cat numar_aparitii | sort -r)
exit 0