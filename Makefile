CC = gcc -ansi -pedantic
CFLAGS = -Wall -O3
EXE = ejercicio1 ejercicio2 ejercicio1b ejercicio2b

all : $(EXE)

.PHONY : clean
clean :
	rm -f *.o core $(EXE)

$(EXE) : % : %.o ordenar.o busqueda.o tiempos.o
	@echo "#---------------------------"
	@echo "# Generando $@ "
	@echo "# Depende de $^"
	@echo "# Ha cambiado $<"
	$(CC) $(CFLAGS) -o $@ $@.o ordenar.o busqueda.o tiempos.o

%.o : %.c ordenar.h busqueda.h tiempos.h
	@echo "#---------------------------"
	@echo "# Generando $@"
	@echo "# Depende de $^"
	@echo "# Ha cambiado $<"
	$(CC) $(CFLAGS) -c $<

ejer1:
	@echo Ejecutando comprobacion.
	@./ejercicio1 -tamanio 100000 -clave 10 

ejer2:
	@echo Ejecutando tiempos.
	@valgrind --track-origins=yes ./ejercicio2 -num_min 1000 -num_max 100000 -incr 10000 -fclaves 10 -numP 10000 -fichSalida tiempo.log

comprobacion:
	@echo Ejecutando comprobacion.
	@valgrind ./ejercicio1b -funcion blin -orden si -tamanio 10000 -clave 9999

experimentos:
	@echo Ejecutando 1 de 14.
	@./ejercicio2b -funcion blin -orden no -generador normal -num_min 1000 -num_max 100000 -incr 1000 -fclaves 1 -numP 1 -fichSalida 1_blin.log

	@echo Ejecutando 2 de 14.
	@./ejercicio2b -funcion bbin -orden si -generador normal -num_min 1000 -num_max 100000 -incr 1000 -fclaves 1 -numP 1 -fichSalida 1_bbin.log

	@echo Ejecutando 3 de 14.
	@./ejercicio2b -funcion blin_auto -orden no -generador potencial -num_min 100 -num_max 100 -incr 1 -fclaves 1 -numP 1 -fichSalida 2_blin_auto_1.log

	@echo Ejecutando 4 de 14.
	@./ejercicio2b -funcion bbin -orden si -generador potencial -num_min 100 -num_max 100 -incr 1 -fclaves 1 -numP 1 -fichSalida 2_bbin_1.log

	@echo Ejecutando 5 de 14.
	@./ejercicio2b -funcion blin_auto -orden no -generador potencial -num_min 100 -num_max 100 -incr 1 -fclaves 10 -numP 1 -fichSalida 2_blin_auto_10.log

	@echo Ejecutando 6 de 14.
	@./ejercicio2b -funcion bbin -orden si -generador potencial -num_min 100 -num_max 100 -incr 1 -fclaves 1 -numP 10 -fichSalida 2_bbin_10.log

	@echo Ejecutando 7 de 14.
	@./ejercicio2b -funcion blin_auto -orden no -generador potencial -num_min 100 -num_max 100 -incr 1 -fclaves 100 -numP 1 -fichSalida 2_blin_auto_100.log

	@echo Ejecutando 8 de 14.
	@./ejercicio2b -funcion bbin -orden si -generador potencial -num_min 100 -num_max 100 -incr 1 -fclaves 1 -numP 100 -fichSalida 2_bbin_100.log

	@echo Ejecutando 9 de 14.
	@./ejercicio2b -funcion blin_auto -orden no -generador potencial -num_min 100 -num_max 100 -incr 1 -fclaves 1000 -numP 1 -fichSalida 2_blin_auto_1000.log

	@echo Ejecutando 10 de 14.
	@./ejercicio2b -funcion bbin -orden si -generador potencial -num_min 100 -num_max 100 -incr 1 -fclaves 1 -numP 1000 -fichSalida 2_bbin_1000.log

	@echo Ejecutando 11 de 14.
	@./ejercicio2b -funcion blin_auto -orden no -generador potencial -num_min 100 -num_max 100 -incr 1 -fclaves 10000 -numP 1 -fichSalida 2_blin_auto_10000.log

	@echo Ejecutando 12 de 14.
	@./ejercicio2b -funcion bbin -orden si -generador potencial -num_min 100 -num_max 100 -incr 1 -fclaves 1 -numP 10000 -fichSalida 2_bbin_10000.log

	@echo Ejecutando 13 de 14.
	@./ejercicio2b -funcion blin_auto -orden no -generador potencial -num_min 100 -num_max 100 -incr 1 -fclaves 100000 -numP 1 -fichSalida 2_blin_auto_100000.log

	@echo Ejecutando 14 de 14.
	@./ejercicio2b -funcion bbin -orden si -generador potencial -num_min 100 -num_max 100 -incr 1 -fclaves 1 -numP 100000 -fichSalida 2_bbin_100000.log

	@echo FIN.

