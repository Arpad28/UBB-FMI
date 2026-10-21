#!/bin/bash

# ./ex2.sh nume_director

#verific  numarul de argumente
#verific ca e director
if [ ! -d $1 ]
then
        echo "$1 trebuie sa fie un nume de director !"
        exit 2
fi

LISTA_FISIERE=$(find $1 -type f)
NTL=0
NTF=0
for FISIER in $LISTA_FISIERE
do
        if file $FISIER | grep -Eq 'ASCII text$'
        then
                #NL=$(wc -l  <$FISIER) # < pentru a scapa de numele fisierului
                NL=$(cat $FISIER | wc -l)
                NTL=$(($NTL+$NL)) # (()) pentru a face calcule,evaluare aritmetica
                NTF=$((NTF+1)) # merge si cu [NTF+1],merge si cu $ si fara
        fi
done

echo -e  "Numar fisiere: $NTF\nLinii: $NTL\nMedia: $((NTL/NTF))"
exit 0