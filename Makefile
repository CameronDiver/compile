BUILD_DIR="../build"

all:
	cd src && make BUILD_DIR=$(BUILD_DIR)
	cp build/compile .

clean:
	cd src && make clean BUILD_DIR=$(BUILD_DIR)