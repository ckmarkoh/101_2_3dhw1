#!/bin/bash
A=1
echo $A
./rasterize ./input/p$A.in > p$A.out
cat ./input/p$A.in | egrep "[-+]?[0-9]*\.?[0-9]+([eE][-+]?[0-9]+)?" > temp1
cat p$A.out | egrep "[-+]?[0-9]*\.?[0-9]+([eE][-+]?[0-9]+)?" > temp2
diff -b --ignore-space-change temp1 temp2
