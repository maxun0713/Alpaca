


CXX = g++
# debug
ifdef RELEASE
CXXFLAGS =  -g  -Iinclude -O3
CXXLFLAGS =  -g -Wall  -lprotobuf -levent -lglog -ldl
else
CXXFLAGS =  -g  -Iinclude -O0
CXXLFLAGS =  -g -Wall  -lprotobuf  -levent -lglog -ldl
endif

OBJS = $(patsubst %.cpp,%.o,$(wildcard *.cpp))
SRCS = $(OBJS:%.o=%.cpp)
DEPS = $(OBJS:%.o=%.d)


SHARED := -fPIC --shared
MODULES = Modules
SERVICES = services
IO_ENGINE_OBJS = $(patsubst $(MODULES)/IOEngine/%.cpp, \
	$(MODULES)/IOEngine/%.o,$(wildcard $(MODULES)/IOEngine/*.cpp))

ALL_TARGETS = Alpaca

all: $(ALL_TARGETS)

-include $(DEPS)
$(DEPS): %.d: %.cpp
	@$(CXX) -M $(CXXFLAGS) $< > $@.$$$$; sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < $@.$$$$ > $@; rm -f $@.$$$$

$(OBJS): %.o: %.cpp
	$(CXX) -c $(CXXFLAGS) $< -o $@

$(ALL_TARGETS): $(OBJS) $(DEPS)
	$(CXX) $(OBJS) -o  $@ $(CXXLFLAGS) 

$(IO_ENGINE):
	$(CXX) 
	
clean:
	@rm -rf $(OBJS) $(ALL_TARGETS) $(DEPS)
