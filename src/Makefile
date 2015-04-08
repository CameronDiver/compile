CC=clang
CXX=clang++

LLVM_CONFIG = llvm-config-3.5

CXXFLAGS = -I`$(LLVM_CONFIG) --includedir --cxxflags` -Iast/ -I. -Wall -std=c++11 -DDEBUG -g
LDFLAGS  = `$(LLVM_CONFIG) --ldflags --system-libs --libs core`

OBJS = $(BUILD_DIR)/ast.o $(BUILD_DIR)/builtins.o $(BUILD_DIR)/main.o $(BUILD_DIR)/token.o \
$(BUILD_DIR)/codegen/intliteral.o $(BUILD_DIR)/codegen/binaryoperation.o $(BUILD_DIR)/codegen/call.o\
$(BUILD_DIR)/codegen/floatliteral.o $(BUILD_DIR)/codegen/functiondef.o $(BUILD_DIR)/codegen/codegen.o\
$(BUILD_DIR)/codegen/functionbody.o
GLOBAL_DEPENDS = ast/*.h
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
