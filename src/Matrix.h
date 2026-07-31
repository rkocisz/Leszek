#pragma once
#include <vector>
#include <random>
#include <stdexcept>
#include <iostream>

class Matrix
{
public:
    int rows, cols;
    std::vector<double> data;

    Matrix() : rows(0), cols(0)
    {
    }

    Matrix(int rows_, int cols_) : rows(rows_), cols(cols_)
    {
        data.resize(rows * cols, 0.0);
    }

    double& at(int i, int j)
    {
        return data[i * cols + j];
    }

    double at(int i, int j) const
    {
        return data[i * cols + j];
    }

    void randomizeHe(int fanIn)
    {
        std::random_device rd;
        std::mt19937 gen(rd());
        double stddev = std::sqrt(2.0 / fanIn);
        std::normal_distribution<double> dist(0.0, stddev);
        for (auto& v : data)
        {
            v = dist(gen);
        }
    }

    void zero()
    {
        std::fill(data.begin(), data.end(), 0.0);
    }

    Matrix multiply(const Matrix& other) const
    {
        if (cols != other.rows)
        {
            throw std::invalid_argument("Matrix::multiply: niezgodne wymiary");
        }
        Matrix result(rows, other.cols);
        for (int i = 0; i < rows; i++)
        {
            for (int k = 0; k < cols; k++)
            {
                double a = at(i, k);
                if (a == 0.0) continue; // mały optymalizacyjny skrót
                for (int j = 0; j < other.cols; j++)
                {
                    result.at(i, j) += a * other.at(k, j);
                }
            }
        }
        return result;
    }

    // Transpozycja
    Matrix transpose() const
    {
        Matrix result(cols, rows);
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < cols; j++)
            {
                result.at(j, i) = at(i, j);
            }
        }
        return result;
    }

    // Dodawanie element-po-elemencie
    Matrix add(const Matrix& other) const
    {
        if (rows != other.rows || cols != other.cols)
        {
            throw std::invalid_argument("Matrix::add: niezgodne wymiary");
        }
        Matrix result(rows, cols);
        for (size_t i = 0; i < data.size(); i++)
        {
            result.data[i] = data[i] + other.data[i];
        }
        return result;
    }

    // Odejmowanie element-po-elemencie
    Matrix subtract(const Matrix& other) const
    {
        if (rows != other.rows || cols != other.cols)
        {
            throw std::invalid_argument("Matrix::subtract: niezgodne wymiary");
        }
        Matrix result(rows, cols);
        for (size_t i = 0; i < data.size(); i++)
        {
            result.data[i] = data[i] - other.data[i];
        }
        return result;
    }

    // Mnożenie element-po-elemencie (Hadamard product) - to jest to "⊙" ze wzorów
    Matrix hadamard(const Matrix& other) const
    {
        if (rows != other.rows || cols != other.cols)
        {
            throw std::invalid_argument("Matrix::hadamard: niezgodne wymiary");
        }
        Matrix result(rows, cols);
        for (size_t i = 0; i < data.size(); i++)
        {
            result.data[i] = data[i] * other.data[i];
        }
        return result;
    }

    // Mnożenie przez skalar (np. przez learning_rate)
    Matrix multiplyScalar(double scalar) const
    {
        Matrix result(rows, cols);
        for (size_t i = 0; i < data.size(); i++)
        {
            result.data[i] = data[i] * scalar;
        }
        return result;
    }

    // Dodanie tego samego wektora bias do każdej "kolumny" (przypadku w batchu)
    // this: (rows x batchSize), bias: (rows x 1)
    Matrix addBiasBroadcast(const Matrix& bias) const
    {
        if (bias.rows != rows || bias.cols != 1)
        {
            throw std::invalid_argument("Matrix::addBiasBroadcast: bias musi być (rows x 1)");
        }
        Matrix result(rows, cols);
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < cols; j++)
            {
                result.at(i, j) = at(i, j) + bias.at(i, 0);
            }
        }
        return result;
    }

    Matrix doReLU()
    {
        Matrix result(rows, cols);
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < cols; j++)
            {
                result.at(i, j) = ReLU(at(i, j));
            }
        }

        return result;
    }

    void print() const
    {
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < cols; j++)
            {
                std::cout << at(i, j) << " ";
            }
            std::cout << "\n";
        }
    }

    
private:

    double ReLU(double x)
    {
        if (x < 0) return 0;
        return x;
    }
};