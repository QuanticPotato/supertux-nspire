#  supertux-nspire
#  Copyright (C) 2014 CHAUVIN Barnabe <barnabe.chauvin@gmail.com>
#  
#  This program is free software; you can redistribute it and/or
#  modify it under the terms of the GNU General Public License
#  as published by the Free Software Foundation; either version 2
#  of the License, or (at your option) any later version.
#
#  This program is distributed in the hope that it will be useful,
#  but WITHOUT ANY WARRANTY; without even the implied warranty of
#  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#  GNU General Public License for more details.
#
#  You should have received a copy of the GNU General Public License
#  along with this program; if not, write to the Free Software
#  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.

RM=rm
MAKE=make
MOVE=mv

MAKER_EXE=./resources-maker/resource_maker
SCANNER_EXE=./resources-scanner/scanner

RAW_FILENAME=sprites.h
ARRAY_FILENAME=data_manager.cpp
RAW_FILEPATH=../src/$(RAW_FILENAME)
ARRAY_FILEPATH=../src/$(ARRAY_FILENAME)
STRING_FILENAME=text_files.h
STRING_FILEPATH=../src/$(STRING_FILENAME)

DATA_FOLDER=../data/

.PHONY: clean

all: $(RAW_FILEPATH) $(ARRAY_FILEPATH) $(STRING_FILEPATH)

$(RAW_FILEPATH) : $(MAKER_EXE) $(SCANNER_EXE) FORCE
	$(SCANNER_EXE) $(DATA_FOLDER) $(ARRAY_FILENAME) $(RAW_FILENAME) $(STRING_FILENAME) $(MAKER_EXE)
	$(MOVE) $(RAW_FILENAME) $(RAW_FILEPATH)

$(ARRAY_FILEPATH) : $(RESOURCE_MAKER) $(RESOURCE_SCANNER) FORCE
	$(MOVE) $(ARRAY_FILENAME) $(ARRAY_FILEPATH)

$(STRING_FILEPATH) : $(RESOURCE_MAKER) $(RESOURCE_SCANNER) FORCE
	$(MOVE) $(STRING_FILENAME) $(STRING_FILEPATH)

$(MAKER_EXE) : 
	$(MAKE) -C resources-maker

$(SCANNER_EXE) :
	$(MAKE) -C resources-scanner

FORCE:

clean:
	$(RM) -f $(MAKER_EXE) $(SCANNER_EXE)

