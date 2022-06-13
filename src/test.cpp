#include "graph.hpp"
#include "input.hpp"
#include <gtest/gtest.h>
#include <list>
#include <vector>

using namespace std;

int numOfCities;
int numOfRoads;
int numOfQueries;

Graph roads;

list<pair<int, int>> queries;

TEST(input, readParameters) {
    const int CITIES = 9;
    const int ROADS = 14;
    const int QUERIES = 1;

    stringstream input("9 14 1");
    Input::readParameters(input);

    EXPECT_EQ(CITIES, numOfCities);
    EXPECT_EQ(ROADS, numOfRoads);
    EXPECT_EQ(QUERIES, numOfQueries);
}

TEST(input, readParametersExceptions) {

    string input;
    stringstream inputStream;

    // Número de cidades
    input = "1 15 16";
    inputStream.str(input);
    ASSERT_DEATH(Input::readParameters(inputStream),
                 "Número de cidades 1 é menor do que o esperado\n");

    input = "101 1 16";
    inputStream.str(input);
    ASSERT_DEATH(Input::readParameters(inputStream),
                 "Número de cidades 101 é maior do que o esperado\n");

    // Número de rodovias
    input = "2 -1 -1";
    inputStream.str(input);
    ASSERT_DEATH(Input::readParameters(inputStream),
                 "Número de rodovias -1 é negativo\n");

    input = "2 1001 1";
    inputStream.str(input);
    ASSERT_DEATH(Input::readParameters(inputStream),
                 "Número de rodovias 1001 é maior do que o esperado\n");

    input = "2 3 1";
    inputStream.str(input);
    ASSERT_DEATH(Input::readParameters(inputStream),
                 "Número de rodovias 3 é maior do que o esperado\n");

    // Número de consultas
    input = "2 1 0";
    inputStream.str(input);
    ASSERT_DEATH(Input::readParameters(inputStream),
                 "Número de consultas 0 não é positivo\n");

    input = "2 1 1001";
    inputStream.str(input);
    ASSERT_DEATH(Input::readParameters(inputStream),
                 "Número de consultas 1001 é maior do que o esperado\n");
}

TEST(input, readRoads) {
    // Vazio no início porque não consideramos o índice 0
    // Vazio no final porque o vértice 4 existe mas grau de saída é 0
    const graph EDGES = {{}, {{2000, 2}}, {{1500, 3}}, {{700, 4}}, {}};
    Graph expected;
    expected.setGraph(EDGES);
    roads.resize(EDGES.size());

    // Atualiza parâmetro para ler a quantidade adequada de consultas
    numOfRoads = 3;

    stringstream input("1 2 2000\n2 3 1500\n3 4 700");
    Input::readRoads(input);

    EXPECT_EQ(expected.getGraph(), roads.getGraph());
}

TEST(input, readRoadsExceptions) {

    string input;
    stringstream inputStream;

    // Atualiza parâmetro para ler a quantidade adequada de rodovias
    numOfRoads = 1;
    numOfCities = 2;

    // Arestas
    input = "0 1 1";
    inputStream.str(input);
    ASSERT_DEATH(Input::readRoads(inputStream),
                 "Vértice de partida 0 não positivo");
    input = "3 1 1";
    inputStream.str(input);
    ASSERT_DEATH(Input::readRoads(inputStream),
                 "Vértice de partida 3 maior que o número de cidades 2");
    input = "1 0 1";
    inputStream.str(input);
    ASSERT_DEATH(Input::readRoads(inputStream),
                 "Vértice de chegada 0 não positiva");
    input = "1 3 1";
    inputStream.str(input);
    ASSERT_DEATH(Input::readRoads(inputStream),
                 "Vértice de chegada 3 maior que o número de cidades 2");
    input = "1 1 1";
    inputStream.str(input);
    ASSERT_DEATH(Input::readRoads(inputStream),
                 "Vértice de partida e vértice de chegada coincidem");

    // Peso
    input = "1 2 0";
    inputStream.str(input);
    ASSERT_DEATH(Input::readRoads(inputStream), "Peso 0 não positivo");
    input = "1 2 1000001";
    inputStream.str(input);
    ASSERT_DEATH(Input::readRoads(inputStream),
                 "Peso 1000001 maior que o máximo 1000000");
}

TEST(input, readQueries) {
    const list<pair<int, int>> EXPECTED = {{1, 4}, {2, 1}, {3, 1}, {4, 3}};

    // Atualiza parâmetro para ler a quantidade adequada de consultas
    numOfQueries = 4;

    stringstream input("1 4\n2 1\n3 1\n4 3");
    Input::readQueries(input);

    EXPECT_EQ(EXPECTED, queries);
}

TEST(input, readQueriesExceptions) {
    stringstream input("1 1");

    EXPECT_DEATH(Input::readQueries(input),
                 "Vértice de partida e vértice de chegada coincidem");
}

TEST(graph, widestPath) {
    // Vazio no início porque não consideramos o índice 0
    // Vazio no final porque o vértice 4 existe, mas grau de saída é 0
    const graph EDGES = {{}, {{2000, 2}}, {{1500, 3}}, {{700, 4}}, {}};
    Graph g(EDGES.size());
    g.setGraph(EDGES);

    const int EXPECTED = 700;
    const int ACTUAL = g.widestPath(1, 4);

    EXPECT_EQ(ACTUAL, EXPECTED);
}

TEST(graph, widestPath2) {
    // Vazio no início porque não consideramos o índice 0
    // Vazio no final porque o último vértice existe, mas grau de saída é 0
    const graph EDGES = {
        {},       {{3, 2}, {8, 3}}, {{7, 4}, {6, 5}}, {{5, 5}, {4, 6}},
        {{1, 7}}, {{3, 7}},         {{4, 7}},         {{}}};
    Graph g(EDGES.size());
    g.setGraph(EDGES);

    const int EXPECTED = 4;
    const int ACTUAL = g.widestPath(1, 7);

    EXPECT_EQ(ACTUAL, EXPECTED);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
