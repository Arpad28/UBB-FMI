#!/bin/bash

if [ $# -eq 0 ]
then
        echo 'Numar insuficient de argumente'
        exit 1
fi

#citesc cele doua cuvinte
read -p "Primul cuvant:" CUV1
read -p "Al doilea cuvant:" CUV2

for FILE in $@
do
        sed -E 's/'$CUV1'/'$CUV2'/gI' $FILE
done

exit 0