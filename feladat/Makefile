all:
	gcc -Iinclude/ src/app.c src/camera.c src/main.c src/scene.c src/texture.c src/utils.c src/ship.c src/apache.c src/mapbox.c -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lobj -lopengl32 -lm -o apache.exe -Wall -Wextra -Wpedantic

linux:
	gcc -Iinclude/ src/app.c src/camera.c src/main.c src/scene.c src/texture.c src/utils.c src/ship.c src/apache.c src/mapbox.c -lobj -lSDL2 -lSDL2_image -lGL -lm -o apache -Wall -Wextra -Wpedantic
