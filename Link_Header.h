#ifndef _Link_Header_
#define _Link_Header_

class Neuron;

class Link
{
private:
    double weight; // signal = weight * input

    double input_signal;
    double output_signal;

    Neuron& ptr_input_Neuron; // ññûëêà íà îòïðàâëàþùèé íåéðîí
    Neuron& ptr_output_Neuron; // ññûëêà íà ïðèíèìàþùèé íåéðîí

    double Generate_signal(double input_signal);

public:
    Link(Neuron&, Neuron&);

    void Set_weight(double);

    double Get_weight();

    void Set_input_neuron(Neuron& new_input_neuron);

    void Set_output_neuron(Neuron& new_output_neuron);

    double Get_input_signal();

    double Get_output_signal();

    double Activate_link_Ner2Ner();

    double Disactivate_link_Ner2Ner();
};

#endif
