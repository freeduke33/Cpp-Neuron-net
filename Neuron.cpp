#include <iostream>
#include <vector>
#include <math.h>

#include "Neuron_Header.h"
#include "Link_Header.h"

using namespace std;

double Neuron::Active_func_vard(double input) {
    double ret = 1.0 / (1.0 + exp(-input));
	std::cout <<"active: ret=" <<ret <<" inp=" <<input << std::endl;
}

// - - - - - -

Neuron::Neuron(int Conn_neurons_up, int Conn_neurons_down) {
    Up_links.resize(Conn_neurons_up); // amount of neurons in previos lay connected to this one -> Conn_neurons
    Down_links.resize(Conn_neurons_down);
}

Neuron::Neuron() {
    Up_links.resize(0); // amount of neurons in previos lay connected to this one -> Conn_neurons
    Down_links.resize(0);
}

// - - - - - -

double Neuron::Get_signal() {
    return signal;
}

void Neuron::Set_signal(double new_signal) {
    signal = new_signal;
}

double Neuron::Set_input_signal(double input) {
    return input_signal = input;
}

double Neuron::Activ_func() {
    return output_signal = Active_func_vard(signal);
}

double Neuron::Get_output_signal() {
    return output_signal;
}

void Neuron::Summ_signals_from_UpLinks() {
	signal = 0;
    for (int i = 0; i < Up_links.size(); i++) {
        Up_links[i]->Activate_link_Ner2Ner();
        signal = signal + input_signal;
    }
}

void Neuron::add_up_link(Link& up_link) {
    Up_links.push_back(&up_link);
}

// - - - - - -

double Neuron::Get_mistake() {
    return mistake;
}

void Neuron::Set_mistake(double new_mistake) {
    mistake = new_mistake;
}

double Neuron::Mistake_func() {
    output_mistake = Active_func_vard(mistake)*(1 - Active_func_vard(mistake));
    return output_mistake;
}

double Neuron::Set_input_mistake(double input) {
    return input_mistake = input;
}

double Neuron::Get_output_mistake() {
    return output_mistake;
}

void Neuron::Summ_signals_from_DownLinks() {
    mistake = 0;
    for (int i = 0; i < Down_links.size(); i++) {
        Down_links[i]->Disactivate_link_Ner2Ner();
        mistake = mistake + input_mistake;
    }
}

void Neuron::add_down_link(Link& down_link) {
    Down_links.push_back(&down_link);
}

// - - - - - -

