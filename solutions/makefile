CC      = clang++
CFLAGS  = -std=c++11 -stdlib=libc++ -I/usr/local/include/ -L/usr/local/lib/ 
LIBS = -lboost_unit_test_framework
RM      = rm -rf

SRC=$(wildcard *.cpp)
EXE=$(SRC:.cpp=)
dSYM=$(SRC:.cpp=.dSYM)

default: all

all: $(EXE)

%: %.cpp
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

clean:
	$(RM) $(EXE) $(dSYM)