#include "map.h"
#include <stdio.h>
#include <string>

int main() {

	map<std::string> culo;
	
	culo.insert(10, "a");
	culo.insert(1, "b");
	culo.insert(2, "c");
	culo.insert(15, "d");

	culo.printTree(culo.root());

	return 6;
}