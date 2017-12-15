BIN ?= build/decompiler
CFLAGS = -I ./src
TEST = 1

include ./Makefile.compile

.PHONY: count

count:
	find ./test ./src -name "*.cc" -or -name "*.h" | xargs cat | wc -l
