﻿#include <iostream>
#include <vector>
#include <math.h>
#include <ctime>

#include "Matrix_Header.h"
#include "MatrixUtility_Header.h"
#include "Neuron_Header.h"

#include <fstream>
#include <sstream> // getline need it :{

using namespace std;

void TEST_1_neuron() {
    Neuron ner;
    double signal = 12.3;

    ner.Set_input_signal(signal);
    ner.Activ_func();
    cout << ner.Get_output_signal() << endl;
}

void TEST_2_neuron() {
    Neuron ner;
    double signal = 12.3;

    ner.Set_unput_mistake(signal);
    ner.Mistake_func();
    cout << ner.Get_output_mistake() << endl;
}

void TEST_2_neuron() {

}

int main()
{
    srand(time(0)); //1 + rand() % 10

    // создание матрицы нейроннов

    string file_name = "text.txt";

    TEST_1_neuron();
    TEST_2_neuron();

    cout << "done";
    return 0;
}


/*
    try
    {
        MatrixUtility::save_matrix(file_name, MatrixUtility::load_matrix(file_name));
    }
    catch (runtime_error& err) {
        cout << err.what() << endl;
    }

    /// lost try

    Matrix net;
    net.matrix_size_correct(1, 1);
    net.matrix_input_num(0, 0, 0.0);
    net.matrix_transport(cout);

    vector <Neuron> neurons;
    vector <Link> links;

    neurons.resize(net.matrix_Xsize());
    if (neurons.size() >= 2) {
        links.resize(neurons.size() - 1);
    }
    else {
        links.resize(1);
    }

    for (int i = 0; i < neurons.size(); i++) {
        if (neurons.size() >= 2) {
            neurons[i].add_down_link(links[i]);
            neurons[i+1].add_up_link(links[i]);
        }
        else {
            neurons[i].add_down_link(links[i]);
            neurons[i].add_down_link(links[i]);
        }

    }
*/