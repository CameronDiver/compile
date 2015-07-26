#include "pathman.h"

#ifdef DEBUG
	#include <iostream>
#endif
#include <sstream>

PathManager::PathManager() {

}

void PathManager::addPath(const char *filepath) {
	addPath(std::string(filepath));
}

void PathManager::addPath(const std::string &filepath) {
	FileInfo f;
	std::size_t idx = filepath.find_last_of('/');

	if(idx == std::string::npos){
		f.path = "./";
		f.name = filepath;
	} else {
		f.path = filepath.substr(0, idx+1);
		f.name = filepath.substr(idx+1);
	}

	paths.push(f);
}

FILE *PathManager::openImport(const char *image) {
	return openImport(std::string(image));
}

FILE *PathManager::openImport(const std::string &image) {
	// The path on the top of the info stack should be searched
	// for the include, along with any standard locations (TODO)

	FileInfo f = paths.top();

	std::stringstream joiner;
	joiner << f.path << image;
	std::string filePath = joiner.str();

	#ifdef DEBUG
		std::cout << "Opening and parsing: " << filePath << std::endl;
	#endif

	// Add the path to the top of the stack
	addPath(filePath);

	return fopen(filePath.c_str(), "r");
}
