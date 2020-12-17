# Planejamento de Tarefas com Duração Variável (PTDV)

O PTDV se trata de um problema de otimização combinatória passado pelo professor da disciplina de Pesquisa Operacional do curso de Engenharia de Computação da Universidade Federal da Paraíba.

Para entender o problema, imagine um escritório de engenharia com um determinado projeto. Este projeto é dividido em N tarefas, cada uma com uma duração de execução e três modos de execução, seu tempo pode ser acelerado por um valor ou acelerado ainda mais por um valor mais alto. Alem disso, o projeto tem uma deadline associada e uma multa é paga para cada dia de atraso. Por último, algumas tarefas possuem dependência de outras, sendo necessário algumas tarefas serem realizadas para que outras também possam ser. O objetivo deste problema, é encontrar a melhora alocação de recursos possível (modo e ordem de execução das atividades) para se ter o menor custo com atividades e multas no projeto.

## Formas de resolução

Existem dois métodos que podem ser seguidos para resolver problemas como o descrito anteriormente, os exatos ou os heurísticos.

Métodos exatos visam iterar sobre todo o conjunto de soluções de um problema para obter sua resposta. Por conta disso, eles retornam a solução ótima do problema, ou seja, a melhor dentre todas as soluções. Por outro lado, em algumas situações, o tempo computacional necessário para se resolver alguns problemas por este método é inviável.

Existê também os métodos heurísticos. Eles tentam resolver estes problemas com um tempo computacional aceitável, porém sem garantir sua otimalidade. Assim como as meta-heurísticos, que tem a mesma finalidade, porém com o intuito de resolver vários tipos de problemas diferentes com um mesmo algoritmo. Por mais que a otimalidade não seja garantida, muitas heurísticas e meta-heurísticas conseguem encontrar resultados ótimos ou muito próximo deles para uma grande gama de problemas.

O PTDV foi resolvido de forma exata, através de técnicas de modelagem matemática baseadas no problema da [designação](https://en.wikipedia.org/wiki/Assignment_problem), com um pós processamento utilizando [ordenação topológica](https://en.wikipedia.org/wiki/Topological_sorting).

## Instância do PTDV

A instância do PTDV encontra-se na pasta `./include` e foi montada a partir dos dados passados pelo professor da disciplina. Nela encontram-se as matrizes de tempo, custo e precedência, assim como outras informações a respeito do problema.

## Compilando e executando

Para compilar o programa, basta utilizar o comando `make` pelo terminal na pasta raiz, gerando o arquivo executável `PTDV`. Basta executar o arquivo gerado para visualizar o resultado.

``` bash
./PTDV
```

## Resultados

> O algorítimo ainda se encontra em fase de implementação,

## TODO

* Criar tabela com os resultados computacionais