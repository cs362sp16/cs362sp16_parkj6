#!/bin/bash -e
	totalfailed=0
	totalpassed=0
	count=1
	tentho=10000
	failed=($(for i in {1..100}; do echo 0; done))
	passed=($(for i in {1..100}; do echo 0; done))
	suspiciousness=($(for i in {1..100}; do echo 0; done))
	red='\033[0;31m'
	green='\033[0;32m'
	yellow='\033[1;33m'
	black='\033[0;30m'

for i in 1 2 3 4 5;
do
	make clean
	make
	cardtest="cardtest"$i
    result=$(./$cardtest)
    gcov dominion.c
    if [ `echo $result | grep -c "FAILED" ` -gt 0 ]
	then
	  flag=1; #testfailed
	else
	  flag=0; #testpassed
	fi
    FILENAME="dominion.c.gcov"
    while read LINE
	do
		IFS=: 
		set $LINE
		exenum1=$1 
		e=$2  #e is the line number
		exenum=$(echo $exenum1 | tr -d ' ') #exenum is the time a line was executed
		if [ "$exenum" -eq "$exenum" ] 2>/dev/null #if exenum is a number
		then
    		if [[ $flag -eq 1 ]]; #this test failed
			then
	    		totalfailed=$(($totalfailed+$count))
	    		failed[$e]=$((${failed[$e]}+$count))
	    	elif [[ $flag -eq 0 ]]; #this test passed
	    	then
	    		totalpassed=$(($totalpassed+$count))
	    		passed[$e]=$((${passed[$e]}+$count))
			fi
		fi
		linenum=$e
	done < $FILENAME
done 
for ((i=1;i<=linenum;i++)); do
	if [ ${passed[i]} -gt 0 -o ${failed[i]} -gt 0 ]; then
		failedlarge=$((${failed[i]}*$tentho))
		passedlarge=$((${passed[i]}*$tentho))
		failrate=$(echo $failedlarge $totalfailed | awk '{ printf "%f", $1 / $2 }')
		passrate=$(echo $passedlarge $totalpassed | awk '{ printf "%f", $1 / $2 }')
		plus=$(echo $failrate $passrate | awk '{ printf "%f", $1 + $2 }')
		suspiciousness[i]=$(echo $failrate $plus | awk '{ printf "%f", $1 / $2 }')
	fi
	
done

mapfile -t myArray < dominion.c

susvar=0.5
nonsusvar=0
for ((j=0; j<1355;j++)); do
	l=$(($j+1))
	if [ ${passed[l]} -gt 0 -o ${failed[l]} -gt 0 ]; then
		if [ $(echo " ${suspiciousness[l]} == $nonsusvar" | bc) -eq 1 ]; then
			printf "${green}${myArray[j]}\n"
		elif [ $(echo " ${suspiciousness[l]} > $susvar" | bc) -eq 1 ]; then
			printf "${red}${myArray[j]}\n"
		elif [ $(echo " ${suspiciousness[l]} < $susvar" | bc) -eq 1 ]; then
			printf "${yellow}${myArray[j]}\n"
		fi
	else
		printf "${black}${myArray[j]}\n"
	fi
done