#include <iostream>
#include <vector>
#include <math.h>

#include "Link_Header.h"
#include "Neuron_Header.h"

using namespace std;

Link::Link(Neuron& new_input_Neuron, Neuron& new_output_Neuron) :
    weight(0),
    input_signal(0),
    output_signal(0),
    ptr_input_Neuron(new_input_Neuron),
    ptr_output_Neuron(new_output_Neuron) {
    ptr_input_Neuron.add_down_link(*this);
    ptr_output_Neuron.add_up_link(*this);
}

void Link::Set_weight(double new_weight) {
    weight = new_weight;
}

double Link::Get_weight() {
    return weight;
}

double Link::Get_input_signal() {
    return input_signal;
}

double Link::Get_output_signal() {
    return output_signal;
}

void Link::Set_input_neuron(Neuron& new_input_neuron) {
    ptr_input_Neuron = new_input_neuron;
}

void Link::Set_output_neuron(Neuron& new_output_neuron) {
    ptr_output_Neuron = new_output_neuron;
}

double Link::Generate_signal(double signal) {
    return signal * weight;
}

double Link::Activate_link_Ner2Ner() {
    double neuron_signal = ptr_input_Neuron.Get_output_signal();
    output_signal = Generate_signal(neuron_signal);
    return Get_output_signal();
}

double Link::Disactivate_link_Ner2Ner() {
    double neuron_mistake = ptr_output_Neuron.Get_output_mistake();
    input_signal = Generate_signal(neuron_mistake);
    return Get_input_signal();
}
