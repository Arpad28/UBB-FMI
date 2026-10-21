#!/bin/bash

# ./ex5.sh . file_1.txt 567 vasile

if [ $# -eq 0 ]
then
        echo 'Numar insuficient de argumente'
        exit 1
fi

for NUME in $@
do
        if [ -f $NUME ]
        then
                NC=$(cat $NUME | wc -m)
                NL=$(cat $NUME | wc -l)
                echo "Fisier: $NUME linii: $NL caracter: $NC"
        elif [ -d $NUME ]
        then
                NF=$(find $NUME -type f | wc -l)
                echo "Director: $NUME fisiere: $NF"
        else
                if [[ "$NUME" =~ ^[a-zA-Z]+$ ]]
                then
                        echo "$NUME este un sir de caractere"
                elif [[ "$NUME" =~ ^[0-9]+$ ]]
                then
                        echo "$NUME este un numar"
                else
                        echo "Nu stiu ce e $NUME"
                fi
        fi
done

exit 0