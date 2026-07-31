#pragma once
#include "Matrix.h"

class Layer
{
public:
	Matrix weights;
	Matrix bias;

private:
	Matrix input;
	Matrix preActivation;
	Matrix postActivation;

public:
	Layer(int neuronCount, int inputsPerNeuron)
	{
		weights = Matrix(neuronCount, inputsPerNeuron);
		weights.randomizeHe(inputsPerNeuron);

		bias = Matrix(neuronCount, 1);
		bias.zero();
	}

	Matrix forward(const Matrix& input_)
	{
		input = input_;

		Matrix output = weights.multiply(input_);
		output = output.addBiasBroadcast(bias);
		preActivation = output;

		output = output.doReLU();
		postActivation = output;

		return output;
	}
};