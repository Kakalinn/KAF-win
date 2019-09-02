#!/usr/bin/env bash
rm KefAirportFlug/kvl 
rm KefAirportFlug/komur
rm KefAirportFlug/out.fly
gcc KefAirportFlug/kvl.c -o KefAirportFlug/kvl
rm newKAF/komur
rm newKAF/brottfarir
rm newKAF/out.fly
rm newKAF/inn.fly
rm newKAF/charlone
rm newKAF/kvl
cd newKAF
./rfr.sh .
echo "#define LOCATION \"$(pwd)/\"" > local.h
cd ..
gcc newKAF/charlone.c -o newKAF/charlone -lncursesw -D KAF_LINUX
