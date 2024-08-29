COMPILER = g++
OPTIONS = -std=c++17 -pedantic -Wall -Wextra -Wconversion -Wunreachable-code
COMPILE = $(COMPILER) $(OPTIONS)
LIBS = -Linclude/SFML-2.6.1/lib -lsfml-graphics-s -lsfml-window-s -lsfml-system-s -lwinmm -lgdi32 -lopengl32 -lfreetype
INCLUDES = -Iinclude/SFML-2.6.1/include -Iinclude/headers

game:
		$(COMPILE) $(INCLUDES) src/*.cpp -o app $(LIBS)

