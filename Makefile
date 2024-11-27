all: build run

build:
	g++ -o game Main.cpp lib/Screen.cpp -lglut -lGLU -lGL 

run: build
	./game

git:
	git config --global user.name josebeco
	git config --global user.email jose.p.sambatti@gmail.com

