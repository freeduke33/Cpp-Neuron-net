#ifndef _Link_Header_
#define _Link_Header_

class Neuron;

class Link
{
private:
    double weight; // signal = weight * input
	double learning_rate;
    double input_signal;
    double output_signal;

    Neuron& ptr_input_Neuron; // ññûëêà íà îòïðàâëàþùèé íåéðîí
    Neuron& ptr_output_Neuron; // ññûëêà íà ïðèíèìàþùèé íåéðîí

    double Pass_through_link(double input_val);

public:
    Link(Neuron&, Neuron&, double learning_rate);

    void Set_weight(double);

    void Update_weight();

    double Get_weight();

    double Get_input_signal();

    double Get_output_signal();

    double Calc_output_signal();

    double Calc_mistake();
};

#endif
