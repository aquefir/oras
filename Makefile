###############################################################################
##                             Oracion Assembler                             ##
##                                                                           ##
##                        Copyright (C) 2022 Aquefir.                        ##
##                  Released under Artisan Software Licence                  ##
###############################################################################

ifeq ($(strip $(AQ)),)
$(error "AQ was not found in your environment. You need to install the Slick Makefiles from github.com/aquefir/slick to continue.")
endif

include $(AQ)/lib/slick/base.mk

# name of project. used in output binary naming
PROJECT := oras

# put a '1' for the desired target types to compile
EXEFILE := 1
SOFILE  :=
AFILE   :=

# space-separated path list for #includes
# <system> includes
INCLUDES :=
# "local" includes
INCLUDEL := src

# space-separated library name list
LIBS    := uni_err uni_himem uni_log uni_str
LIBDIRS :=

# '3P' are in-tree 3rd-party dependencies
# 3PLIBDIR is the base directory
# 3PLIBS is the folder names in the base directory for each library
3PLIBDIR :=
3PLIBS   :=

# frameworks (macOS target only)
FWORKS :=

# sources
CFILES    := \
	src/lexer.c \
	src/main.c
PRVHFILES := \
	src/lexer.h \
	src/main.h

# this defines all our usual targets
include $(AQ)/lib/slick/targets.mk
