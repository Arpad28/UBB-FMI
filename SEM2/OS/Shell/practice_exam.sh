#!/bin/bash

if [ ! $# -eq 4 ]
then
        echo "Nu ai introdus destule argumente"
        echo "Mod de utilizare <fisier_script> file1 file2 file3"
        exit 1
fi
fisier_intrare=$1
fisier2=$2
fisier3=$3
fisier4=$4
nr2=0
nr3=0
while read cuv
do
        if echo "$cuv" | grep -Eq "^[aeiouAEIOU][a-zA-Z0-9]*[^aeiouAEIOU]$"
        then
                echo $cuv >>"$fisier2"
                nr2=$(($nr2+1))
        fi
        if echo "$cuv" | grep -Eq "[0-9]"
        then
                echo $cuv >>"$fisier3"
                nr3=$(($nr3+1))
        fi
done < <(grep -Eo "[a-zA-Z0-9]+" "$fisier_intrare")

echo "Pe primul criteriu s-au gasit $nr2 cuvinte si pe al doilea criteriu $nr3 cuvinte" >>"$fisier4"
exit 0