CC=clang
CPP=clang++

NODEDIR=nodes

CFLAGS=-Wall -DDEBUG -g
CPPFLAGS=-Wall -std=c++11 -Wno-write-strings -Wno-deprecated-register -g -DDEBUG

LIBS=-ll

LEX=flex
YACC=bison

YACCFLAGS=-d

LEXFILE=lex.l
YACCFILE=parse.ypp

LEXOUTFILES=lex.yy.c
YACCOUTFILE=parse.tab.cpp
YACCOUTFILES=parse.tab.cpp parse.tab.hpp

YACCOBJ=parse.tab.o
LEXOBJ=lex.yy.o

GLOBALS=parse.h $(wildcard $(NODEDIR)/*.h)

OBJS= parse.o $(YACCOBJ) $(LEXOBJ)

OUT=parse

all: build

build: $(LEXOUTFILES) $(YACCOUTFILES) realbuild

realbuild: $(OBJS)
	$(CPP) $(CPPFLAGS) $(OBJS) -o $(OUT) $(LIBS)

$(LEXOUTFILES): $(LEXFILE) $(GLOBALS)
	$(LEX) $(LEXFILE)

$(YACCOUTFILE): $(YACCFILE) $(GLOBALS)
	$(YACC) $(YACCFLAGS) $(YACCFILE)

%.o: %.cpp %.h $(GLOBALS)
	$(CPP) $(CPPFLAGS) -c -o $@ $<

$(YACCOBJ): $(YACCOUTFILES)
	$(CPP) $(CPPFLAGS) -c -o $@ $<

$(LEXOBJ): $(LEXOUTFILES)
	$(CPP) $(CPPFLAGS) -Wno-unused-function -Wno-unneeded-internal-declaration -c -o $@ $<

clean:
	rm $(OBJS) $(LEXOUTFILES) $(YACCOUTFILES)

