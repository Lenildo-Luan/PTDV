#include <string>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <algorithm>
#include "../include/data.hpp"
#include "../include/model.hpp"

int main(){
	std::string path = "./instances/proj1.txt";
	
	Data data(path);
	data.printData();

    Model model(data);
    model.solve();
	
	return 0;
}