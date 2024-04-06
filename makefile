buildpath=build
bc=cmake
runpath=$(buildpath)/ogc

all: build

build:
	$(bc) -S . -B $(buildpath)
	make -C $(buildpath)

update: build
	make -C $(buildpath)

run: update
	./$(runpath)

del:
	rm -rf build

rebuild: del build

leaks: update
	leaks -atExit -- $(runpath)
