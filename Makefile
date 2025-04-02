CXX = g++
CXXFLAGS = -Isrc/include -Isrc/include/SDL2 -Igame -Lsrc/lib
LIBS = -lSDL2 -lSDL2main -lSDL2_image -lSDL2_ttf
SRCS = main.cpp game/ship/ship.cpp game/shipbullet/shipbullet.cpp game/alien/alien.cpp
OBJS = $(SRCS:.cpp=.o)
TARGET = main.exe

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LIBS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

clean:
	del /Q $(OBJS) $(TARGET) 2>nul || rm -f $(OBJS) $(TARGET)

run: $(TARGET)
	./$(TARGET)