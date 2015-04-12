CC=clang
CXX=clang++

LLVM_CONFIG = llvm-config-3.5

CXXFLAGS = -I`$(LLVM_CONFIG) --includedir --cxxflags` -Iast/ -I. -Wall -std=c++11 -DDEBUG -g
LDFLAGS  = `$(LLVM_CONFIG) --ldflags --system-libs --libs core native bitwriter`

CODEGEN_DIR=$(BUILD_DIR)/codegen

OBJS = $(BUILD_DIR)/ast.o $(BUILD_DIR)/builtins.o $(BUILD_DIR)/main.o $(BUILD_DIR)/token.o \
$(CODEGEN_DIR)/intliteral.o $(CODEGEN_DIR)/binaryoperation.o $(CODEGEN_DIR)/call.o\
$(CODEGEN_DIR)/floatliteral.o $(CODEGEN_DIR)/functiondef.o $(CODEGEN_DIR)/codegen.o\
$(CODEGEN_DIR)/functionbody.o $(CODEGEN_DIR)/symbolref.o $(CODEGEN_DIR)/variableinit.o\
$(CODEGEN_DIR)/ifstatement.o $(CODEGEN_DIR)/whilestatement.o
GLOBAL_DEPENDS = ast/*.h builtins.h
EXE = $(BUILD_DIR)/compile

ALL: $(EXE)


$(EXE): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) $(LDFLAGS) -o $(EXE)


$(BUILD_DIR)/%.o: %.cpp %.h $(GLOBAL_DEPENDS)
	$(CXX) -c $(CXXFLAGS) -o $@ $<

$(BUILD_DIR)/%.o: %.cpp $(GLOBAL_DEPENDS)
	$(CXX) -c $(CXXFLAGS) -o $@ $<

clean:
	rm $(OBJS)
