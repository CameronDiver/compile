CC=clang
CXX=clang++

LLVM_CONFIG = llvm-config-3.5

CXXFLAGS = -I`$(LLVM_CONFIG) --includedir --cxxflags` -Wall -std=c++11 -DDEBUG -g
LDFLAGS  = `$(LLVM_CONFIG) --ldflags --system-libs --libs core`

OBJS = $(BUILD_DIR)/ast.o $(BUILD_DIR)/builtins.o $(BUILD_DIR)/main.o $(BUILD_DIR)/token.o
GLOBAL_DEPENDS = ast/*.h
EXE = $(BUILD_DIR)/compile

ALL: $(EXE)


$(EXE): $(OBJS)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $(OBJS) -o $(EXE)


$(BUILD_DIR)/%.o: %.cpp %.h $(GLOBAL_DEPENDS)
	$(CXX) -c $(CXXFLAGS) -o $@ $<

$(BUILD_DIR)/%.o: %.cpp $(GLOBAL_DEPENDS)
	$(CXX) -c $(CXXFLAGS) -o $@ $<

clean:
	rm $(OBJS)
