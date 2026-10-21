#!/bin/bash

#citesc cuvantul
read -p "Cuvant: " CUVANT
#$@ lista de arugmente
for FILE in $@
do
        #verific ca fisierul exista
        if [ -f $FILE ]
        then
                #NA=$(grep -Eo "\b$CUVANT\b" $FILE | wc -l)
                #echo "Fisier: $FILE cuvant: $CUVANT aparitii: $NA"   #echo -e pentru \n
                NA=0
                for CUV in $(cat $FILE)
                do
                        if [[ "$CUV" == "$CUVANT" ]];then
                                NA=$((NA+1))
                        fi
                done
                echo "Fisier: $FILE cuvant: $CUVANT aparitii: $NA"   #echo -e pentru \n
        fi
done

exit 0