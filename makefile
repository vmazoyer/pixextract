# the compiler: gcc for C program, define as g++ for C++
CXX = g++

CXXFLAGS = `pkg-config --cflags opencv` -Wall
LDFLAGS = `pkg-config --libs opencv` -lm

# the build target executable:
TARGET = pixextract

all: $(TARGET)

$(TARGET): $(TARGET).cpp
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o $(TARGET) $(TARGET).cpp

clean:
	$(RM) $(TARGET)
