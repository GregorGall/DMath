/*###################################################################################################################*/

#include "DMath.h"

/*-------------------------------------------------------------------------------------------------------------------*/
// Перегрузка "*" умножением векторов:

auto operator*(DMath::vector_cd f1, DMath::vector_cd f2) -> DMath::vector_cd
{

    std::complex<double>* ptr = &f2.front();

    for (auto& value : f1) {
        value *= *ptr;
        ++ptr;

        if (ptr > &f2.back() + 1) {
            std::cout << "Vector multiply error: f2 < f1" << std::endl;
            break;
        }
    }

    return f1;
}

/*-------------------------------------------------------------------------------------------------------------------*/
// Перегрузка "*" умножением объектов DMath:

auto operator*(DMath dm1, DMath dm2) -> DMath
{
 
    dm1.function = dm1.function * dm2.function;
    return dm1;

}

/*-------------------------------------------------------------------------------------------------------------------*/
// Комплексное сопряжение значений вектора:

auto DMath::conj(vector_cd f) -> vector_cd {

    for (auto& value : f) {
        value = std::conj(value);
    }

    return f;
}

/*-------------------------------------------------------------------------------------------------------------------*/
// Интеграл:

auto DMath::integral(dFunction function, double a, double b, double step) -> double
{
    double value = function(a);
    double past{ value };
    int dots = static_cast<int>((b - a) / step);

    /* Добавить расчет до заданной точности */
    for (int i = 1; i <= dots; ++i) {

        double argument = a + i * step;
        double current = function(argument);
        value += 0.5 * (current + past) * step;
        past = current;

    }

    return value;

}

/*-------------------------------------------------------------------------------------------------------------------*/
// Дополнение нулями:

auto DMath::nullApp(vector_cd& f, int app) -> void
{

    int difference = static_cast<int>(pow(2, app) - f.size());

    if (difference >= 0) {
        for (int i = 0; i < difference; ++i) {
            f.push_back(0);
        }
    }
    else {
        std::cout << "NullApp error: pow(2, app) < f.size()";
    }
    
}

/*-------------------------------------------------------------------------------------------------------------------*/
// Дополнение function нулями до первой степени двойки:

auto DMath::nullApp() -> void
{
    auto degree = int(log2(function.size()));
    auto app = pow(2, degree) == function.size() ? degree : (degree + 1);

    nullApp(function, app);
}

/*-------------------------------------------------------------------------------------------------------------------*/
// Заполнение аргумента:  

auto DMath::fillArg(double start, double step) ->DMath&
{

    auto size = function.size();
    for (int i = 0; i < size; ++i) {
        double temp = start + i * step;
        argument.push_back(temp);
    }
    
    return *this;
}

/*-------------------------------------------------------------------------------------------------------------------*/
// Перестановка левой и правой половины function:

auto DMath::roll() -> DMath&
{
    
    auto half = function.size() / 2;
    function.insert(function.end(), function.begin(), function.begin() + half);
    function.erase(function.begin(), function.begin() + half);

    return *this;
}

/*===================================================================================================================*/