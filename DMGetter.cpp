/*###################################################################################################################*/

#include "DMath.h"

/*-------------------------------------------------------------------------------------------------------------------*/
// Получение вектора значений/аргумента

auto DMath::getValue(Format format, Type type) -> vector_d
{
	vector_d tempOut;
	vector_cd* tempIn{nullptr};

	switch (type)
	{
	case Type::FUNCTION:
		tempIn = &function;
		break;
	case Type::ARGUMENT:
		tempIn = &argument;
		break;
	default:
		std::cout << "Type error";
		exit(-1);
	}

	int size = static_cast<int>(tempIn->size());

	for (auto &member : *tempIn) {

		if (format == Format::ABS) { tempOut.push_back(abs(member)); }
		if (format == Format::REAL) { tempOut.push_back(member.real()); }
		if (format == Format::IMAG) { tempOut.push_back(member.imag()); }

	}

	return tempOut;
}

/*-------------------------------------------------------------------------------------------------------------------*/
// Получение tuple<Argument, Function>

auto DMath::getValue(Format format) -> tuple_dd 
{	
	if (argument.empty()) { fillArg(); }
	return {getValue(Format::REAL, Type::ARGUMENT), getValue(format, Type::FUNCTION) };
}

/*-------------------------------------------------------------------------------------------------------------------*/
// Вывод в файл значений Function и Argument

auto DMath::getFile(string name) -> void 
{
	using namespace std;

	ofstream file;
	file.open(name, ios::out);

	vector_d p1, p2;
	tie(p1, p2) = getValue();

	int size = static_cast<int>(p2.size());

	for (int i = 0; i < size; i++) {
		
		file.setf(ios::fixed);
		file.width(8);
		file.precision(6);

		if (p1.size() != p2.size()) {
			file << i << "\t" << p2[i] << endl;
		}
		else {
			file << p1[i] << "\t" << p2[i] << endl;
		}
		
	}

	file << endl;
	file.close();
}

/*===================================================================================================================*/