CXX = g++
CXXFLAGS = -Isrc/include -Isrc/include/SDL2 -Icore/init -Icore/window -Icore/game -Iobjects/ship -Iobjects/alien -Iobjects/shipbullet -Iobjects/alienbullet -Lsrc/lib -L/usr/lib -L/usr/local/lib
LIBS = -lSDL2 -lSDL2main -lSDL2_image -lSDL2_ttf -lSDL2_mixer
SRCS = main.cpp core/game/game.cpp objects/ship/ship.cpp objects/shipbullet/shipbullet.cpp objects/alien/alien.cpp objects/alienbullet/alienbullet.cpp core/init/init.cpp core/window/window.cpp menu/menu.cpp
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