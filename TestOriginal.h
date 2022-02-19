#ifndef TESTORIGINAL_H
#define TESTORIGINAL_H

#include "Neuron_Header.h"
#include "Link_Header.h"

class NetOriginal
{
public:
	NetOriginal();
	~NetOriginal();

	double down(double i0, double i1);
	void up(double err5);

	void dump();

private:
    double learn_norm;

public:
	Neuron n0, n1, n2, n3, n4, n5;

	Link l02, l03, l04;
	Link l12, l13, l14;
	Link l25, l35, l45;
};


class TestOriginal
{
public:
	TestOriginal();
	~TestOriginal();

	bool isOk();

private:
	NetOriginal net;
	bool succeed;
};

#endif // TESTORIGINAL_H
