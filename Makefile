


CXX = g++
# debug
ifdef RELEASE
CXXFLAGS =  -g  -Iinclude -O3
CXXLFLAGS =  -g -Wall  -lprotobuf -levent -lglog
else
CXXFLAGS =  -g  -Iinclude -O0
CXXLFLAGS =  -g -Wall  -lprotobuf  -levent -lglog
endif


OBJS = $(patsubst %.cpp,%.o,$(wildcard *.cpp))
SRCS = $(OBJS:%.o=%.cpp)
DEPS = $(OBJS:%.o=%.d)

ALL_TARGETS = Alpaca

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