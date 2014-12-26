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

DATA_FOLDER=../data/
CONFIG_FILE=config

# This files will be generated in the Makefile directory, and then deleted
FIRST_FILENAME=levels_files.h
FILENAMES=$(FIRST_FILENAME) levels_index.cpp sprites.h sprites_index.cpp text_files.h
SRC_FOLDER=../src/
# Append the source directory, in order to move the generated files
#FILEPATH=$(foreach file, $(FILENAMES), $(SRC_FOLDER)/$(file))
FILEPATH=$(SRC_FOLDER)/$(FIRST_FILENAME)

.PHONY: clean

# We only deal with the first file to avoid repeating the rules for every files 
# (Since they are all generated/moved at the same time)

all: $(FILEPATH)

$(FILEPATH) : $(FIRST_FILENAME)
	$(MOVE) $(FILENAMES) $(SRC_FOLDER)

$(FIRST_FILENAME): $(MAKER_EXE) $(SCANNER_EXE) FORCE
	$(SCANNER_EXE) $(DATA_FOLDER) $(CONFIG_FILE) $(MAKER_EXE)

$(MAKER_EXE) : 
	$(MAKE) -C resources-maker

$(SCANNER_EXE) :
	$(MAKE) -C resources-scanner

FORCE:

clean:
	$(RM) -f $(MAKER_EXE) $(SCANNER_EXE)

