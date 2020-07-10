COMPILER=gcc 
FLAGS= -Wall -pedantic -std=c99
ROOTNAME=procesarArboles
OUTPUT_BUE=$(ROOTNAME)BUE
OUTPUT_VAN=$(ROOTNAME)VAN
VAN_LABEL=VAN
BUE_LABEL=BUE
HFILES=manageCSV.h botanicalADT.h civilADT.h 
CFILES=main.c manageCSV.c botanicalADT.c civilADT.c

clean: 
	rm $(OUTPUT_FILE) $(FILES)

build:  $(CFILES) $(HFILES)
	$(COMPILER) $(FLAGS) -D $(VAN_LABEL) -o $(OUTPUT_VAN) $(CFILES)
	$(COMPILER) $(FLAGS) -D $(BUE_LABEL) -o $(OUTPUT_BUE) $(CFILES)

