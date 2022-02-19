#include <iostream>
#include <vector>
#include <math.h>

#include "Neuron_Header.h"
#include "Link_Header.h"

using namespace std;

double Neuron::Active_func_vard(double input) {
    double ret = 1.0 / (1.0 + exp(-input));
	std::cout <<"active: ret=" <<ret <<" inp=" <<input << std::endl;
	return ret;
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

void Neuron::Set_input_signal_testonly(double signal) {
    input_signal = signal;
}

void Neuron::Set_output_signal(double new_output_signal) {
    output_signal = new_output_signal;
}

double Neuron::Get_input_signal() {
    return input_signal;
}

double Neuron::Activ_func() {
    return output_signal = Active_func_vard(input_signal);
}

double Neuron::Get_output_signal() {
    return output_signal;
}

void Neuron::Summ_signals_from_UpLinks() {
	input_signal = 0;
    for (int i = 0; i < Up_links.size(); i++) {
        double signal_from_uplink = Up_links[i]->Calc_output_signal();
        input_signal = input_signal + signal_from_uplink;
    }
}

void Neuron::add_up_link(Link& up_link) {
    Up_links.push_back(&up_link);
}

// - - - - - -

double Neuron::Mistake_func() {
    output_mistake = input_mistake * Active_func_vard(input_signal)*(1 - Active_func_vard(input_signal));
	std::cout <<"output_mistake=" <<output_mistake <<" input_mistake=" <<input_mistake <<" input_signal=" <<input_signal <<std::endl;
    return output_mistake;
}

double Neuron::Set_input_mistake(double input) {
    return input_mistake = input;
}

double Neuron::Get_input_mistake() {
    return input_mistake;
}

double Neuron::Get_output_mistake() {
    return output_mistake;
}

void Neuron::Summ_mistake_from_DownLinks() {
    input_mistake = 0;
    for (int i = 0; i < Down_links.size(); i++) {
        double mistake_from_downlink = Down_links[i]->Calc_mistake();
        input_mistake = input_mistake + mistake_from_downlink;
        std::cout <<"sum: input_mistake=" <<input_mistake <<" mistake_from_downlink=" <<mistake_from_downlink << std::endl;
    }
}

void Neuron::add_down_link(Link& down_link) {
    Down_links.push_back(&down_link);
}

// - - - - - -

