#!/bin/bash

IFS="
"
TMPFILE=$(mktemp)
echo $TMPFILE

current_row=0
delay=$1

while read -r line; do
	for (( i=0; i<${#line}; i++ )); do
		letter=${line:$i:1}
		if [[ ! $letter = *[[:space:]]* ]]
		then
			echo $letter $current_row $i >> $TMPFILE
		fi	
	done

	current_row=$((current_row + 1))
done

shuf < $TMPFILE -o $TMPFILE
clear

while read -r line; do
	IFS=" " read -r letter row col <<< $line
	tput cup $row $col
	echo $letter
	sleep $delay
done < $TMPFILE
tput cup $current_row 0

rm -f $TMPFILE
