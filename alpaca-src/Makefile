


CXX = g++
# debug
ifdef RELEASE
CXXFLAGS =  -g  -I../include  -I../service-src -I. -O3
CXXLFLAGS =  -g -Wall -L../lib  -lprotobuf -levent -lglog -ldl  -rdynamic
else
CXXFLAGS =  -g  -I../include -I../service-src -I. -O0
CXXLFLAGS =  -g -Wall -L../lib  -lprotobuf  -levent -lglog -ldl  -rdynamic
endif

OBJS = $(patsubst %.cpp,%.o,$(wildcard *.cpp))
SRCS = $(OBJS:%.o=%.cpp)
DEPS = $(OBJS:%.o=%.d)


ALL_TARGETS = ../GateSrv

all: $(ALL_TARGETS)

-include $(DEPS)
$(DEPS): %.d: %.cpp
	@$(CXX) -M $(CXXFLAGS) $< > $@.$$$$; sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < $@.$$$$ > $@; rm -f $@.$$$$

$(OBJS): %.o: %.cpp
	$(CXX) -c $(CXXFLAGS) $< -o $@

$(ALL_TARGETS): $(OBJS) $(DEPS)
	$(CXX) $(OBJS) -o  $@ $(CXXLFLAGS) 

	
clean:
	@rm -rf $(OBJS) $(ALL_TARGETS) $(DEPS)
