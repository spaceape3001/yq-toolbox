#!/bin/csh

make clean
(time make) |& tee build.log

