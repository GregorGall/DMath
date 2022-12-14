/*###################################################################################################################*/

#include "DMath.h"

/*-------------------------------------------------------------------------------------------------------------------*/
// Установка диапазона вычислений аргумента

auto DMath::setRange(double lLimit, double rLimit) -> DMath& 
{

    DMath::lLimit = lLimit;
    DMath::rLimit = rLimit;

    setUp[0] = false;
    return *this;
}

/*-------------------------------------------------------------------------------------------------------------------*/
// Установка значения дискрета

auto DMath::setDiscrete(double discrete) -> DMath&
{
    DMath::discrete = discrete;

    setUp[1] = false;
    return *this;
}

/*-------------------------------------------------------------------------------------------------------------------*/
// Установка значения дискрета

auto DMath::setAuto() -> DMath&
{
    setUp = { true, true };
    return *this;
}

/*-------------------------------------------------------------------------------------------------------------------*/
// Заполнение функции значениями value

auto DMath::setValue(int num, double_c value) -> DMath& {

    function.clear();
    argument.clear();

    for (int i = 0; i < num; ++i) {
        function.push_back(value);
    }

    return *this;
}

/*-------------------------------------------------------------------------------------------------------------------*/
// Заполнение функции значениями fill;

auto DMath::setFunction(int num, cFunction fill) -> DMath& {
   
    function.clear();
    argument.clear();

    for (int i = 0; i < num; ++i) {
        function.push_back(fill(i));
    }

    return *this;
}

/*===================================================================================================================*/