

CXX = g++
# debug
CXXFLAGS =  -g   -I../alpaca -I./ -O0 
CXXLFLAGS =  -g -Wall  -lpthread -lgtest -rdynamic  -L./lib

COMMON_DIR=../alpaca
OBJS = $(patsubst %.cpp,%.o,$(wildcard *.cpp)) $(patsubst $(COMMON_DIR)/%.cpp, $(COMMON_DIR)/%.o,$(wildcard $(COMMON_DIR)/*.cpp)) 

SRCS = $(OBJS:%.o=%.cpp)
DEPS = $(OBJS:%.o=%.d)


ALL_TARGETS = test

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
