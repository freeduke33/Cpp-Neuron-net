#include <iostream>
#include <vector>
#include <math.h>

#include "Link_Header.h"
#include "Neuron_Header.h"

using namespace std;
/*
Link::Link(Neuron& input_Neuron, Neuron& output_Neuron) :
    ptr_input_Neuron(input_Neuron),
    ptr_output_Neuron(output_Neuron)
{
    ptr_input_Neuron.add_down_link(*this);
    ptr_output_Neuron.add_up_link(*this);
    weight = 0;
}

void Link::set_weight(double new_weight) {
    weight = new_weight;
}

double Link::get_signal_to_end() {
    return ptr_input_Neuron.Activ_func() * weight;
}

double Link::get_signal_to_beg() {
    return ptr_output_Neuron.Activ_func() * weight;
}
*/

// - - - - - - - - -

Link::Link(Neuron& new_input_Neuron, Neuron& new_output_Neuron) :
    ptr_input_Neuron(new_input_Neuron),
    ptr_output_Neuron(new_output_Neuron) {
    ptr_input_Neuron.add_down_link(*this);
    ptr_output_Neuron.add_up_link(*this);
}

void Link::set_weight(double new_weight) {
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

void Link::Set_input_signal(double new_input_signal) {
    input_signal = new_input_signal;
}

void Link::Set_output_signal(double new_output_signal) {
    output_signal = new_output_signal;
}

void Link::Set_input_neuron(Neuron& new_input_neuron) {
    ptr_input_Neuron = new_input_neuron;
}

void Link::Set_output_neuron(Neuron& new_output_neuron) {
    ptr_output_Neuron = new_output_neuron;
}

void Link::Generate_output_signal() {
    output_signal = input_signal * weight;
}

void Link::Activate_link_Ner2Ner() {
    Set_input_signal(ptr_input_Neuron.Get_output_signal());
    Generate_output_signal();
    ptr_output_Neuron.Set_input_signal(Link::Get_output_signal());
}

void Link::Disactivate_link_Ner2Ner() {
    Set_input_signal(ptr_output_Neuron.Get_output_mistake());
    Generate_output_signal();
    ptr_input_Neuron.Set_input_mistake(Link::Get_output_signal());
}

void Link::Activate_link_Input2Ner(double new_input_signal) {
    Set_input_signal(new_input_signal);
    Generate_output_signal();
    ptr_output_Neuron.Set_input_signal(Link::Get_output_signal());
}

double Link::Disactivate_link_Input2Ner() {
    Set_input_signal(ptr_output_Neuron.Get_output_mistake());
    Generate_output_signal();
    return Get_output_signal();
}