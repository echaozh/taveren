.PHONY: all deps clean check

all: debug release-build

check: debug
	LD_LIBRARY_PATH="build/debug:$$LD_LIBRARY_PATH" build/debug/test_tavn

debug: deps build/debug/Makefile
	make -C build/debug

release-build: deps build/release/Makefile
	make -C build/release

install: release-build
	make -C build/release install

clean:
	rm -rf build

build/debug/Makefile: | build/debug
	cd build/debug; \
	  cmake -DCMAKE_BUILD_TYPE=Debug ../..

build/release/Makefile: | build/release
	cd build/release; \
	  cmake -DCMAKE_BUILD_TYPE=RelWithDebInfo ../..

build/debug:
	mkdir -p $@

build/release:
	mkdir -p $@

deps:
	[ -d deps ] && make -C deps || true
