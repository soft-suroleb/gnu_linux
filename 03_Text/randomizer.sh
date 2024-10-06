#!/bin/bash

IFS="
"
TMPFILE=$(mktemp)
TMPFILE2=$(mktemp)
echo $TMPFILE

max_len=0
current=0
delay=$1

while read -r line; do
	for (( i=0; i<${#line}; i++ )); do
		letter=${line:$i:1}
		if [[ ! $letter = *[[:space:]]* ]]
		then
			echo $letter $current $i >> $TMPFILE
		fi	
	done

	if (($i>$max_len))
	then
		max_len=$i
	fi;

	current=$((current + 1))
done;

shuf < $TMPFILE -o $TMPFILE
clear

while read -r line; do
	# вот этот костыль нужен, потому что у меня почему-то не работает
	# обычный пайп echo $line | read -r letter row col
	# просто в консоли работает а здесь нет, с чем связано не понимаю
	echo $line > TMPFILE2
	IFS=" " read -r letter row col < TMPFILE2
	tput cup $row $col
	echo $letter
	sleep $delay
done < $TMPFILE
tput cup $((current)) 0

rm -f $TMPFILE
rm -f $TMPFILE2
