#ifndef PARSE_PATH_MANAGER_H
#define PARSE_PATH_MANAGER_H

#include <cstdio>
#include <string>
#include <stack>

class PathManager {
public:

	struct FileInfo {
		// The path up to and including the last /
		std::string path;
		// the name of the file without the preceeding /
		std::string name;
	};

	PathManager();

	void addPath(const char *filepath);
	void addPath(const std::string &filepath);

	FILE *openImport(const char *image);
	FILE *openImport(const std::string &image);


private:
	std::stack<FileInfo> paths;
};

#endif
