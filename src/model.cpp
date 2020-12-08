#pragma once
#include <model.hpp>

Model::Model(Data data){
    this->_data = data;
    this->_env = IloEnv();
    this->_model = IloModel(this->_env);

    initData();
    addVariables();
    addObjFunction();
    addConstraints(); 
    initCplexFromModel();
}

void Model::addVariables(){

}
void Model::addObjFunction(){

}
void Model::addConstraints(){

}
void Model::initCplexFromModel(){
    this->_cplex = IloCplex(_model);
}
void Model::solve(){

}
void Model::initData(){

}
void Model::generateDot(){

}