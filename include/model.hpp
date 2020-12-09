#pragma once
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
#include <string.h>
#include <ilcplex/ilocplex.h> 
#include "./data.hpp"

struct Model {
    int typesOfTasks;
    IloArray< IloBoolVarArray > x;
    
    IloModel _model;
    IloCplex _cplex;
    IloEnv _env;
    Data _data;

    Model(Data data);
    void solve();
    void generateDot();

private:
    void addObjFunction();
    void addVariables();
    void addConstraints(); 
    void initCplexFromModel();
    void initData();
};