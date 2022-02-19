#include "Neuron_Header.h"
#include "Link_Header.h"

#include <iostream>
#include <cmath>

using namespace std;

void TEST_1_neuron() {
    Neuron ner, ner0;
    double signal = 0.3;

    ner0.Set_input_signal_testonly(signal);
    ner.Activ_func();
    cout << ner.Get_output_signal() << endl;
}

void TEST_1__2_neuron() {
    // test activate function from neuron

    Neuron ner;
    double signal = 0;

    ner.Set_input_signal_testonly(signal);
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
    Link link(ner1, ner2, 0.85);
    link.Set_weight(0.3);

    ner1.Set_input_signal_testonly(signal);
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
    Link link(ner1, ner2, 0.85);
    link.Set_weight(0.3);

    ner1.Set_input_signal_testonly(signal);
    ner1.Activ_func();
    ner2.Summ_signals_from_UpLinks();
    ner2.Activ_func();

    cout << link.Get_weight() << endl;

    result = ner2.Get_output_signal();
    ner2.Set_input_mistake(predicted_result - result);
    ner2.Mistake_func();
    ner1.Summ_mistake_from_DownLinks();
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
