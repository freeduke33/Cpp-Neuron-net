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

public:
    Link(Neuron&, Neuron&);

    void Set_weight(double);

    double Get_weight();

    void Set_input_neuron(Neuron& new_input_neuron);

    void Set_output_neuron(Neuron& new_output_neuron);

    double Get_input_signal();

    double Get_output_signal();

    void Set_input_signal(double new_input_signal);

    void Set_output_signal(double new_output_signal);

    void Generate_output_signal();

    double Activate_link_Ner2Ner();

    double Disactivate_link_Ner2Ner();

    double Activate_link_Input2Ner(double new_input_signal);

    double Disactivate_link_Input2Ner();
};

#endif
