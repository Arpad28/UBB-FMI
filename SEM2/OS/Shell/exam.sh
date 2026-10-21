#!/bin/bash

if [ $# -eq 0 ]
then
        echo "Nu ai introdus niciun argument"
        exit 1
fi

for user in $@
do
        if echo "$user" | grep -Eq "^[a-z]{2}[0-9]{3}
                then
                        grupa=$(cat /etc/passwd | grep -E "$user" | awk '{print $3}')
                        nume=$(grep -E "$user" /etc/passwd | awk -F ' ' '{print $3}' | awk -F: '{print $1}')
                        time=$(last | grep -E "$user" | head -n 1| awk '{print $5, $6, $7}')
                        if[ -n $time ]
                        then
                                echo "$grupa | $nume | $time"
                        else
                                echo "$grupa | $nume"
                        fi
                fi
done