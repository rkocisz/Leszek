#pragma once

#include "Matrix.h"

#include <fstream>
#include <string>
#include <sstream>


void readCSV(std::string file, Matrix& X, Matrix& Y)
{
	std::ifstream file_(file);

	if (!file_.is_open())
	{
		std::cout << "plik sie nie otworzyl!!!";
		return;
	}

	int dataRows = 0;
	int dataCols = 0;
	std::string line;

	while (std::getline(file_, line))
	{
		if (dataCols == 0)
		{
			for (char x : line)
			{
				if (x == ',')
				{
					dataCols++;
				}
			}
			dataCols++;
		}	
		dataRows++;
	}

	X = Matrix(dataCols - 1, dataRows);
	Y = Matrix(10, dataRows);

	file_.clear();
	file_.seekg(0);

	int i = 0;
	int j = 0;

	while (std::getline(file_, line))
	{
		std::stringstream ss(line);
		std::string cell;

		j = 0;
		while (std::getline(ss, cell, ','))
		{
			if(i == 0) break;

			if (j == 0)
			{
				int label = std::stoi(cell);
				Y.at(label, i) = 1; 
			}
			else
			{
				X.at(j - 1, i) = std::stod(cell) / 255;
			}
			j++;
		}
		i++;
	}
}