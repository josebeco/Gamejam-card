all: build run

build:
	g++ -o game Main.cpp lib/*.cpp simulador/*.cpp   -lGL  -lglut

run: build
	./game


win:
	g++ -o game Main.cpp  lib/Screen.cpp lib/Draw.cpp lib/HandlerSprites.cpp simulador/jogo.cpp  simulador/efeitoCartas.cpp  simulador/HandlerCarta.cpp -lopengl32 -lfreeglut -lkernel32 -user32


git:
	git config --global user.name josebeco
	git config --global user.email jose.p.sambatti@gmail.com

