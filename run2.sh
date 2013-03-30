#!/bin/bash
A=5
./rasterize ./input/p$A.in 
ppmtobmp img.out > img.bmp
mv img.bmp ~/public_html
