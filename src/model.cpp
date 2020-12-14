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
    std::cout << "Cronograma: " << std::endl;

    std::vector<int> result = getOrder(_data);
    std::reverse(result.begin(), result.end());
    int totalTime = 0, taskCost = 0;

    for(int i = 0; i < result.size(); i++){
        std::cout << "Tarefa ";
        for (int j = 0; j < 3; j++){
            if(_cplex.getValue(x[i][j])){
                totalTime += _data.Tau[i][j];
                taskCost += _data.C[i][j];
                std::cout << result[i] + 1 << " - " << _data.Tau[i][j] << " dias - " << "R$ " <<  _data.C[i][j] << std::endl;   
            }
        }
    }

    std::cout << "Tempo total do projeto: " << totalTime << " dias" << std::endl;
    std::cout << "Custo com multa: R$ " << (((totalTime - _data.D) * _data.M) < 0 ? 0 : ((totalTime - _data.D) * _data.M)) << std::endl;
    std::cout << "Custo com tarefas: R$ " << taskCost << std::endl;
    std::cout << "Custo total do projeto: R$ " << (((totalTime - _data.D) * _data.M) < 0 ? taskCost : _cplex.getObjValue()) << std::endl;

    std::cout << std::endl;    
}
void Model::topsort(int v, std::vector<int>& visited, std::vector<std::vector<int>>& graph, std::vector<int>&result)
{
    visited[v] = 1;
    for (int u = 0; u < graph.size(); ++u) {
        if (!visited[u] && graph[v][u]) {
            topsort(u, visited, graph, result);
        }
    }
        result.push_back(v);
}
std::vector<int> Model::getOrder(Data data){
    std::vector<std::vector<int>> graph(data.n, std::vector<int>(data.n, 0));
    for(int i = 0; i < data.precedence.size(); i++){
        int a=data.precedence[i].first;
        int b=data.precedence[i].second;
        graph[a-1][b-1]=1;
    }
    std::vector<int> result(0,0);
    std::vector<int> visited(data.n, 0);
    for(int i = 0; i < data.n; i++){
        topsort(i, visited, graph, result);
        int AnyoneIsMissing=0;
        for(int j = 0; j < data.n; j++){
            if(!visited[j]){
                AnyoneIsMissing = true;
                break;
                }
        }
        if(!AnyoneIsMissing){
            break;
        }
    }
    return result;
}