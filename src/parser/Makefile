CC=gcc
CPP=g++

CFLAGS=-Wall

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
	$(CPP) $(LEXOUTFILES) $(OBJS) -o $(OUT) $(LIBS)

$(LEXOUTFILES): $(LEXFILE)
	$(LEX) $(LEXFILE)

$(YACCOUTFILES): $(YACCFILE)
	$(YACC) $(YACCFLAGS) $(YACCFILE)

%.o: %.cpp
	$(CPP) $(CFLAGS) -c -o $@ $<

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm $(OBJS)
	rm $(LEXOUTFILES) $(YACCOUTFILES)

