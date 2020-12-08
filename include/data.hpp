#pragma once
#include <string>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <algorithm>
#include <iostream>

struct Data{
	// Matriz de custo da tarefa j executando no tipo e
	std::vector<std::vector<int>> C;
	// Matriz de tempo para executar a tarefa j executando no tipo e
	std::vector<std::vector<int>> Tau;
	// Lista de precendencia
	std::vector<std::pair<int, int>> precedence;
	// Numero de tarefas, dias limite, multa
	int n, D, M;

	std::string name_instance;
	std::string path;
	
	Data(std::string path_to_instance);
	void printData();

	private:
	FILE* fp;
	void readInstance();
};