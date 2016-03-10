#################################
#    Analisis de Algoritmos     #
#          Practica 3           #
#                               #
#  Manuel Reyes y Adrian Bueno  #
#          Grupo 1262           #
#                               #
#  Fichero para crear graficas  #
#################################

###########################################
# Formas de ejecutar:                     #
#    1) Desde el prompt de gnuplot:       #
#              gnuplot> load "<fichero>"  #
#                                         #
#    2) Desde el prompt del shell:        #
#              gnuplot <fichero>          #
###########################################


set term png

f(x) = a*log(x) + b

# BUSQUEDA BINARIA

# 1-16 bbin ordenada equiprobable
set output 'orden_equi_bbin_tiempo.png'
fit f(x) "orden_equi_bbin.log" using 1:2 via a,b
plot "orden_equi_bbin.log" using 1:2 with lines, f(x)

set output 'orden_equi_bbin_ob.png'
fit f(x) "orden_equi_bbin.log" using 1:3 via a,b
plot "orden_equi_bbin.log" using 1:3 with lines, f(x)

# 2-16 bbin ordenada exponencial
set output 'orden_exp_bbin_tiempo.png'
fit f(x) "orden_exp_bbin.log" using 1:2 via a,b
plot "orden_exp_bbin.log" using 1:2 with lines, f(x)

set output 'orden_exp_bbin_ob.png'
fit f(x) "orden_exp_bbin.log" using 1:3 via a,b
plot "orden_exp_bbin.log" using 1:3 with lines, f(x)

# 3-16 bbin_nrec ordenada equiprobable
set output 'orden_equi_bbin_nrec_tiempo.png'
fit f(x) "orden_equi_bbin_nrec.log" using 1:2 via a,b
plot "orden_equi_bbin_nrec.log" using 1:2 with lines, f(x)

set output 'orden_equi_bbin_nrec_ob.png'
fit f(x) "orden_equi_bbin_nrec.log" using 1:3 via a,b
plot "orden_equi_bbin_nrec.log" using 1:3 with lines, f(x)

# 4-16 bbin_nrec ordenada exponencial
set output 'orden_exp_bbin_nrec_tiempo.png'
fit f(x) "orden_exp_bbin_nrec.log" using 1:2 via a,b
plot "orden_exp_bbin_nrec.log" using 1:2 with lines, f(x)

set output 'orden_exp_bbin_nrec_ob.png'
fit f(x) "orden_exp_bbin_nrec.log" using 1:3 via a,b
plot "orden_exp_bbin_nrec.log" using 1:3 with lines, f(x)


# BUSQUEDA LINEAL

f(x) = a*x + b

# 5-16 blin ordenada equiprobable
set output 'orden_equi_blin_tiempo.png'
fit f(x) "orden_equi_blin.log" using 1:2 via a,b
plot "orden_equi_blin.log" using 1:2 with lines, f(x)

set output 'orden_equi_blin_ob.png'
fit f(x) "orden_equi_blin.log" using 1:3 via a,b
plot "orden_equi_blin.log" using 1:3 with lines, f(x)

# 6-16 blin ordenada exponencial
set output 'orden_exp_blin_tiempo.png'
fit f(x) "orden_exp_blin.log" using 1:2 via a,b
plot "orden_exp_blin.log" using 1:2 with lines, f(x)

set output 'orden_exp_blin_ob.png'
fit f(x) "orden_exp_blin.log" using 1:3 via a,b
plot "orden_exp_blin.log" using 1:3 with lines, f(x)

# 7-16
set output 'orden_equi_blin_rec_tiempo.png'
fit f(x) "orden_equi_blin_rec.log" using 1:2 via a,b
plot "orden_equi_blin_rec.log" using 1:2 with lines, f(x)

set output 'orden_equi_blin_rec_ob.png'
fit f(x) "orden_equi_blin_rec.log" using 1:3 via a,b
plot "orden_equi_blin_rec.log" using 1:3 with lines, f(x)

