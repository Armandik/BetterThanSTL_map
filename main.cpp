#include "map.h"
#include <stdio.h>
#include <map>
#include <chrono>

#define INSERTION				// insertion of n elements
//#define DELETE_RANDOM_ELEMENTS	// deletion of m elements
//#define CLEAR					// clear the map from all elements
#define PRINT					// in order print of the map
//#define RANDOM_OPERATIONS		// performs a number of random operations (insert, erase and search)

int main() {

	srand(time(NULL));

	map<int> myMap;
	std::map<int, int> stlMap;
	
	auto start = std::chrono::high_resolution_clock::now();
	auto stop = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);

	int n = 500;			// number of elements to insert
	int m = 2000;			// number of elements to randomly delete
	int range = 10000;		// range of elements that will be randomly inserted/deleted
	int randomOps = 50000;	// number of random operations to perform

#ifdef INSERTION
	start = std::chrono::high_resolution_clock::now();
	for (int i = 0; i < n; i++) {
		int x = rand() % range;
		myMap.insert(x, x);
	}
	stop = std::chrono::high_resolution_clock::now();

	duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
	std::cout << "my map, inserted " << myMap.size() << " elements in " << float(duration.count()) / 1000 << " ms\n";



	start = std::chrono::high_resolution_clock::now();
	for (int i = 0; i < n; i++) {
		int x = rand() % range;
		stlMap.insert(std::pair<int, int>(x, x));
	}
	stop = std::chrono::high_resolution_clock::now();

	duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
	std::cout << "stl map, inserted " << stlMap.size() << " elements in " << float(duration.count()) / 1000 << " ms\n\n";
#endif

#ifdef DELETE_RANDOM_ELEMENTS
	start = std::chrono::high_resolution_clock::now();
	for (int i = 0; i < m; i++) {
		int x = rand() % range;
		myMap.erase(x);
	}
	stop = std::chrono::high_resolution_clock::now();
	duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
	std::cout << "my map, deleted " << m << " elements in " << float(duration.count()) / 1000 << " ms\n";

	start = std::chrono::high_resolution_clock::now();
	for (int i = 0; i < m; i++) {
		int x = rand() % range;
		stlMap.erase(x);
	}
	stop = std::chrono::high_resolution_clock::now();
	duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
	std::cout << "stl map, deleted " << m << " elements in " << float(duration.count()) / 1000 << " ms\n\n";
#endif

#ifdef CLEAR
	start = std::chrono::high_resolution_clock::now();
	myMap.clear();
	stop = std::chrono::high_resolution_clock::now();
	duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
	std::cout << "my map cleared in: " << float(duration.count()) / 1000 << " ms\n";

	start = std::chrono::high_resolution_clock::now();
	stlMap.clear();
	stop = std::chrono::high_resolution_clock::now();
	duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
	std::cout << "stl map cleared in: " << float(duration.count()) / 1000 << " ms\n\n";
#endif

#ifdef PRINT
	start = std::chrono::high_resolution_clock::now();
	std::cout << "My map printed in order:\n";
	myMap.printTree(myMap.root());	
	stop = std::chrono::high_resolution_clock::now();
	duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
	std::cout << "my map was printed in: " << float(duration.count()) / 1000 << " ms\n\n";

	start = std::chrono::high_resolution_clock::now();	
	std::cout << "STL map printed in order:\n";
	for (auto& p : stlMap)
		std::cout << p.second << "\n";
	stop = std::chrono::high_resolution_clock::now();
	duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
	std::cout << "stl map was printed in: " << float(duration.count()) / 1000 << " ms\n\n";
#endif

#ifdef RANDOM_OPERATIONS
	start = std::chrono::high_resolution_clock::now();
	for (int i = 0; i < randomOps; i++) {
		int op = rand() % 3;

		switch (op) {
		case 0: {
			int x = rand() % range;
			myMap.insert(x, x);
			break;
		}
		case 1: {
			int x = rand() % range;
			myMap.erase(x);
			break;
		}
		case 2: {
			int x = rand() % range;
			myMap.search(x);
		}
		}
	}
	stop = std::chrono::high_resolution_clock::now();
	duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
	std::cout << "my map performed " << randomOps << " random operations in " << float(duration.count()) / 1000 << " ms\n";

	start = std::chrono::high_resolution_clock::now();
	for (int i = 0; i < randomOps; i++) {
		int op = rand() % 3;

		switch (op) {
		case 0: {
			int x = rand() % range;
			stlMap.insert(std::pair<int, int>(x, x));
			break;
		}
		case 1: {
			int x = rand() % range;
			stlMap.erase(x);
			break;
		}
		case 2: {
			int x = rand() % range;
			stlMap.find(x);
		}
		}
	}
	stop = std::chrono::high_resolution_clock::now();
	duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
	std::cout << "stl map performed " << randomOps << " random operations in " << float(duration.count()) / 1000 << " ms\n\n";
#endif
	return 0;
}