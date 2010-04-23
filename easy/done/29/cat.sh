#!/bin/sh

#set -x
n2=`seq $(($1+1)) $(($1*2))`
np1=`seq 1 $(($1+1))`

f1=`echo $n2 | sed 's/ /*/g' | bc -l | tr -d '\n\\\\'`
f2=`echo $np1 | sed 's/ /*/g' | bc -l | tr -d '\n\\\\'`

c=`echo $f1/$f2 | bc | tr -d '\n\\\\'`
#echo $c
c=`echo $c % 10000 | bc`
echo $c
