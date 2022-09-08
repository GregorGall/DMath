/*###################################################################################################################*/

#include "DMath.h"

/*-------------------------------------------------------------------------------------------------------------------*/
// Поворачивающий множитель

auto DMath::turnMult(double size, double n, double k) -> double_c
{
	//double range = rLimit - lLimit;
	double phi = 8 * atan(1) * n * k / size;
	return double_c(cos(phi), -mode * sin(phi));
}

/*-------------------------------------------------------------------------------------------------------------------*/
// БПФ с временной децимацией

auto DMath::tmFFT(int mode) -> DMath& 
{

	int size = function.size();
	int degree = static_cast<int>(log2(size));

	rearrange(&function, size, degree);

	for (int i = 0; i < degree; i++) {

		vector_cd temp;
		int range = static_cast<int>(pow(2, i + 1));

		for (int shift = 0; shift < size / range; shift++) {
			for (int j = 0; j < range; j++) {
				temp.push_back(function[j + shift * range]);
			}

			temp = dragonfly(temp);
			function.erase(function.begin() + shift * range, function.begin() + range + shift * range);
			function.insert(function.begin() + shift * range, temp.begin(), temp.end());
			temp.clear();
		}
	}

	if (mode == -1) {
		for (int i = 0; i < size; i++) {
			function[i] = { function[i].real() / size, function[i].imag() / size };
		}
	}

	return *this;
}

/*-------------------------------------------------------------------------------------------------------------------*/
// Полный граф "бабочка" в БПФ

auto DMath::dragonfly(vector_cd value) -> vector_cd {

	vector_cd temp, phalf, nhalf;
	vector_cd tempBF;

	int number = value.size();
	for (int i = 0; i < number / 2; i++) {
		double frq = 0.1*i +number * lLimit;
		auto tM = turnMult(number, frq);
		tempBF = butterfly(value[i], value[i + number / 2], turnMult(number, frq), number, i);
		phalf.push_back(tempBF[0]);
		nhalf.push_back(tempBF[1]);
	}

	temp.insert(temp.end(), phalf.begin(), phalf.end());
	temp.insert(temp.end(), nhalf.begin(), nhalf.end());

	return temp;
}


/*-------------------------------------------------------------------------------------------------------------------*/
// Граф "бабочка"

auto DMath::butterfly(double_c a, double_c b, double_c c, double size, double i) -> vector_cd
{
	double degree = log2(size / 2);
	double m = 0.1;
	double Nc = 8 * atan(1) * size * m;
	double phase = Nc /size;
	double_c W1{ cos(degree * phase), -sin(degree * phase) };
	double_c W2{ cos(phase / 2.0), -sin(phase / 2.0) };
	vector_cd value;
	if (size != 4) {
		value = { a + b * c, a * W1 + b * W1 * c * W2 };
	}
	else {
		value = { a + b * c, a*W1 + b *W1* c * W2 };
	}
	return value;
}

/*-------------------------------------------------------------------------------------------------------------------*/
// Предварительная перестановка

auto DMath::rearrange(vector_cd* value, int size, int degree) -> void
{

	for (int i = 0; i < degree - 1; i++) {

		vector_cd temp;
		int range = static_cast<int>(pow(2, degree - i));

		for (int shift = 0; shift < size / range; shift++) {
			for (int j = 0; j < range; j++) {
				temp.push_back((*value)[j + shift * range]);
			}

			temp = separation(temp);
			(*value).erase((*value).begin() + shift * range, (*value).begin() + range + shift * range);
			(*value).insert((*value).begin() + shift * range, temp.begin(), temp.end());
			temp.clear();
		}
	}
}

/*-------------------------------------------------------------------------------------------------------------------*/
// Разделение последовательности по четным и нечетным номерам

auto DMath::separation(vector_cd value) -> vector_cd
{

	vector_cd even;
	vector_cd odd;

	for (unsigned int i = 0; i < value.size() / 2; i++) {

		even.push_back(value[2 * i]);
		odd.push_back(value[2 * i + 1]);

	}

	value.clear();
	value.insert(value.end(), even.begin(), even.end());
	value.insert(value.end(), odd.begin(), odd.end());

	return value;
}

/*-------------------------------------------------------------------------------------------------------------------*/
// Перестановка:

DMath& DMath::roll() {

	int halfSize = function.size() / 2;
	std::vector<std::complex<double>> temp1, temp2;

	for (int i = 0; i < halfSize; i++) {
		temp1.push_back(function[i]);
		temp2.push_back(function[halfSize + i]);
	}

	function.clear();
	function.insert(function.end(), temp2.begin(), temp2.end());
	function.insert(function.end(), temp1.begin(), temp1.end());

	return *this;
}

/*===================================================================================================================*/