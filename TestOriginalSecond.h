#ifndef TESTORIGINALSECOND_H
#define TESTORIGINALSECOND_H

#include "Neuron_Header.h"
#include "Link_Header.h"

class NetOriginalSecond
{
public:
	NetOriginalSecond();
	~NetOriginalSecond();

	double down(double i0, double i1);
	void up(double err5);

private:
    double learn_norm;

public:
	Neuron x, y, n0, n1, n2, n3, n4, n5;

	Link lx0, lx1, ly0, ly1;
	Link l02, l03, l04;
	Link l12, l13, l14;
	Link l25, l35, l45;

};


class TestOriginalSecond
{
public:
	TestOriginalSecond();
	~TestOriginalSecond();

	bool isOk();

private:
	NetOriginalSecond net;
	bool succeed;
};


#endif // TESTORIGINALSECOND_H
