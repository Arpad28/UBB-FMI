#!/bin/bash

if [ $# -eq 0 ]
then
        echo "Nu ai introdus un argument"
        exit 1
fi

if [ ! -d $1 ]
then
        echo "Nu ai introdus un director"
        exit 2
fi
count=0

while read file
do
        lines=$(wc -l <"$file")
        if [ "$lines" -gt 500 ]
        then
                echo "$file"
                count=$(($count+1))
        fi
        if [ "$count" -eq 2 ]
        then
                break
        fi
done < <(find "$1" -type f -name "*.c")

exit 0