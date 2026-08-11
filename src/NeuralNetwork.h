#pragma once

#include "Layer.h"
#include "Matrix.h"
#include <cmath>
#include <fstream>

inline Matrix softMax(const Matrix& preActivationOutput)
{
	Matrix result = preActivationOutput;
	double sum = 0;

	for (int i = 0; i < result.cols; i++)
	{
		for (int j = 0; j < result.rows; j++)
		{
			result.at(j, i) = std::exp(result.at(j, i));
			sum += result.at(j, i);
		}
		for (int j = 0; j < result.rows; j++)
		{
			result.at(j, i) /= sum;
		}
		sum = 0;
	}
	return result;
}

inline double crossEntropyLoss(const Matrix& guess, const Matrix& target)
{
	double result = 0;

	for (int i = 0; i < guess.cols; i++)
	{
		for (int j = 0; j < guess.rows; j++)
		{
			if (target.at(j, i) == 1)
			{
				result -= std::log(guess.at(j, i));
				break;
			}
		}
	}
	result /= guess.cols;

	return result;
}

class NeuralNetwork
{
private:
	std::vector<Layer> layers;
	
public:

	NeuralNetwork(std::vector<int> layerSizes)
	{
		for (int i = 0; i < layerSizes.size() - 1; i++)
		{
			layers.push_back(Layer(layerSizes[i + 1], layerSizes[i]));
		}
	}

	Matrix forward(const Matrix& input)
	{
		Matrix nextLayerInput = input;
		for (int i = 0; i < layers.size(); i++)
		{
			if (i == layers.size() - 1)
				nextLayerInput = layers[i].forward(nextLayerInput, true);
			else
				nextLayerInput = layers[i].forward(nextLayerInput, false);
		}

		return softMax(nextLayerInput);
	}

	void backward(const Matrix& guess, const Matrix& target, double learningRate)
	{
		Matrix prevLayerInput = guess.subtract(target);

		for (int i = layers.size() - 1; i >= 0; i--)
		{
			if(i == layers.size() - 1)
				prevLayerInput = layers[i].backward(prevLayerInput, learningRate, true);
			else
				prevLayerInput = layers[i].backward(prevLayerInput, learningRate, false);
		}
	}

	void train(const Matrix& X, const Matrix& Y, int epochs, int batchSize, double learningRate)
	{
		for (int i = 0; i < epochs; i++)
		{
			int batchesCount = X.cols / batchSize;

			for (int batch = 0; batch < batchesCount; batch++)
			{
				int startIndex = batch * batchSize;

				Matrix input = X.getColumns(startIndex, batchSize);
				Matrix target = Y.getColumns(startIndex, batchSize);

				Matrix output = forward(input);
				backward(output, target, learningRate);
			
				if (batch == batchesCount - 1)
				{
					std::cout << "epoch " << i << ": " << crossEntropyLoss(output, target) << "\n";
				}
			}
		}
	}

	void saveToFile(std::string fileName)
	{
		std::ofstream file(fileName);

		file << layers.size() << "\n";

		for (int i = 0; i < layers.size(); i++)
		{
			layers[i].saveToStream(file);
		}

		file.close();
	}

	void loadFromFile(std::string fileName)
	{
		std::ifstream file(fileName);
		
		int layers_;
		file >> layers_;
		if (layers.size() != layers_)
		{
			std::cout << "zla liczba layerow";
			return;
		}
		
		for (int i = 0; i < layers.size(); i++)
		{
			layers[i].loadFromStream(file);
		}
	
		file.close();
	}
};
