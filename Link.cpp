#include <iostream>
#include <vector>
#include <math.h>

#include "Link_Header.h"
#include "Neuron_Header.h"

using namespace std;

Link::Link(Neuron& new_input_Neuron, Neuron& new_output_Neuron, double new_learning_rate) :
    weight(0),
	learning_rate(new_learning_rate),
    input_signal(0),
    output_signal(0),
    ptr_input_Neuron(new_input_Neuron),
    ptr_output_Neuron(new_output_Neuron) {
    ptr_input_Neuron.add_down_link(*this);
    ptr_output_Neuron.add_up_link(*this);
}

void Link::Update_weight() {
    weight += ptr_input_Neuron.Get_output_signal() * ptr_output_Neuron.Get_output_mistake() * learning_rate;
    std::cout <<"link: weight=" <<weight
		<<" up_signal=" <<ptr_input_Neuron.Get_output_signal()
		<<" down_mistake=" <<ptr_output_Neuron.Get_output_mistake()
		<<" rate=" <<learning_rate
		<<std::endl;
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

double Link::Pass_through_link(double input_val) {
    double output_val = input_val * weight;
    std::cout <<"link: out=" <<output_val <<" inp=" <<input_val <<" w=" <<weight <<std::endl;
    return output_val;
}

double Link::Calc_output_signal() {
    double neuron_signal = ptr_input_Neuron.Get_output_signal();
    output_signal = Pass_through_link(neuron_signal);
    return Get_output_signal();
}

double Link::Calc_mistake() {
    double neuron_mistake = ptr_output_Neuron.Get_output_mistake();
    input_signal = Pass_through_link(neuron_mistake);
    return Get_input_signal();
}
