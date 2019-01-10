.phony: all clean

CPP_FILES=$(wildcard *.cpp)
O_FILES=$(patsubst %.cpp,%.o,$(CPP_FILES))
OUT_FILE=nuked-dashboard
CXXFLAGS=-Ispdlog/include -Inuklear

all: $(O_FILES)
	$(CXX) $(CXXFLAGS) $(O_FILES) -o $(OUT_FILE)

clean:
	-rm *.o
	-rm $(OUT_FILE)