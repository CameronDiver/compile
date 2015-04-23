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
SUBLIBS_DEPENDS = */*.h */*.cpp

GLOBAL_DEPENDS = ast/*.h builtins.h
EXE = compile

ALL: $(EXE)


$(EXE): $(SUBLIBS) $(OBJS) 
	$(CXX) $(CXXFLAGS) $(OBJS) $(SUBLIBS) $(LDFLAGS) -o $(EXE)


%.o: %.cpp %.h $(GLOBAL_DEPENDS)
	$(CXX) -c $(CXXFLAGS) -o $@ $<

%.o: %.cpp $(GLOBAL_DEPENDS)
	$(CXX) -c $(CXXFLAGS) -o $@ $<

%.a: force_look
	@#echo $(wildcard $(dir $@)*.cpp) $(wildcard $(dir $@)*.h)
	@#echo $(dir $@)*.cpp $(dir $@)*.h
	cd $(dir $@) && $(MAKE) CXXFLAGS="$(CXXFLAGSPRE)" CXX="$(CXX)" LLVMCXXFLAGS="$(LLVMCXX)"

clean:
	$(foreach target, $(SUBLIBS_MAKE), cd $(target) && $(MAKE) clean && cd ..;)
	rm $(OBJS)

force_look:
	true
