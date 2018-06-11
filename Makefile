CXX = g++
DEFINES= -DWITH_OPENMP
CXXFLAGS=-c -Wall -g -std=c++11 -m64 $(DEFINES)
OPENMP= -fopenmp
LDFLAGS= -lpthread

# Environment 
MKDIR=mkdir
CP=cp
RM=rm -f
CCADMIN=CCadmin

OPENCV= `pkg-config opencv --cflags --libs`
LIBS= $(OPENCV)
EXECUTABLE= raymarching

SOURCES= main.cpp
OBJS=$(subst .cpp,.o,$(SOURCES))

all: $(EXECUTABLE)
	
$(EXECUTABLE): $(OBJS)
	@echo "MAKING EXECUTABLE"
	$(CXX) -o $(EXECUTABLE) $(OBJS) $(LIBS) $(OPENMP)

main.o: main.cpp
	@echo "MAKING main.o"
	$(CXX) $(OPENMP) $(CXXFLAGS) $(LDFLAGS) -c main.cpp

clean:
	@echo "CLEANING"
	$(RM) $(OBJS)

distclean: clean
	@echo "DISTCLEANING"
	$(RM) $(EXECUTABLE)
	

