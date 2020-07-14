COMPILER=gcc 
FLAGS= -Wall -pedantic -std=c99 -lm -fsanitize=address
ROOTNAME=procesarArboles
OUTPUT_BUE=$(ROOTNAME)BUE
OUTPUT_VAN=$(ROOTNAME)VAN
VAN_LABEL=VAN
BUE_LABEL=BUE
HFILES=manageCSV.h botanicalADT.h civilADT.h
CFILES=main.c manageCSV.c botanicalADT.c civilADT.c
OFILES=$(SOURCES:.c=.o)

all: build clean

clean: 
	rm *.o

build:  $(OFILES) 
	$(COMPILER) $(FLAGS) -D $(VAN_LABEL) -o $(OUTPUT_VAN) $(OFILES)
	$(COMPILER) $(FLAGS) -D $(BUE_LABEL) -o $(OUTPUT_BUE) $(OFILES)


main.o: main.c
	$(COMPILER) $(FLAGS) -c main.c


manageCSV.o: manageCSV.c
	$(COMPILER) $(FLAGS) -c manageCSV.c


botanicalADT.o: botanicalADT.c
	$(COMPILER) $(FLAGS) -c botanicalADT.c
