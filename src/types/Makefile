OBJS=types.o

OUT=types.a

INCDIRS=-I.. -I../ast

all: $(OUT)


$(OUT): $(OBJS)
	$(AR) rvs $(OUT) $(OBJS)

%.o: %.cpp %.h
	$(CXX) $(LLVMCXXFLAGS) $(CXXFLAGS) -c $< $(INCDIRS) -o $@ 

clean:
	rm -f $(OBJS) $(OUT)


