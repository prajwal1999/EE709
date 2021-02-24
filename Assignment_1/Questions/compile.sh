#!/bin/sh

gcc  -o output $1 -I ../include -L ../lib -lbdd -lmem
./output 2>&1 | tee $1.log
