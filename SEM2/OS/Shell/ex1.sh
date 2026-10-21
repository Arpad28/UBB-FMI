#!/bin/bash

#verific numarul de  argumente
if [ $# -eq 0 ]; then
    echo "Trebuie sa dai un numar !"
    echo "Utilizare: $0 numar_natural"
    exit 1
fi

#verific  daca e numar
#[[    ]] dubla testare pentru a putea folosi =~ sau == et
if [[ ! "$1" =~ [0-9]+ ]]
then
        echo "$1 nu e numar !"
        exit 2
fi

#generez N fisier
for X in $(seq 1 $1)
do
        #touch "file_$X.txt"
        sed -En ''$X',+5p' /etc/passwd >"file_$X.txt"
done

exit 0