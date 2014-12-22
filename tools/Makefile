RM=rm
MAKE=make
MOVE=mv

MAKER_EXE=./resources-maker/resource_maker
SCANNER_EXE=./resources-scanner/scanner

RAW_FILENAME=sprites.h
ARRAY_FILENAME=data_manager.cpp
RAW_FILEPATH=../src/$(RAW_FILENAME)
ARRAY_FILEPATH=../src/$(ARRAY_FILENAME)

DATA_FOLDER=../data/

.PHONY: clean

all: $(RAW_FILEPATH) $(ARRAY_FILEPATH)

$(RAW_FILEPATH) : $(MAKER_EXE) $(SCANNER_EXE) FORCE
	$(SCANNER_EXE) $(DATA_FOLDER) $(ARRAY_FILENAME) $(RAW_FILENAME) $(MAKER_EXE)
	$(MOVE) $(RAW_FILENAME) $(RAW_FILEPATH)

$(ARRAY_FILEPATH) : $(RESOURCE_MAKER) $(RESOURCE_SCANNER) FORCE
# Both files (raw and array) have alreay been generated
	$(MOVE) $(ARRAY_FILENAME) $(ARRAY_FILEPATH)

$(MAKER_EXE) : 
	$(MAKE) -C resources-maker

$(SCANNER_EXE) :
	$(MAKE) -C resources-scanner

FORCE:

clean:
	$(RM) -f $(MAKER_EXE) $(SCANNER_EXE)

