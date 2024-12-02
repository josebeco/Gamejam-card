all: build run

build:
	g++ -o game Main.cpp code/*.cpp lib/*.cpp simulador/*.cpp -lglut -lGLU -lGL -lSDL2

run: build
	./game

static:
	g++ -o game Main.cpp code/*.cpp lib/*.cpp simulador/*.cpp -lglut -lGLU -lGL -lSDL2 -static

win:
	x86_64-w64-mingw32-g++ -o game Main.cpp code/*.cpp lib/*.cpp simulador/*.cpp -lglut -lGLU -lGL -lSDL2 -static

git:
	git config --global user.name josebeco
	git config --global user.email jose.p.sambatti@gmail.com

