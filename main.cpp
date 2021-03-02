#include "map.h"
#include <stdio.h>
#include <string>
#include <map>
#include <chrono>

int main() {

	map<int> mappaMia;
	std::map<int, int> mappaSTL;

	auto start = std::chrono::high_resolution_clock::now();
	auto stop = std::chrono::high_resolution_clock::now();

	for (int i = 0; i < 50; i++) {
		int x = rand();
		mappaMia.insert(x, x);
	}
	stop = std::chrono::high_resolution_clock::now();

	auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
	std::cout << "mappa mia, tempo: " << float(duration.count()) / 1000 << " millisecondi, " << mappaMia.size() << " elementi\n";

	start = std::chrono::high_resolution_clock::now();
	for (int i = 0; i < 50; i++) {
		long int x = rand();
		mappaSTL.insert(std::pair<int, int>(x, x));
	}
	stop = std::chrono::high_resolution_clock::now();

	duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
	std::cout << "mappa stl, tempo: " << float(duration.count()) / 1000 << " millisecondi, " << mappaSTL.size() << " elementi\n";;

	mappaMia.printTree(mappaMia.root());
	printf("\n");

	return 0;
}