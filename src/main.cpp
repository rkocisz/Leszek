#include "App.h"
#include "fileReader.h"
#include <iostream>

int main(int argc, char* argv[])
{
    App app;
    app.run();

    return 0;
}


//
//int main()
//{
//    Matrix x;
//    Matrix y;
//
//    readCSV("../trainingData/mnist_train.csv", x, y);
//
//    NeuralNetwork leszek{ {784,128,10} };
//
//    leszek.loadFromFile("../weights.txt");
//
//    leszek.train(x, y, 6, 4, 0.05);
//
//    leszek.saveToFile("../weights.txt");
//
//    return 0;
//}