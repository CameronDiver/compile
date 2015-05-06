OBJS=binaryoperation.o call.o codegen.o floatliteral.o functionbody.o\
functiondef.o ifstatement.o intliteral.o symbolref.o variableinit.o\
whilestatement.o unaryoperation.o

OUT=codegen.a

INCDIRS=-I.. -I../ast

all: $(OUT)


$(OUT): $(OBJS)
	ar rvs $(OUT) $(OBJS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(INCDIRS) $(LLVMCXXFLAGS) -c $<  -o $@ 

%.o: %.cpp %.h
	$(CXX) $(CXXFLAGS) $(INCDIRS) $(LLVMCXXFLAGS) -c $<  -o $@ 

clean:
	rm -f $(OBJS) $(OUT)