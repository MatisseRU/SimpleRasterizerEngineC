TARGET = build/main.out
TESTTARGET = build/example.out

SRC = ./univ/main.c ./univ/glad.c ./univ/ring0.c ./univ/ring1.c ./univ/ring2.c
SRCTEST = ./univ/example.c ./univ/glad.c ./univ/ring0.c ./univ/ring1.c ./univ/ring2.c

CFLAGS = -Wall -Wextra -O2 `pkg-config --cflags sdl3` ${EXTRA_CFLAGS}
LDFLAGS = `pkg-config --libs sdl3` -ldl -lm -lGL

# Exécutables
$(TARGET): $(SRC)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET) $(LDFLAGS)

$(TESTTARGET): $(SRCTEST)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(SRCTEST) -o $(TESTTARGET) $(LDFLAGS)

# Cibles pratiques
all: $(TARGET)
example: $(TESTTARGET)

clean:
	rm -rf build

.PHONY: all clean example

