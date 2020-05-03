#include "Bellmanalg.h"

double BellmanAlg(std::shared_ptr<List> workingGraph, int startingNode)
{
	std::string* pathStorage = new std::string[workingGraph->GetNodes()];
	auto startTime = std::chrono::high_resolution_clock::now();
	int* distanceStorage = new int[workingGraph->GetNodes()];

	for (int iterNodes = 0; iterNodes < workingGraph->GetNodes(); iterNodes++)
		distanceStorage[iterNodes] = infinity;

	distanceStorage[startingNode] = 0;

	for (int iterNodes = 1; iterNodes < workingGraph->GetNodes(); iterNodes++)
		for (int iterEdges = 0; iterEdges < workingGraph->GetEdges(); iterEdges++)
		{
			int temNodeStart = workingGraph->GetEdge()[iterEdges].nodeStart;
			int temNodeEnd = workingGraph->GetEdge()[iterEdges].nodeEnd;
			int temValue = workingGraph->GetEdge()[iterEdges].value;

			if (distanceStorage[temNodeStart] + temValue < distanceStorage[temNodeEnd])
				distanceStorage[temNodeEnd] = distanceStorage[temNodeStart] + temValue;

			pathStorage[temNodeEnd].clear();
			pathStorage[temNodeEnd].append(pathStorage[temNodeStart] + std::to_string(temNodeStart) + "->");
		}

	for (int iterNodes = 1; iterNodes < workingGraph->GetNodes(); iterNodes++)
		for (int iterEdges = 0; iterEdges < workingGraph->GetEdges(); iterEdges++)
		{
			int temNodeStart = workingGraph->GetEdge()[iterEdges].nodeStart;
			int temNodeEnd = workingGraph->GetEdge()[iterEdges].nodeEnd;
			int temValue = workingGraph->GetEdge()[iterEdges].value;

			if (distanceStorage[temNodeStart] + temValue < distanceStorage[temNodeEnd])
			{
				if (distanceStorage[temNodeStart] > infinity / 2)
					distanceStorage[temNodeStart] = infinity;

				else
					distanceStorage[temNodeEnd] = negInfinity;
			}

			else if (distanceStorage[temNodeStart] > infinity / 2)
				distanceStorage[temNodeStart] = infinity;
		}

	auto endTime = std::chrono::high_resolution_clock::now();

	Results(std::move(pathStorage), std::move(distanceStorage), workingGraph->GetNodes(), startingNode);
	delete[] pathStorage;
	delete[] distanceStorage;

	return std::chrono::duration<double, std::milli>(endTime - startTime).count();
}

