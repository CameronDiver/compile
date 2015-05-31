CC=gcc
CPP=g++

CFLAGS=-std=c++11 -Wno-write-strings

LIBS=-ll

LEX=flex
YACC=bison

YACCFLAGS=-d

LEXFILE=lex.l
YACCFILE=parse.ypp

LEXOUTFILES=lex.yy.c
YACCOUTFILES=parse.tab.cpp parse.tab.hpp


OBJS= parse.o parse.tab.o

OUT=parse

all: build

build: $(LEXOUTFILES) $(YACCOUTFILES) realbuild

realbuild: $(OBJS)
	$(CPP) $(LEXOUTFILES) $(CFLAGS) $(OBJS) -o $(OUT) $(LIBS)

$(LEXOUTFILES): $(LEXFILE)
	$(LEX) $(LEXFILE)

$(YACCOUTFILES): $(YACCFILE)
	$(YACC) $(YACCFLAGS) $(YACCFILE)

%.o: %.cpp %.h
	$(CPP) $(CFLAGS) -c -o $@ $<

%.o: %.cpp
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm $(OBJS)
	rm $(LEXOUTFILES) $(YACCOUTFILES)

