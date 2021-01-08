SHELL = /bin/sh
.POSIX:

# version
VERSION = 0.0
PROJ_NAME = baca

#paths
PREFIX = /usr/local
MANPREFIX = ${PREFIX}/share/man

#includes and libs
LIBS=

#flags
#no debug:
CFLAGS= -std=c99 -pedantic -Wall -Wno-deprecated-declarations -Os
#debug:
#CFLAGS= -g -std=c99 -pedantic -Wall -Wno-deprecated-declarations -Os

#compiler and linker
CC=gcc
#cleaning program
RM=rm -rf
