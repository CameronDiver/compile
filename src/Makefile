CC=clang
CXX=clang++

LLVM_CONFIG = llvm-config-3.5

INCDIRS=-Iast/ -I.
LLVMCXX=`$(LLVM_CONFIG) --cxxflags`
CXXFLAGSPRE=-Wall -std=c++11 -DDEBUG -g
CXXFLAGS= $(CXXFLAGSPRE) $(LLVMCXX) $(INCDIRS)
LDFLAGS  = `$(LLVM_CONFIG) --ldflags --system-libs --libs core native bitwriter mcjit jit` -rdynamic

CODEGEN_DIR=$(BUILD_DIR)/codegen

OBJS = ast.o builtins.o main.o token.o jit.o

SUBLIBS = types/types.a codegen/codegen.a
SUBLIBS_MAKE = types codegen

GLOBAL_DEPENDS = ast/*.h builtins.h
EXE = compile

ALL: $(EXE)


$(EXE): $(OBJS)
	$(foreach target, $(SUBLIBS_MAKE), cd $(target) && $(MAKE) CXXFLAGS="$(CXXFLAGSPRE)" CXX="$(CXX)" LLVMCXXFLAGS="$(LLVMCXX)" && cd ..;)
	$(CXX) $(CXXFLAGS) $(OBJS) $(SUBLIBS) $(LDFLAGS) -o $(EXE)


%.o: %.cpp %.h $(GLOBAL_DEPENDS)
	$(CXX) -c $(CXXFLAGS) -o $@ $<

%.o: %.cpp $(GLOBAL_DEPENDS)
	$(CXX) -c $(CXXFLAGS) -o $@ $<

clean:
	$(foreach target, $(SUBLIBS_MAKE), cd $(target) && $(MAKE) clean && cd ..;)
	rm $(OBJS)
