#!/bin/bash

IFS="
"
TMPFILE=$(mktemp)
TMPFILE2=$(mktemp)
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
	# вот этот костыль нужен, потому что у меня почему-то не работает
	# обычный пайп echo $line | read -r letter row col
	# просто в консоли работает а здесь нет, с чем связано не понимаю
	echo $line > $TMPFILE2
	IFS=" " read -r letter row col < $TMPFILE2
	tput cup $row $col
	echo $letter
	sleep $delay
done < $TMPFILE
tput cup $((current_row)) 0

rm -f $TMPFILE
rm -f $TMPFILE2
