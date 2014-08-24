

CXX = g++
# debug
ifdef RELEASE
CXXFLAGS =  -g  -I../include -I../../alpaca-src -IInc -O3 -fPIC
CXXLFLAGS =  -g -Wall  -lglog -ldl -lprotobuf -lzmq -rdynamic
else
CXXFLAGS =  -g  -I../include -I../alpaca-src/include -O0 
CXXLFLAGS =  -g -Wall  -L../lib -L../alpaca-src  -lalpaca -ltinyxml -ldl -lglog -lzmq -lprotobuf -levent  -rdynamic
endif

OBJS = $(patsubst %.cpp,%.o,$(wildcard *.cpp))
SRCS = $(OBJS:%.o=%.cpp)
DEPS = $(OBJS:%.o=%.d)

TARGET_DIR = ../../services

ALL_TARGETS = GateSrv

all: $(ALL_TARGETS)

-include $(DEPS)
$(DEPS): %.d: %.cpp
	@$(CXX) -M $(CXXFLAGS) $< > $@.$$$$; sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < $@.$$$$ > $@; rm -f $@.$$$$

$(OBJS): %.o: %.cpp
	$(CXX)  -c $(CXXFLAGS) $< -o $@

$(ALL_TARGETS): $(OBJS) $(DEPS)
	$(CXX)  $(OBJS) -o  $@ $(CXXLFLAGS) 
	
clean:
	@rm -rf $(OBJS) $(ALL_TARGETS) $(DEPS)
