# Nom de l'exécutable final
TARGET = build/main.out

# Fichiers source
SRC = ./univ/main.c ./platforms/Linux/glad.c
SRCTEST = ./univ/tests.c ./platforms/Linux/glad.c

# Compilateur
CC = gcc

# Options de compilation
CFLAGS = -Wall -Wextra -O2 `pkg-config --cflags sdl3`

# Options d'édition de liens (SDL3 + OpenGL)
LDFLAGS = `pkg-config --libs sdl3` -ldl -lm -lGL

# Règle par défaut
all: $(TARGET)

# Règle de compilation
$(TARGET): $(SRC)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET) $(LDFLAGS)

# Compile le test / exemple
example: $(TARGET)

# Règle de compilation
$(TARGET): $(SRCTEST)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(SRCTEST) -o $(TARGET) $(LDFLAGS)



# Nettoyage
clean:
	rm -rf build

.PHONY: all clean
