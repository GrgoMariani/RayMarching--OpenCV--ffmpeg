CXX = g++
CXXFLAGS=-c -Wall -g -std=c++11 -m64
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
	$(CXX) -o $(EXECUTABLE) $(OBJS) $(LIBS)

main.o: main.cpp
	@echo "MAKING main.o"
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -c main.cpp

clean:
	@echo "CLEANING"
	$(RM) $(OBJS)

distclean: clean
	@echo "DISTCLEANING"
	$(RM) $(EXECUTABLE)
	

