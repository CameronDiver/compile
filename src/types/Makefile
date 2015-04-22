OBJS=types.o sint.o uint.o float.o double.o longint.o longuint.o 

OUT=types.a

INCDIRS=-I.. -I../ast

all: $(OUT)


$(OUT): $(OBJS)
	$(AR) rvs $(OUT) $(OBJS)

%.o: %.cpp %.h
	$(CXX) $(LLVMCXXFLAGS) $(CXXFLAGS) -c $< $(INCDIRS) -o $@ 

clean:
	rm -f $(OBJS) $(OUT)


