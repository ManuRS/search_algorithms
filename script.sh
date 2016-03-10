#!/bin/bash

echo
echo EJECUTANDO SCRIPT
echo

make

make simulacion

gnuplot makegraphs.sh

mkdir DATOS
mkdir GRAFICAS

rm -f fit.log

mv *.log DATOS/
mv *.png GRAFICAS/

make clean

echo
echo SCRIPT FINALIZADO
echo

# rm -f *png fit.log
# rmdir DATOS
# rmdir GRAFICAS
