#pragma once
#include <chrono>
#include <string>

#include "List.h"
#include "Matrix.h"

double BellmanAlg(std::shared_ptr<List> workingGraph, int startingNode);
double BellmanAlg(std::shared_ptr<Matrix> workingGraph, int startingNode);
void Results(std::string pathString[], int distStorage[], int nodesAmount, int startingNode);