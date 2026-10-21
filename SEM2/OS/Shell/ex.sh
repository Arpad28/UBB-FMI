#!/bin/bash

nrlinii=0;
nrfile=0;
total=0;

for file in `ls | grep -E ".*\.txt"`
do
        nrlinii=`cat $file | wc -l`
        nrfile=$(($nrfile+1))
        total=$(($total+$nrlinii))
done

average=$(($total/$nrfile))

echo $average