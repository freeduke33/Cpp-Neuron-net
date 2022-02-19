#include "TestOriginalSecond.h"

#include <iostream>
#include <cmath>

// sample network (second example) from:
// https://microtechnics.ru/obuchenie-nejronnoj-seti-algoritm-obratnogo-rasprostraneniya-oshibok/
//

NetOriginalSecond::NetOriginalSecond() :
		learn_norm(0.85),
		lx0(x,  n0, -1, learn_norm),
		lx1(x,  n1,  1, learn_norm),
		ly0(y,  n0,  1, learn_norm),
		ly1(y,  n1,  2, learn_norm),
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

NetOriginalSecond::~NetOriginalSecond()
{
}

double NetOriginalSecond::down(double i0, double i1) {
	x.Set_output_signal(i0);
	y.Set_output_signal(i1);

	n0.Summ_signals_from_UpLinks();
	n0.Activ_func();
	n1.Summ_signals_from_UpLinks();
	n1.Activ_func();

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

void NetOriginalSecond::up(double mistake) {
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

	std::cout <<"---- y" <<std::endl;
	y.Summ_mistake_from_DownLinks();
	y.Mistake_func();
	std::cout <<"---- x" <<std::endl;
	x.Summ_mistake_from_DownLinks();
	x.Mistake_func();

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

	ly0.Update_weight();
	ly1.Update_weight();

	lx0.Update_weight();
	lx1.Update_weight();
}

static bool eq(double v1, double v2) {
	return fabs(v1) - fabs(v2) < 0.01;
}

TestOriginalSecond::TestOriginalSecond() :
	succeed(true)
{
	std::cout <<"TestOriginalSecond: down ---------------" <<std::endl;

	double out = net.down(0.2, 0.5);
	double expected_out = 0.974; // FIXME: change to real value
	std::cout <<"n5.out expected=" <<expected_out <<" real=" <<out <<std::endl;
	succeed &= eq(out, expected_out);

	std::cout <<"TestOriginalSecond: up ---------------" <<std::endl;
	net.up(out - expected_out);
}

TestOriginalSecond::~TestOriginalSecond()
{
}

bool TestOriginalSecond::isOk() {
	return succeed;
}
