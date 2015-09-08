TARGET=	cas-mpt
SRCS=	mpt.cpp mptwrap.cpp
CXX=	g++
OPT=	-O2

PKG=		libopenmpt

include compiler.mk
include audacious.mk

mpt.o: mptwrap.h
mptwrap.o: mptwrap.h
