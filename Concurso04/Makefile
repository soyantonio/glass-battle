CPP = g++
SRCS := $(wildcard *.cpp)
BINS := $(SRCS:%.cpp=run.%)
RUNS := $(SRCS:%.cpp=%)

all: ${BINS} ${RUNS}

%: run.%
	@./$<

run.%: %.cpp
	${CPP} $< -o $@
