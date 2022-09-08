/*###################################################################################################################*/

#include "DMath.h"

/*-------------------------------------------------------------------------------------------------------------------*/
// ������ �������� ��������� ��������������� ������� (������/�������):

auto DMath::getParametr(double p) -> double
{
	return lLimit + discrete * p;
}

/*-------------------------------------------------------------------------------------------------------------------*/
// ������ ��������������� ���������:

auto DMath::getArgument(int p) -> double
{

	if (argument.empty()) { return p; }
	return argument[p].real();
}

/*-------------------------------------------------------------------------------------------------------------------*/
// ������ ��������������� ���������:

auto DMath::getTurnFactor(double mode, double p1, double p2) -> double_c
{

	p1 = getParametr(p1);
	p2 = getArgument(static_cast<int>(p2));

	double phase = 8 * atan(1) * p1 * p2;
	return {cos(phase), -mode*sin(phase)};
}

/*-------------------------------------------------------------------------------------------------------------------*/
// ������������ �������������� �����:

auto DMath::cmFT(int mode) -> DMath&
{

	vector_cd tFunction;
	vector_cd tArgument;

	int size = (int)function.size();

	double timeDiscrete{ 1 };

	if (!argument.empty()) {
		timeDiscrete = (argument[1] - argument[0]).real();
	}

	if (setUp[0]) {
		rLimit = 0.5 / timeDiscrete;
		lLimit = -0.5 / timeDiscrete;
	}
	
	if (setUp[1]) { discrete = (rLimit - lLimit) / function.size(); }
	int argSize = static_cast<int>((rLimit - lLimit) / discrete);

	/* ���� ���������� �������� ����� ������� S(w)||f(t) � ����������� �� mode */
	for (int i = 0; i < argSize; i++) {                   

		double_c temp{ 0,0 };

		/* �������� �� ������� ��������� ������� */
		for (int j = 0; j < size; j++) {           
			temp += function[j] * getTurnFactor(mode, i, j);
		}

		if (mode == -1) {
			temp = { temp.real() / size, temp.imag() / size };
		}

		tFunction.push_back(temp);
		tArgument.push_back(getParametr(i));

	}

	function = tFunction;
	argument = tArgument;

	return *this;
}

/*===================================================================================================================*/