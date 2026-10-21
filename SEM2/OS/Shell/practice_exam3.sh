#!/bin/bash

NRU=$(wc -l < who.fake)
for INDEX in $(seq $NRU)
do
        user=$(awk "NR==$INDEX {print \$1}" who.fake)
        nr_proces=$(grep "^$user " ps.fake | wc -l)
        echo "$user $nr_proces"
done

exit  0