double BellmanAlg(std::shared_ptr<Matrix> workingGraph, int startingNode)
{
	std::string* pathStorage = new std::string[workingGraph->GetNodes()];
	auto startTime = std::chrono::high_resolution_clock::now();
	int* distanceStorage = new int[workingGraph->GetNodes()];

	for (int iterNodes = 0; iterNodes < workingGraph->GetNodes(); iterNodes++)
		distanceStorage[iterNodes] = infinity;

	distanceStorage[startingNode] = 0;

	for (int iterNodes = 1; iterNodes < workingGraph->GetNodes(); iterNodes++)
		for (int iterNodeCell = 0; iterNodeCell < workingGraph->GetNodes(); iterNodeCell++)
			for (int iterNodeCollumn = 0; iterNodeCollumn < workingGraph->GetNodes(); iterNodeCollumn++)
			{
				int temNodeStart = iterNodeCell;
				int temNodeEnd = iterNodeCollumn;
				int temValue = workingGraph->GetValue(iterNodeCell, iterNodeCollumn);

				if (distanceStorage[temNodeStart] + temValue < distanceStorage[temNodeEnd])
				{
					distanceStorage[temNodeEnd] = distanceStorage[startingNode] + temValue;
					pathStorage[temNodeEnd].clear();
					pathStorage[temNodeEnd].append(pathStorage[temNodeStart] + std::to_string(temNodeStart) + "->");
				}
			}

	for (int iterNodes = 1; iterNodes < workingGraph->GetNodes(); iterNodes++)
		for (int iterNodeCell = 0; iterNodeCell < workingGraph->GetNodes(); iterNodeCell++)
			for (int iterNodeCollumn = 0; iterNodeCollumn < workingGraph->GetNodes(); iterNodeCollumn++)
			{
				int temNodeStart = iterNodeCell;
				int temNodeEnd = iterNodeCollumn;
				int temValue = workingGraph->GetValue(iterNodeCell, iterNodeCollumn);

				if (distanceStorage[temNodeStart] + temValue < distanceStorage[temNodeEnd])
				{
					if (distanceStorage[temNodeStart] > infinity / 2)
						distanceStorage[temNodeStart] = infinity;

					else if (temValue == infinity)
						continue;

					else
						distanceStorage[temNodeEnd] = negInfinity;
				}

				else if (distanceStorage[temNodeStart] > infinity / 2)
					distanceStorage[temNodeStart] = infinity;
			}

	auto endTime = std::chrono::high_resolution_clock::now();

	Results(std::move(pathStorage), std::move(distanceStorage), workingGraph->GetNodes(), startingNode);

	delete[] pathStorage;
	delete[] distanceStorage;

	return std::chrono::duration<double, std::milli>(endTime - startTime).count();
}

void Results(std::string pathString[], int distanceStorage[], int nodesAmount, int startingNode)
{
	std::ofstream resoultsFile("Results.txt");
	std::cout << "\n           Results            \n\n";
	std::cout << "Starting node was : " << startingNode << std::endl;
	resoultsFile << "\n           Results            \n\n";
	resoultsFile << "Starting node was : " << startingNode << std::endl;

	for (int itrNodes = 0; itrNodes < nodesAmount; itrNodes++)
	{
		if (distanceStorage[itrNodes] == infinity)
		{
			std::cout << itrNodes << "-> inf" << std::endl;
			resoultsFile << itrNodes << "-> inf" << std::endl;

			continue;
		}

		else if (distanceStorage[itrNodes] == negInfinity)
		{
			std::cout << itrNodes << "-> -inf" << std::endl;
			resoultsFile << itrNodes << "-> -inf" << std::endl;

			continue;
		}
		else
		{
			std::cout << itrNodes << "->" << distanceStorage[itrNodes] << std::endl;
			resoultsFile << itrNodes << "->" << distanceStorage[itrNodes] << std::endl;
		}

		std::cout << "  ";
		resoultsFile << "  ";

		if ((distanceStorage[itrNodes] >= 100 && distanceStorage[itrNodes] < 1000) || (-100 > distanceStorage[itrNodes] && distanceStorage[itrNodes] <= -10))
		{
			std::cout << " The shortest path: " << pathString[itrNodes] << itrNodes;
			resoultsFile << " The shortest path: " << pathString[itrNodes] << itrNodes;
		}
		else if (0 <= distanceStorage[itrNodes] && distanceStorage[itrNodes] < 10)
		{
			std::cout << "   The shortest path: " << pathString[itrNodes] << itrNodes;
			resoultsFile << "   The shortest path: " << pathString[itrNodes] << itrNodes;
		}
		else if ((distanceStorage[itrNodes] >= 10 && distanceStorage[itrNodes] < 100) || (-10 < distanceStorage[itrNodes] && distanceStorage[itrNodes] < 0))
		{
			std::cout << "  The shortest path: " << pathString[itrNodes] << itrNodes;
			resoultsFile << "  The shortest path: " << pathString[itrNodes] << itrNodes;
		}
		else
		{
			std::cout << "The shortest path: " << pathString[itrNodes] << itrNodes;
			resoultsFile << "The shortest path: " << pathString[itrNodes] << itrNodes;
		}
		std::cout << std::endl;
	}
	resoultsFile << std::endl;
}
