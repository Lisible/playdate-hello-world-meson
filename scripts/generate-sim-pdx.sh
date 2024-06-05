#!/bin/sh
mkdir SourceSim
cp pdex.so SourceSim/pdex.so
pdc -sdkpath $2 SourceSim $1.pdx
rm -rf SourceSim
