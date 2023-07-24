BUILD_DIR=bin
BINARY=game
windows:
	gcc src/*.c -Wall -std=c99 -Wno-missing-braces -L lib/ms-windows -lraylib -lopengl32 -lgdi32 -lwinmm -o $(BUILD_DIR)/$(BINARY)-windows
r:
	bin/*
linux:
	gcc src/*.c*.c -Wall -std=c99 -Wno-missing-braces -L lib/gnu-linux -lraylib -lglfw -lGL -lm -lpthread -ldl -lrt -lX11 -o $(BUILD_DIR)/$(BINARY)-linux

mac:
	clang --std=c99 src/*.c*.c -L lib/mac-osx -framework CoreVideo -framework IOKit -framework Cocoa -framework GLUT -framework OpenGL lib/mac-os -o $(BUILD_DIR)$(BINARY)-macos

clean:
	rm $(BUILD_DIR)/*
