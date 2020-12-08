#include <string>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <algorithm>
#include "../include/data.hpp"

int main(){
	std::string path = "./instances/proj1.txt";
	
	Data data(path);
	data.printData();
	
	return 0;
}