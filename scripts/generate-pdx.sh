#!/bin/sh
mkdir Source
cp pdex.elf Source/pdex.elf
pdc Source $1.pdx
rm -rf Source

