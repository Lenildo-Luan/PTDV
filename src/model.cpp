#include "../include/model.hpp"

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

void Model::initData(){
    typesOfTasks = 3;
}
void Model::addVariables(){
    //Cria matriz
    x = IloArray< IloBoolVarArray >(this->_env, _data.n);

    //Adiciona vetores a matriz
    for(int i = 0; i < _data.n; i++) {
        IloBoolVarArray vetor_i(this->_env, typesOfTasks);
        x[i] = vetor_i;
    }

    //Adiciona variáveis ao modelo
    for(int i = 0; i < _data.n; i++) {
        for(int j = 0; j < typesOfTasks; j++) {
            try {
                x[i][j].setName(std::string("x" + std::to_string(i) + "_" + std::to_string(j)).c_str());
            } catch(...) {
                std::cout << "ERRO AO ADICIONAR VARIÁVEL" << std::endl;
            }
        }
    }
}
void Model::addObjFunction(){
    IloExpr FO(this->_env), FO2(this->_env);

    for(int i = 0; i < _data.n; i++) {
        for(int j = 0; j < typesOfTasks; j++) {
            FO += this->x[i][j] * _data.C[i][j];
            FO2 += this->x[i][j] * _data.Tau[i][j];
        }
    }

    FO2 = (FO2 - _data.D) * _data.M;
    FO += FO2;

    this->_model.add(IloMinimize(this->_env, FO));
}
void Model::addConstraints(){
    for(int i = 0; i < _data.n; i++) {
        IloExpr sumX(_env);

        for(int j = 0; j < typesOfTasks; j++) {
            sumX += x[i][j];
        }       

        IloConstraint c1 = (sumX == 1);

        char c_name[32];
        sprintf(c_name, "c_1(%d)", i);
        c1.setName((char*) c_name);
        _model.add(c1);

        sumX.end();
    }
}
void Model::initCplexFromModel(){
    this->_cplex = IloCplex(_model);
}
void Model::solve(){
    this->_cplex.exportModel("modelo.lp");

    try {
        this->_cplex.solve();
    } catch(IloException e) {
        std::cerr <<"Error" <<  ": " << e.getMessage() << std::endl;
    }

    std::cout << "status: " << this->_cplex.getStatus() << std::endl;
    std::cout << "FO: " << _cplex.getObjValue() << std::endl;
    std::cout << "x: " << std::endl;

    int resultado = 0, dias = 0;

    for(int i = 0; i < _data.n; i++){
        for(int j = 0; j < typesOfTasks; j++){
            resultado +=  _cplex.getValue(x[i][j]) * _data.C[i][j];
            dias +=  _cplex.getValue(x[i][j]) * _data.Tau[i][j];
            std::cout << _cplex.getValue(x[i][j]) << " ";
        }
        std::cout << std::endl;
    }

    std::cout << resultado + (dias - _data.D) * _data.M << std::endl;
    
}
void Model::generateDot(){

}