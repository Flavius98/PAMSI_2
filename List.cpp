#include "List.h"


void List::FillGraph(const bool allowLoops) const
{
	if (this->mDensity == 1)
	{
		int flag = 0;

		for (int iterNodeStart = 0; iterNodeStart < this->mAmOfNodes; iterNodeStart++)
			for (int iterNodeEnd = 0; iterNodeEnd < this->mAmOfNodes; iterNodeEnd++)
				if (iterNodeStart != iterNodeEnd)
				{
					int valueOfConnection = rand() % 50 - regulatingValue;

					while (valueOfConnection == 0)
						valueOfConnection = rand() % 50 - regulatingValue;
					
					AddEdge(iterNodeStart, iterNodeEnd, valueOfConnection, flag);
					flag++;
				}
	}

	else
	
		for (int iterEdges = 0; iterEdges < this->mAmOfEdges; iterEdges++)
		{
			int randStartNode = rand() % this->mAmOfNodes;
			int randEndNode = rand() % this->mAmOfNodes;

			if (!this->IsExisting(randStartNode, randEndNode))
			{
				int valueOfConnection = rand() % 50 - regulatingValue;

				while (valueOfConnection == 0)
					valueOfConnection = rand() % 50 - regulatingValue;
				
				if (randStartNode != randEndNode)
					AddEdge(randStartNode, randEndNode, valueOfConnection, iterEdges);
				
				else if (allowLoops)
					AddEdge(randStartNode, randEndNode, valueOfConnection, iterEdges);
			}
		}
}

void List::PrintGraph() const
{
	std::cout << " \n \n List representation of Graph \n \n ";
	for (int iterStartNode = 0; iterStartNode < this->mAmOfNodes; iterStartNode++)
	{
		std::cout << iterStartNode;

		for (int iterEdge = 0; iterEdge < this->mAmOfEdges; iterEdge++)
			if (this->inEdge[iterEdge].nodeStart == iterStartNode)
				std::cout << "->" << inEdge[iterEdge].nodeEnd << "|" << inEdge[iterEdge].value << "]";
	
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

const int List::RFile(const std::string fileName)
{
	std::ifstream inFile(fileName);

	if (!inFile.is_open())
	{
		std::cerr << "File is not open" << std::endl;

		return -1; //error code
	}

	int startingAlgNode, startNode, endNode, value;
	inFile >> mAmOfEdges >> mAmOfNodes >> startingAlgNode;
	this->inEdge = new Edge[mAmOfEdges];

	for (int iterEdge = 0; iterEdge < this->mAmOfEdges; iterEdge++)
	{
		inFile >> startNode >> endNode >> value;
		AddEdge(startNode, endNode, value, iterEdge);
	}

	inFile.close();

	return startingAlgNode;
}

void List::CreateInput(const int startNode) const
{
	std::ofstream out_file("out_input.txt");

	if (!out_file.is_open())
	{
		std::cerr << "File not open" << std::endl;

		return;
	}
	out_file << this->mAmOfEdges << this->mAmOfNodes << startNode << std::endl;

	for (int iterEdge = 0; iterEdge < mAmOfEdges; iterEdge++)
		out_file << inEdge[iterEdge].nodeStart << " " << inEdge[iterEdge].nodeEnd << " " << inEdge[iterEdge].value << "\n";

	out_file.close();
}

void List::AddEdge(int nodeStart, int nodeEnd, int value, int whereflag) const
{
	this->inEdge[whereflag].nodeStart = nodeStart;
	this->inEdge[whereflag].nodeEnd = nodeEnd;
	this->inEdge[whereflag].value = value;
}

bool List::IsExisting(int nodeStart, int nodeEnd) const
{
	for (int iterEdges = 0; iterEdges < this->mAmOfEdges; iterEdges++)
		if (this->inEdge[iterEdges].nodeStart == nodeStart && this->inEdge[iterEdges].nodeEnd == nodeEnd)
			return true;

	return false;
}
