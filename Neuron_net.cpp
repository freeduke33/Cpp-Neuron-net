#include <iostream>
#include <vector>
#include <math.h>
#include <ctime>

#include "Matrix_Header.h"
#include "MatrixUtility_Header.h"
#include "Neuron_Header.h"
#include "Link_Header.h"
#include "TestOriginal.h"

#include <fstream>
#include <sstream> // getline need it :{

using namespace std;

void TEST_1_neuron() {
    Neuron ner;
    double signal = 0.3;

    ner.Set_input_signal(signal);
    ner.Activ_func();
    cout << ner.Get_output_signal() << endl;
}

void TEST_1__2_neuron() {
    // test activate function from neuron

    Neuron ner;
    double signal = 0;

    ner.Set_input_signal(signal);
    ner.Activ_func();

    cout << ner.Activ_func() << endl;
    cout << ner.Get_output_signal() << endl;
    cout << "- - - - -" << endl;
    cout << exp(-signal) << endl;
    cout << 1.0 + exp(-signal) << endl;
    cout << 1.0 / (1.0 + exp(-signal)) << endl;
}

void TEST_2_neuron() {
    Neuron ner;
    double signal = 0.3;

    ner.Set_input_mistake(signal);
    ner.Mistake_func();
    cout << ner.Get_output_mistake() << endl;
}

void TEST_3_neuron() {
    double signal = 0.9;

    Neuron ner1, ner2;
    Link link(ner1, ner2);
    link.Set_weight(0.3);

    ner1.Set_input_signal(signal);
    ner1.Activ_func();
    cout << ner1.Get_output_signal() << endl;
    ner2.Summ_signals_from_UpLinks();
    cout << ner2.Get_input_signal() << endl;
    ner2.Activ_func();
    cout << ner2.Get_output_signal() << endl;
}

void TEST_4_neuron() {
    double signal = 0.9;
    double predicted_result = 0.3;
    double Edict_norm = 0.0001;
    double result;

    Neuron ner1, ner2;
    Link link(ner1, ner2);
    link.Set_weight(0.3);

    ner1.Set_input_signal(signal);
    ner1.Activ_func();
    ner2.Summ_signals_from_UpLinks();
    ner2.Activ_func();

    cout << link.Get_weight() << endl;

    result = ner2.Get_output_signal();
    ner2.Set_input_mistake(predicted_result - result);
    ner2.Mistake_func();
    ner1.Summ_signals_from_DownLinks();
    link.Set_weight(link.Get_weight() + Edict_norm * ner1.Get_output_signal() * result);
    ner1.Mistake_func();

    cout << link.Get_weight() << endl;

}

void TEST_4__2_neuron() {
    double signal = 0.0616501;

    Neuron ner;

    ner.Set_input_mistake(signal);
    cout << ner.Get_input_mistake() << endl;
    ner.Mistake_func();
    cout << ner.Get_output_mistake() << endl;
    cout << "- - - - -" << endl;
    cout << exp(-signal) << endl;
    cout << 1.0 + exp(-signal) << endl;
    cout << 1.0 / (1.0 + exp(-signal)) << endl;
    cout << 1 - (1.0 / (1.0 + exp(-signal))) << endl;
    cout << (1.0 / (1.0 + exp(-signal))) * (1 - (1.0 / (1.0 + exp(-signal)))) << endl;

}

std::string okOrFailed(bool ok) {
	if (ok) {
		return "Ok";
	} else {
		return "FAILED";
	}
}

extern "C" int main()
{
    srand(time(0)); //1 + rand() % 10

    // создание матрицы нейроннов

    string file_name = "text.txt";

    TEST_4_neuron();

	TestOriginal t;
	std::cout <<"TestOriginal: "  <<okOrFailed( t.isOk() ) <<std::endl;

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
