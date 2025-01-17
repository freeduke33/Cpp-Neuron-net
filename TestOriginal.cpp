#include "TestOriginal.h"
#include "Link_Header.h"

#include <iostream>
#include <cmath>

// sample network from:
// https://microtechnics.ru/obuchenie-nejronnoj-seti-algoritm-obratnogo-rasprostraneniya-oshibok/

NetOriginal::NetOriginal() :
		learn_norm(0.85),
		l02(n0, n2, -1, learn_norm),
		l03(n0, n3,  1, learn_norm),
		l04(n0, n4,  3, learn_norm),
		l12(n1, n2,  2, learn_norm),
		l13(n1, n3,  1, learn_norm),
		l14(n1, n4, -2, learn_norm),
		l25(n2, n5,  1, learn_norm),
		l35(n3, n5,  2, learn_norm),
		l45(n4, n5,  4, learn_norm)
{
}

NetOriginal::~NetOriginal()
{
}


double NetOriginal::down(double i0, double i1) {
	n0.Set_output_signal(i0);
	n1.Set_output_signal(i1);

	n2.Summ_signals_from_UpLinks();
	n2.Activ_func();
	n3.Summ_signals_from_UpLinks();
	n3.Activ_func();
	n4.Summ_signals_from_UpLinks();
	n4.Activ_func();

	n5.Summ_signals_from_UpLinks();
	n5.Activ_func();
	return n5.Get_output_signal();
}

void NetOriginal::up(double mistake) {
	std::cout <<"---- n5" <<std::endl;
	n5.Set_input_mistake(mistake);
	n5.Mistake_func();

	std::cout <<"---- n4" <<std::endl;
	n4.Summ_mistake_from_DownLinks();
	n4.Mistake_func();
	std::cout <<"---- n3" <<std::endl;
	n3.Summ_mistake_from_DownLinks();
	n3.Mistake_func();
	std::cout <<"---- n2" <<std::endl;
	n2.Summ_mistake_from_DownLinks();
	n2.Mistake_func();

	std::cout <<"---- n1" <<std::endl;
	n1.Summ_mistake_from_DownLinks();
	n1.Mistake_func();
	std::cout <<"---- n0" <<std::endl;
	n0.Summ_mistake_from_DownLinks();
	n0.Mistake_func();

	// necessary but missed step/method
	l25.Update_weight();
	l35.Update_weight();
	l45.Update_weight();

	l12.Update_weight();
	l13.Update_weight();
	l14.Update_weight();

	l02.Update_weight();
	l03.Update_weight();
	l04.Update_weight();
}

void NetOriginal::dump() {

}


static bool eq(double v1, double v2) {
	return fabs(v1) - fabs(v2) < 0.01;
}

