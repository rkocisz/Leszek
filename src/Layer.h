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

	Matrix forward(const Matrix& input_, bool isOutputLayer)
	{
		input = input_;

		Matrix output = weights.multiply(input_);
		output = output.addBiasBroadcast(bias);
		preActivation = output;

		if(!isOutputLayer)
			output = output.doReLU(); //jak output layer to skipujemy ReLU
		
		postActivation = output;

		return output;
	}

	Matrix backward(const Matrix& influenceOnNextLayer, double learningRate, bool isOutputLayer)
	{
		Matrix delta;
		if (isOutputLayer)
			delta = influenceOnNextLayer; // skipujemy pochodną ReLU
		else
			delta = influenceOnNextLayer.hadamard(preActivation.doReLU_Derivative());

		Matrix weightGradients = delta.multiply(input.transpose());
		Matrix biasGradients = delta.sumColumns();

		weightGradients = weightGradients.multiplyScalar(1.0 / influenceOnNextLayer.cols);
		biasGradients = biasGradients.multiplyScalar(1.0 / influenceOnNextLayer.cols);

		Matrix prevLayerInfluence = weights.transpose().multiply(delta);

		weights = weights.subtract(weightGradients.multiplyScalar(learningRate));
		bias = bias.subtract(biasGradients.multiplyScalar(learningRate));

		return prevLayerInfluence;
	}
};