#!/bin/bash
#Author: Ryuho Kudo

if [ $# -ne 1 ] 
then
   echo "need exactly one argument"
   exit
fi

for file in $( find ~/ -type f )
do
   if [ $( find "$file" | grep $1 | wc -l) -ne 0 ]; then
      echo "$file"
   fi
done


