CXX = g++
CXXFLAGS = -Isrc/include -Isrc/include/SDL2 -Icore/init -Icore/window -Icore/game -Iobjects/ship -Iobjects/alien -Iobjects/shipbullet -Iobjects/alienbullet -Lsrc/lib -L/usr/lib -L/usr/local/lib -w
LIBS = -lmingw32 -lSDL2main -lSDL2 -lSDL2_mixer -lSDL2_image -lSDL2_ttf
SRCS = main.cpp core/game/game.cpp objects/ship/ship.cpp objects/shipbullet/shipbullet.cpp objects/alien/alien.cpp objects/alienbullet/alienbullet.cpp core/init/init.cpp core/window/window.cpp menu/menu.cpp
OBJS = $(SRCS:.cpp=.o)
TARGET = main.exe

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LIBS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

clean:
	del /Q main.o core\game\game.o objects\ship\ship.o objects\shipbullet\shipbullet.o objects\alien\alien.o objects\alienbullet\alienbullet.o core\init\init.o core\window\window.o menu\menu.o main.exe

run: $(TARGET)
	./$(TARGET)