# 8-16
set output 'orden_exp_blin_rec_tiempo.png'
fit f(x) "orden_exp_blin_rec.log" using 1:2 via a,b
plot "orden_exp_blin_rec.log" using 1:2 with lines, f(x)

set output 'orden_exp_blin_rec_ob.png'
fit f(x) "orden_exp_blin_rec.log" using 1:3 via a,b
plot "orden_exp_blin_rec.log" using 1:3 with lines, f(x)

# 9-16
set output 'orden_equi_blin_auto_tiempo.png'
fit f(x) "orden_equi_blin_auto.log" using 1:2 via a,b
plot "orden_equi_blin_auto.log" using 1:2 with lines, f(x)

set output 'orden_equi_blin_auto_ob.png'
fit f(x) "orden_equi_blin_auto.log" using 1:3 via a,b
plot "orden_equi_blin_auto.log" using 1:3 with lines, f(x)

# 10-16
set output 'orden_exp_blin_auto_tiempo.png'
fit f(x) "orden_exp_blin_auto.log" using 1:2 via a,b
plot "orden_exp_blin_auto.log" using 1:2 with lines, f(x)

set output 'orden_exp_blin_auto_ob.png'
fit f(x) "orden_exp_blin_auto.log" using 1:3 via a,b
plot "orden_exp_blin_auto.log" using 1:3 with lines, f(x)

# 11-16
set output 'orden_no_equi_blin_tiempo.png'
fit f(x) "orden_no_equi_blin.log" using 1:2 via a,b
plot "orden_no_equi_blin.log" using 1:2 with lines, f(x)

set output 'orden_no_equi_blin_ob.png'
fit f(x) "orden_no_equi_blin.log" using 1:3 via a,b
plot "orden_no_equi_blin.log" using 1:3 with lines, f(x)

# 12-16
set output 'orden_no_exp_blin_tiempo.png'
fit f(x) "orden_no_exp_blin.log" using 1:2 via a,b
plot "orden_no_exp_blin.log" using 1:2 with lines, f(x)

set output 'orden_no_exp_blin_ob.png'
fit f(x) "orden_no_exp_blin.log" using 1:3 via a,b
plot "orden_no_exp_blin.log" using 1:3 with lines, f(x)

# 13-16
set output 'orden_no_equi_blin_rec_tiempo.png'
fit f(x) "orden_no_equi_blin_rec.log" using 1:2 via a,b
plot "orden_no_equi_blin_rec.log" using 1:2 with lines, f(x)

set output 'orden_no_equi_blin_rec_ob.png'
fit f(x) "orden_no_equi_blin_rec.log" using 1:3 via a,b
plot "orden_no_equi_blin_rec.log" using 1:3 with lines, f(x)

# 14-16
set output 'orden_no_exp_blin_rec_tiempo.png'
fit f(x) "orden_no_exp_blin_rec.log" using 1:2 via a,b
plot "orden_no_exp_blin_rec.log" using 1:2 with lines, f(x)

set output 'orden_no_exp_blin_rec.png'
fit f(x) "orden_no_exp_blin_rec.log" using 1:3 via a,b
plot "orden_no_exp_blin_rec.log" using 1:3 with lines, f(x)

# 15-16
set output 'orden_no_equi_blin_auto_tiempo.png'
fit f(x) "orden_no_equi_blin_auto.log" using 1:2 via a,b
plot "orden_no_equi_blin_auto.log" using 1:2 with lines, f(x)

set output 'orden_no_equi_blin_auto_ob.png'
fit f(x) "orden_no_equi_blin_auto.log" using 1:3 via a,b
plot "orden_no_equi_blin_auto.log" using 1:3 with lines, f(x)

# 16-16
set output 'orden_no_exp_blin_auto_tiempo.png'
fit f(x) "orden_no_exp_blin_auto.log" using 1:2 via a,b
plot "orden_no_exp_blin_auto.log" using 1:2 with lines, f(x)

set output 'orden_no_exp_blin_auto_ob.png'
fit f(x) "orden_no_exp_blin_auto.log" using 1:3 via a,b
plot "orden_no_exp_blin_auto.log" using 1:3 with lines, f(x)


