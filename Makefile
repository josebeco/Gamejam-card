all: build run

build:
	g++ -o game Main.cpp code/*.cpp lib/*.cpp -lglut -lGLU -lGL -lSDL2

run: build
	./game

git:
	git config --global user.name josebeco
	git config --global user.email jose.p.sambatti@gmail.com

