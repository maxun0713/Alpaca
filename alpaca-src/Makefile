

CXX = g++
# debug
ifdef RELEASE
CXXFLAGS =  -g  -I../../include -I../../alpaca-src -IInc -O3 -fPIC
CXXLFLAGS =  -g -Wall  -lglog -ldl -lprotobuf -lzmq -rdynamic
else
CXXFLAGS =  -g   -O0 -fPIC -I../include -Iinclude
CXXLFLAGS =  -g -Wall  -lglog -ldl -lprotobuf -lzmq -rdynamic -ltinyxml -L../lib
endif

OBJS = $(patsubst %.cpp,%.o,$(wildcard *.cpp))
SRCS = $(OBJS:%.o=%.cpp)
DEPS = $(OBJS:%.o=%.d)

ALL_TARGETS = ../lib/libalpaca.a

all: $(ALL_TARGETS)

-include $(DEPS)
$(DEPS): %.d: %.cpp
	@$(CXX) -M $(CXXFLAGS) $< > $@.$$$$; sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < $@.$$$$ > $@; rm -f $@.$$$$

$(OBJS): %.o: %.cpp
	$(CXX) -c $(CXXFLAGS) $< -o $@

$(ALL_TARGETS): $(OBJS) $(DEPS)
	@ar cru $(ALL_TARGETS) $(OBJS)  
	@ranlib $(ALL_TARGETS)
clean:
	@rm -rf $(OBJS) $(ALL_TARGETS) $(DEPS)
