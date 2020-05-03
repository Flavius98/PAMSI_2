#pragma once

#include <memory>

#include "Graph.h"

static int infinity = 10000000;
static int negInfinity = -10000000;

class Matrix : public Graph {
	std::unique_ptr<std::unique_ptr<int[]>[]> matrix;

public:
	void FillGraph(const bool allowLoops) const override;
	void PrintGraph() const override;
	const int RFile(const std::string fName) override;
	void CreateInput(const int startNode) const override;

	const int GetValue(int one, int two) const
	{
		return this->matrix[one][two];
	}

	Matrix(int nodesAmount, double density);
	Matrix() : Graph() {};
};

