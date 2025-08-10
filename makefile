TARGET = build/main.out
TESTTARGET = build/tests.out

SRC = ./univ/main.c ./platforms/Linux/glad.c
SRCTEST = ./univ/tests.c ./platforms/Linux/glad.c

CFLAGS = -Wall -Wextra -O2 `pkg-config --cflags sdl3` ${EXTRA_CFLAGS}
LDFLAGS = `pkg-config --libs sdl3` -ldl -lm -lGL

all: $(TARGET)

$(TARGET): $(SRC)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET) $(LDFLAGS)

$(TESTTARGET): $(SRCTEST)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(SRCTEST) -o $(TESTTARGET) $(LDFLAGS)

example: $(TESTTARGET)

clean:
	rm -rf build

.PHONY: all clean example test
