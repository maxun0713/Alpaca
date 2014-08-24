

CXX = g++
# debug
ifdef RELEASE
CXXFLAGS =  -g  -I../../include -I../../ -O3 -fPIC
CXXLFLAGS =  -g -Wall  -lprotobuf  -lglog 
else
CXXFLAGS =  -g  -I../../include -I../../ -O0 -fPIC
CXXLFLAGS =  -g -Wall  -lprotobuf   -lglog 
endif

OBJS = $(patsubst %.cpp,%.o,$(wildcard *.cpp))
SRCS = $(OBJS:%.o=%.cpp)
DEPS = $(OBJS:%.o=%.d)


SHARED := -fPIC --shared
TARGET_DIR = ../../services

ALL_TARGETS = ../../services/Timer.so

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