TestOriginal::TestOriginal() :
	succeed(true)
{
	std::cout <<"TestOriginal: down" <<std::endl;

	double out = net.down(0.2, 0.5);
	double expected_out = 0.974;
	std::cout <<"n5.out expected=" <<expected_out <<" real=" <<out <<std::endl;
	succeed &= eq(out, expected_out);

	double expected_i2 = -1 * 0.2  +  2 * 0.5;
	double expected_i3 =  1 * 0.2  +  1 * 0.5;
	double expected_i4 = -2 * 0.5  +  3 * 0.2;
	double expected_i5 =  1 * 0.69 +  2 * 0.67  +  4 * 0.4;
	double in;

	in = net.n2.Get_input_signal();
	std::cout <<"n2.in expected=" <<expected_i2 <<" real=" <<in <<std::endl;
	succeed &= eq(in, expected_i2);

	in = net.n3.Get_input_signal();
	std::cout <<"n3.in expected=" <<expected_i3 <<" real=" <<in <<std::endl;
	succeed &= eq(in, expected_i3);

	in = net.n4.Get_input_signal();
	std::cout <<"n4.in expected=" <<expected_i4 <<" real=" <<in <<std::endl;
	succeed &= eq(in, expected_i4);

	in = net.n5.Get_input_signal();
	std::cout <<"n5.in expected=" <<expected_i5 <<" real=" <<in <<std::endl;
	succeed &= eq(in, expected_i5);

	double expected_o0 = 0.2;
	double expected_o1 = 0.5;
	double expected_o2 = 0.69;
	double expected_o3 = 0.67;
	double expected_o4 = 0.40;

	out = net.n0.Get_output_signal();
	std::cout <<"n0.out expected=" <<expected_o0 <<" real=" <<out <<std::endl;
	succeed &= eq(out, expected_o0);

	out = net.n1.Get_output_signal();
	std::cout <<"n1.out expected=" <<expected_o1 <<" real=" <<out <<std::endl;
	succeed &= eq(out, expected_o1);

	out = net.n2.Get_output_signal();
	std::cout <<"n2.out expected=" <<expected_o2 <<" real=" <<out <<std::endl;
	succeed &= eq(out, expected_o2);

	out = net.n3.Get_output_signal();
	std::cout <<"n3.out expected=" <<expected_o3 <<" real=" <<out <<std::endl;
	succeed &= eq(out, expected_o3);

	out = net.n4.Get_output_signal();
	std::cout <<"n4.out expected=" <<expected_o4 <<" real=" <<out <<std::endl;
	succeed &= eq(out, expected_o4);

	if (succeed) {
		std::cout <<"TestOriginal: up" <<std::endl;
		double good_out = 0.4;
		net.up(good_out - expected_out);
		net.dump();
		double expected_w02 = -1 + 0.2 * (-0.0029) * 0.85;
		double expected_w03 =  1 + 0.2 * (-0.0061) * 0.85;
		double expected_w04 =  3 + 0.2 * (-0.0134) * 0.85;

		double expected_w12 =  2 + 0.5 * (-0.0029) * 0.85;
		double expected_w13 =  1 + 0.5 * (-0.0061) * 0.85;
		double expected_w14 = -2 + 0.5 * (-0.0134) * 0.85;

		double expected_w25 =  1 + 0.69 * (-0.0014) * 0.85;
		double expected_w35 =  2 + 0.67 * (-0.0014) * 0.85;
		double expected_w45 =  4 + 0.40 * (-0.0014) * 0.85;

		double w;
		// 0x
		w = net.l02.Get_weight();
		std::cout <<"w02 expected=" <<expected_w02 <<" real=" <<w <<std::endl;
		succeed &= eq(w, expected_w02);

		w = net.l03.Get_weight();
		std::cout <<"w03 expected=" <<expected_w03 <<" real=" <<w <<std::endl;
		succeed &= eq(w, expected_w03);

		w = net.l04.Get_weight();
		std::cout <<"w04 expected=" <<expected_w04 <<" real=" <<w <<std::endl;
		succeed &= eq(w, expected_w04);

		// 1x
		w = net.l12.Get_weight();
		std::cout <<"w12 expected=" <<expected_w12 <<" real=" <<w <<std::endl;
		succeed &= eq(w, expected_w12);

		w = net.l13.Get_weight();
		std::cout <<"w013 expected=" <<expected_w13 <<" real=" <<w <<std::endl;
		succeed &= eq(w, expected_w13);

		w = net.l14.Get_weight();
		std::cout <<"w14 expected=" <<expected_w14 <<" real=" <<w <<std::endl;
		succeed &= eq(w, expected_w14);

		// x5
		w = net.l25.Get_weight();
		std::cout <<"w25 expected=" <<expected_w25 <<" real=" <<w <<std::endl;
		succeed &= eq(w, expected_w25);

		w = net.l35.Get_weight();
		std::cout <<"w35 expected=" <<expected_w35 <<" real=" <<w <<std::endl;
		succeed &= eq(w, expected_w35);

		w = net.l45.Get_weight();
		std::cout <<"w45 expected=" <<expected_w45 <<" real=" <<w <<std::endl;
		succeed &= eq(w, expected_w45);
	}
}

TestOriginal::~TestOriginal()
{
}

bool TestOriginal::isOk() {
	return succeed;
}
