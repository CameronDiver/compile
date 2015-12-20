# compile
# A compiler for a custom language
The language aims to be as expressive as an interpreted language, but have the speed and type-checking given by compiling.

## State
The language started out with a custom recursive descent parser, which worked moderately well. After this the compiler used llvm
to generate either standalone binaries, or run JIT.

Currently the parsing system for the compiler is being changed, to use lex and yacc (flex and bison really...) which should 
be more stable given a correct grammar (WIP).


Most of the latest code is in other branches, to be shipped in when finished.

## Examples
TODO
