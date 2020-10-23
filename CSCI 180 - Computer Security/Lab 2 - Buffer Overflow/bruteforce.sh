#!/bin/bash

SECONDS=0
value=0
while [ 1 ]
	do
	value=$(( $value+1 ))
	duration=$SECONDS
	min=$(($duration / 60))
	sec=$(($duration % 60))
	echo "The program has been running $value times so far."
	echo "It has been $min:$sec (mins:secs)"
	./unsafe
	echo ""
done
