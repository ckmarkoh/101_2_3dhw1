#!/bin/bash
./rasterize $1 $2 $3 $4 $5
ppmtobmp img.out > img.bmp
mv img.bmp ~/public_html
