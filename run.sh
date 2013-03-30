#!/bin/bash
for (( A=1; A<=13; A=A+1 ))
do
echo '****'
echo $A
	./rasterize ./input/p$A.in > p$A.out
	diff -b ./input/p$A.in p$A.out
done

