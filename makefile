# Arquivo Makefile

all: calc clean
	@echo "Compilação Concluída!"
	@echo "Pare executar digite: ./calc"

calc: main.o
	g++ -g -Wall main.o -o calc

clean:
	rm *.o
