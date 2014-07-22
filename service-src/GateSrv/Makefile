

CXX = g++
# debug
ifdef RELEASE
CXXFLAGS =  -g  -I../../include -I../../alpaca-src -IInc -O3 -fPIC
CXXLFLAGS =  -g -Wall  -lglog -ldl -lzmq -rdynamic
else
CXXFLAGS =  -g  -I../../include -I../../alpaca-src -I../../service-src  -IInc -O0 -fPIC
CXXLFLAGS =  -g -Wall  -lglog -ldl -lzmq -rdynamic
endif

OBJS = $(patsubst %.cpp,%.o,$(wildcard *.cpp))
SRCS = $(OBJS:%.o=%.cpp)
DEPS = $(OBJS:%.o=%.d)


SHARED := -fPIC --shared
TARGET_DIR = ../../services

ALL_TARGETS = ../../services/GateSrv.so

all: $(ALL_TARGETS)

-include $(DEPS)
$(DEPS): %.d: %.cpp
	@$(CXX) -M $(CXXFLAGS) $< > $@.$$$$; sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < $@.$$$$ > $@; rm -f $@.$$$$

$(OBJS): %.o: %.cpp
	$(CXX) -c $(CXXFLAGS) $< -o $@

$(ALL_TARGETS): $(OBJS) $(DEPS)
	$(CXX) $(SHARED) $(OBJS) -o  $@ $(CXXLFLAGS) 
	
clean:
	@rm -rf $(OBJS) $(ALL_TARGETS) $(DEPS)
