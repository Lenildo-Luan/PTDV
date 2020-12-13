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

    // std::vector<int> result = getOrder(data);
    // for(int i : result){
    //     std::cout << i << " ";
    // }
    // std::cout << std::endl;
	
	return 0;
}