#pragma once

#include <fstream>
#include <cstdlib>
#include <iostream>
#include <ctime>
#include <string>

#include "Edge.h"

class Graph {
protected:
	int mAmOfNodes;
	int mAmOfEdges;
	double mDensity;

public:
	const int GetNodes()
	{
		return this->mAmOfNodes;
	}

	const int GetEdges()
	{
		return this->mAmOfEdges;
	}

	virtual void FillGraph(const bool allowLoops) const = 0;
	virtual void PrintGraph() const = 0;
	virtual const int RFile(const std::string fileName) = 0;
	virtual void CreateInput(const int startNode) const = 0;

	virtual ~Graph() {};
	Graph(int inAmOfNodes, int inAmOfEdges, double inDensity) : mAmOfNodes(inAmOfNodes), mAmOfEdges(inAmOfEdges), mDensity(inDensity) {};
	Graph() {};
};

