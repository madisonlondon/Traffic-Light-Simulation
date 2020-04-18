EXECS = testSimulation

OBJS = testSimulation.o TrafficLight.o Vehicle.o Lane.o Roadway.o Animator.o VehicleBase.o

#### use next two lines for Mac
#CC = clang++
#CCFLAGS = -std=c++11 -stdlib=libc++

#### use next two lines for mathcs* machines:
CC = g++
CCFLAGS = -std=c++11 -g

all: $(EXECS)

testSimulation: $(OBJS)
	$(CC) $(CCFLAGS) $^ -o $@

%.o: %.cpp *.h
	$(CC) $(CCFLAGS) -c $<

%.o: %.cpp
	$(CC) $(CCFLAGS) -c $<

clean:
	/bin/rm -f a.out $(OBJS) $(EXECS)
