COMPILER=gcc 
FLAGS= -Wall -pedantic -std=c99 -lm -fsanitize=address
ROOTNAME=arbolesADT
VAN_LABEL=VAN
BUE_LABEL=BUE
OUTPUT_BUE=$(ROOTNAME)$(BUE_LABEL)
OUTPUT_VAN=$(ROOTNAME)$(VAN_LABEL)
OFILES=botanicalADT.o civilADT.o

all: buildVAN buildBUE clean

clean: 
	rm *.o

buildVAN: mainVAN.o manageCSVVAN.o botanicalADT.o civilADT.o
	$(COMPILER) $(FLAGS) -D $(VAN_LABEL) -o $(OUTPUT_VAN) $(OFILES) mainVAN.o manageCSVVAN.o
	
buildBUE: mainBUE.o manageCSVBUE.o botanicalADT.o civilADT.o
	$(COMPILER) $(FLAGS) -D $(BUE_LABEL) -o $(OUTPUT_BUE) $(OFILES)  mainBUE.o manageCSVBUE.o


mainBUE.o: main.c
	$(COMPILER) $(FLAGS) -D $(BUE_LABEL) -o mainBUE.o -c main.c

mainVAN.o: main.c
	$(COMPILER) $(FLAGS) -D $(VAN_LABEL) -o mainVAN.o -c main.c


manageCSVBUE.o: manageCSV.c
	$(COMPILER) $(FLAGS) -D $(BUE_LABEL) -o manageCSVBUE.o -c manageCSV.c

manageCSVVAN.o: manageCSV.c
	$(COMPILER) $(FLAGS) -D $(VAN_LABEL) -o manageCSVVAN.o -c manageCSV.c


botanicalADT.o: botanicalADT.c
	$(COMPILER) $(FLAGS) -o botanicalADT.o -c botanicalADT.c

civilADT.o: civilADT.c
	$(COMPILER) $(FLAGS) -o civilADT.o -c civilADT.c
