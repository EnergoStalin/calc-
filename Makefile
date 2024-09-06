.PHONY: all build debug clean lint dvi dist test install uninstall intellisense
.RECIPEPREFIX = >

INSTALL_DIR ?= ./install

DISTFILE=dist.tar
.RECIPEPREFIX=>

LINTFILES=$(shell find src -type f  -name '*.c' -or -name '*.cc' -or -name '*.h')

all: build test gcov_report

build:
> xmake config -m release
> xmake build -g bin

debug:
> xmake config -m debug
> xmake build -g bin

clean:
> xmake clean

format:
> clang-format -i --style=Google $(LINTFILES)

lint:
> clang-format -n --style=Google $(LINTFILES)
> [ "$(which s21lint)" == "" ] && s21lint $(LINTFILES)

dvi:
> @echo "Compile .md docs are you insane? This is the best format ever that dont need compilation every format rather should compile to it."

dist: install
> mkdir -p $(INSTALL_DIR)/dist
> cp $(INSTALL_DIR)/bin/app $(INSTALL_DIR)/lib/* $(INSTALL_DIR)/README.md $(INSTALL_DIR)/dist
> tar -c $(INSTALL_DIR)/dist -f $(DISTFILE)

test:
> xmake config -m release
> xmake build -g test
> xmake run -g test

install: build
> mkdir -p $(INSTALL_DIR)
> cp -r docs $(INSTALL_DIR)
> xmake install -o $(INSTALL_DIR) -g bin

run: install
> LD_LIBRARY_PATH="$(INSTALL_DIR)/lib" "$(INSTALL_DIR)/bin/app" $(ARGS)

uninstall:
> rm -r $(INSTALL_DIR)

gcov_report:
> xmake config -m coverage
> xmake build -g test
> xmake run -vg test
> xdg-open report/index.html

fclean:
> xmake clean --all
> rm -rf build $(DISTFILE) report

intellisense:
> xmake config -m release
> xmake project -k compile_commands
