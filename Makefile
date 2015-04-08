THIS_BUILD_DIR="build/codegen"
BUILD_DIR="../build"

all:
	mkdir -p $(THIS_BUILD_DIR)
	cd src && make BUILD_DIR=$(BUILD_DIR)
	cp build/compile .

clean:
	cd src && make clean BUILD_DIR=$(BUILD_DIR)