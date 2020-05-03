#include "Matrix.h"
#include "List.h"

Matrix::Matrix(int nodesAmount, double density) :Graph(nodesAmount, static_cast<int>(density* nodesAmount* (nodesAmount - 1)), density), matrix(std::make_unique<std::unique_ptr<int[]>[]>(nodesAmount))
{
	for (int iterNodesCell = 0; iterNodesCell < this->mAmOfNodes; iterNodesCell++)
	{
		matrix[iterNodesCell] = std::make_unique<int[]>(nodesAmount);

		for (int iterNodesCollumn = 0; iterNodesCollumn < this->mAmOfNodes; iterNodesCollumn++)
		{
			if (iterNodesCell == iterNodesCollumn)
				matrix[iterNodesCell][iterNodesCollumn] = 0;

			else
				matrix[iterNodesCell][iterNodesCollumn] = infinity;
		}
	}
}


void Matrix::FillGraph(const bool allowLoops) const
{
	if (this->mDensity == 1)
	{
		for (int iterNodesCell = 0; iterNodesCell < this->mAmOfNodes; iterNodesCell++)
			for (int iterNodesCollumn = 0; iterNodesCollumn < this->mAmOfNodes; iterNodesCollumn++)
				if (iterNodesCell != iterNodesCollumn)
				{
					int randValue = rand() % 50 - regulatingValue;

					while (randValue == 0)
						randValue = rand() % 50 - regulatingValue;
					
					matrix[iterNodesCell][iterNodesCollumn] = randValue;
				}
	}
	else
	{
		int iterEdges = this->mAmOfEdges;
		while (iterEdges != 0)
		{
			int cellNode = rand() % this->mAmOfNodes;
			int collumnNode = rand() % this->mAmOfNodes;

			if (matrix[cellNode][collumnNode] == 0 || matrix[cellNode][collumnNode] == infinity)
			{
				int randValue = rand() % 50 - regulatingValue;

				while (randValue == 0)
					randValue = rand() % 50 - regulatingValue;

				if (cellNode != collumnNode)
				{
					matrix[cellNode][collumnNode] = randValue;
					--iterEdges;
				}

				else if (allowLoops)
				{
					matrix[cellNode][collumnNode] = randValue;
					--iterEdges;
				}
			}
		}

	}
}

void Matrix::PrintGraph() const
{
	std::cout << "\n Matrix represetation of Graph \n\n";

	for (int nodeIter = 0; nodeIter < this->mAmOfNodes; nodeIter++)
		std::cout << "  " << nodeIter;
	
	std::cout << std::endl << std::endl;

	for (int nodeCell = 0; nodeCell < this->mAmOfNodes; nodeCell++)
	{
		std::cout << nodeCell << " *";

		for (int nodeCollumn = 0; nodeCollumn < this->mAmOfNodes; nodeCollumn++)
		{
			int temporaryMatrixValue = matrix[nodeCell][nodeCollumn];

			if (temporaryMatrixValue == infinity)
				std::cout << "#";
			
			else
				std::cout << temporaryMatrixValue;
			
			std::cout << "  ";
		}
		std::cout << "*" << std::endl;
	}
	std::cout << std::endl;
}

const int Matrix::RFile(const std::string fileName)
{
	std::ifstream inFile(fileName);

	if (!inFile.is_open())
	{
		std::cerr << " Input file is not open" << std::endl;

		return -1;
	}

	int startingNode, nodeStart, nodeEnd, value;
	inFile >> this->mAmOfEdges >> this->mAmOfNodes >> startingNode;
	matrix = std::make_unique<std::unique_ptr<int[]>[]>(this->mAmOfNodes);

	for (int iterNodesCell = 0; iterNodesCell < this->mAmOfNodes; iterNodesCell++)
	{
		matrix[iterNodesCell] = std::make_unique<int[]>(this->mAmOfNodes);

		for (int iterNodesCollumn = 0; iterNodesCollumn < this->mAmOfNodes; iterNodesCollumn++)
		{
			if (iterNodesCell == iterNodesCollumn)
				matrix[iterNodesCell][iterNodesCollumn] = 0;
			
			else
				matrix[iterNodesCell][iterNodesCollumn] = infinity;
			
		}
	}

	for (int iterEdge = 0; iterEdge < this->mAmOfEdges; iterEdge++)
	{
		inFile >> nodeStart >> nodeEnd >> value;
		matrix[nodeStart][nodeEnd] = value;
	}

	inFile.close();

	return startingNode;
}

void Matrix::CreateInput(const int startNode) const
{
	std::ofstream outFile("OutInput.txt");

	if (!outFile.is_open())
	{
		std::cerr << " Output File not Created";

		return;
	}

	outFile << this->mAmOfEdges << " " << this->mAmOfNodes << " " << startNode << std::endl;

	for (int iterNodesCell = 0; iterNodesCell < this->mAmOfNodes; iterNodesCell++)
		for (int iterNodesCollumn = 0; iterNodesCollumn < this->mAmOfNodes; iterNodesCollumn++)
			if (matrix[iterNodesCell][iterNodesCollumn] != infinity && matrix[iterNodesCell][iterNodesCollumn] != 0)
				outFile << iterNodesCell << " " << iterNodesCollumn << " " << matrix[iterNodesCell][iterNodesCollumn] << std::endl;
	
	outFile.close();
}
