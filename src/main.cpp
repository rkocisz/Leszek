#include "App.h"
#include "fileReader.h"
#include <iostream>

int main(int argc, char* argv[])
{
    App app;
    app.run();

    return 0;
}



//int main()
//{
//    Matrix x;
//    Matrix y;
//
//    readCSV("../trainingdata/mnist_train.csv", x, y);
//
//    NeuralNetwork leszek{ {784,128,10} };
//
//    leszek.loadFromFile("../weights.txt");
//
//    leszek.train(x, y, 5, 2, 0.02);
//
//    leszek.saveToFile("../weights.txt");
//
//    return 0;
//}