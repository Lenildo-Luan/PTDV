#include "../include/data.hpp"

void Data::printData(){
	printf("n:%d D:%d M:%d\n", n, D, M);
	// Matriz de custo da tarefa j executando no tipo e
	for(int t = 0; t < 3; t++){
		for(int j = 0; j < n; j++){
			printf("%5d", C[j][t]);
		}
		puts("");
	}
	// Matriz de tempo para executar a tarefa j executando no tipo e
	for(int t = 0; t < 3; t++){
		for(int j = 0; j < n; j++){
			printf("%4d", Tau[j][t]);
		}
		puts("");
	}
	// Lista de precendencia
	for(int i = 0; i < n; i++){
		printf("%4d %4d\n", precedence[i].first, precedence[i].second);
	}
}

void Data::readInstance(){
	char aux_c[64] = "";
	int aux_i = 0, aux_i2 = 0;
	fscanf(fp, "NAME : %s\n", aux_c);
	this->name_instance = std::string(aux_c);
	fscanf(fp, "SIZE : %i\n", &aux_i);
	this->n = aux_i;
	fscanf(fp, "DEADLINE : %i\n", &aux_i);
	this->D = aux_i;
	fscanf(fp, "FINE : %i\n", &aux_i);
	fscanf(fp, "NODE_DURATION\n");
	this->M = aux_i;
	this->Tau = std::vector<std::vector<int>>(this->n, std::vector<int>(3, 0));
	for(int t = 0; t < 3; t++){
		for(int j = 0; j < this->n; j++){
			fscanf(fp, "%d", &this->Tau[j][t]);
		}
	}
	fscanf(fp, "\nNODE_COST\n");
	this->C = std::vector<std::vector<int>>(this->n, std::vector<int>(3, 0));
	for(int t = 0; t < 3; t++){
		for(int j = 0; j < this->n; j++){
			fscanf(fp, "%d", &this->C[j][t]);
		}
	}
	fscanf(fp, "\nPRECEDENCE\n");
	this->precedence = std::vector<std::pair<int, int>>(n, std::make_pair(0,0));
	for(int i = 0; i < n; i++){
		fscanf(fp, "%d %d\n", &aux_i, &aux_i2);
		precedence[i] = std::make_pair(aux_i, aux_i2);
	}
	return;
}

Data::Data(std::string path_to_instance){
	this->path = path_to_instance;
	this->fp = fopen(path_to_instance.data(), "r");

	if(!fp){
		throw "Error when opening instance file!";
	}
	
	readInstance();
}