simulacion: bbin blin

bbin:
	@echo Ejecutando prueba 1 de 16.
	@./ejercicio2b -funcion bbin -orden si -generador normal -num_min 100000 -num_max 1000000 -incr 100000 -fclaves 50 -numP 1 -fichSalida orden_equi_bbin.log

	@echo Ejecutando prueba 2 de 16.
	@./ejercicio2b -funcion bbin -orden si -generador potencial -num_min 100000 -num_max 1000000 -incr 100000 -fclaves 50 -numP 1 -fichSalida orden_exp_bbin.log

	@echo Ejecutando prueba 3 de 16.
	@./ejercicio2b -funcion bbin_nrec -orden si -generador normal -num_min 100000 -num_max 1000000 -incr 100000 -fclaves 50 -numP 1 -fichSalida orden_equi_bbin_nrec.log

	@echo Ejecutando prueba 4 de 16.
	@./ejercicio2b -funcion bbin_nrec -orden si -generador potencial -num_min 100000 -num_max 1000000 -incr 100000 -fclaves 50 -numP 1 -fichSalida orden_exp_bbin_nrec.log

blin:
	@echo Ejecutando prueba 5 de 16.
	@./ejercicio2b -funcion blin -orden si -generador normal -num_min 1000 -num_max 10000 -incr 1000 -fclaves 50 -numP 1 -fichSalida orden_equi_blin.log

	@echo Ejecutando prueba 6 de 16.
	@./ejercicio2b -funcion blin -orden si -generador potencial -num_min 1000 -num_max 10000 -incr 1000 -fclaves 50 -numP 1 -fichSalida orden_exp_blin.log

	@echo Ejecutando prueba 7 de 16.
	@./ejercicio2b -funcion blin_rec -orden si -generador normal -num_min 1000 -num_max 10000 -incr 1000 -fclaves 50 -numP 1 -fichSalida orden_equi_blin_rec.log

	@echo Ejecutando prueba 8 de 16.
	@./ejercicio2b -funcion blin_rec -orden si -generador potencial -num_min 1000 -num_max 10000 -incr 1000 -fclaves 50 -numP 1 -fichSalida orden_exp_blin_rec.log

	@echo Ejecutando prueba 9 de 16.
	@./ejercicio2b -funcion blin_auto -orden si -generador normal -num_min 1000 -num_max 10000 -incr 1000 -fclaves 50 -numP 1 -fichSalida orden_equi_blin_auto.log

	@echo Ejecutando prueba 10 de 16.
	@./ejercicio2b -funcion blin_auto -orden si -generador potencial -num_min 1000 -num_max 10000 -incr 1000 -fclaves 50 -numP 1 -fichSalida orden_exp_blin_auto.log

	@echo Ejecutando prueba 11 de 16.
	@./ejercicio2b -funcion blin -orden no -generador normal -num_min 1000 -num_max 10000 -incr 1000 -fclaves 50 -numP 1 -fichSalida orden_no_equi_blin.log

	@echo Ejecutando prueba 12 de 16.
	@./ejercicio2b -funcion blin -orden no -generador potencial -num_min 1000 -num_max 10000 -incr 1000 -fclaves 50 -numP 1 -fichSalida orden_no_exp_blin.log

	@echo Ejecutando prueba 13 de 16.
	@./ejercicio2b -funcion blin_rec -orden no -generador normal -num_min 1000 -num_max 10000 -incr 1000 -fclaves 50 -numP 1 -fichSalida orden_no_equi_blin_rec.log

	@echo Ejecutando prueba 14 de 16.
	@./ejercicio2b -funcion blin_rec -orden no -generador potencial -num_min 1000 -num_max 10000 -incr 1000 -fclaves 50 -numP 1 -fichSalida orden_no_exp_blin_rec.log

	@echo Ejecutando prueba 15 de 16.
	@./ejercicio2b -funcion blin_auto -orden no -generador normal -num_min 1000 -num_max 10000 -incr 1000 -fclaves 50 -numP 1 -fichSalida orden_no_equi_blin_auto.log

	@echo Ejecutando prueba 16 de 16.
	@./ejercicio2b -funcion blin_auto -orden no -generador potencial -num_min 1000 -num_max 10000 -incr 1000 -fclaves 50 -numP 1 -fichSalida orden_no_exp_blin_auto.log

	@echo FIN.



