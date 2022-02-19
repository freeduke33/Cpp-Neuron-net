#ifndef _Link_Header_
#define _Link_Header_

class Neuron;

class Link
{
private:
    double weight; // signal = weight * input
    double input_signal;
    double output_signal;

    Neuron& ptr_input_Neuron; // ссылка на отправлающий нейрон
    Neuron& ptr_output_Neuron; // ссылка на принимающий нейрон

public:
    //Link(Neuron&, Neuron&);

    //void Set_weight(double);

    //double get_signal_to_end();

    //double get_signal_to_beg();

    // - - - - - - - - - - - - -
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

    void Activate_link_Ner2Ner();

    void Disactivate_link_Ner2Ner();

    void Activate_link_Input2Ner(double new_input_signal);

    double Disactivate_link_Input2Ner();
};

#endif