all:
	cd src && make
	cp src/compile .

clean:
	cd src && make clean