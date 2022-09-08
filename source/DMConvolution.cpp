/*###################################################################################################################*/

#include "DMath.h"
auto operator*(DMath::vector_cd f1, DMath::vector_cd f2) -> DMath::vector_cd;

/*-------------------------------------------------------------------------------------------------------------------*/
// Свертка через БПФ:

auto DMath::convFFT(vector_cd& f1, vector_cd& f2)->vector_cd
{
    DMath t1, t2;

    t1.function = f1;
    t2.function = f2;

    auto max = f1.size() > f2.size() ? f1.size() : f2.size();
    auto degree = int(log2(max));

    /* +1 требуется даже при совпадении со степенью 2, для сохранения размеров вектора, т.к. половина частот
    будет выкинута. +2 требуется в случае необходимости дополнения сначала до степени 2 */
    auto app = pow(2, degree) == max ? (degree + 1) : (degree + 2);

    t1.nullApp(t1.function, app);
    t2.nullApp(t2.function, app);

    t1.frFFT();
    t2.frFFT();

    t1.function = t1.function * conj(t2.function);

    /* Выкидываем частоты выше половины частоты дискретизации (см. convFT) */
    t1.function.resize(t1.function.size() / 2);

    t1.frFFT(-1);

    return t1.function;
}

/*-------------------------------------------------------------------------------------------------------------------*/
// Свертка function c f через БПФ:

auto DMath::convFFT(vector_cd& f) -> DMath&
{
    function = convFFT(function, f);
    argument.clear();

    for (int i = 0; i < static_cast<int>(function.size()); ++i) {
        argument.push_back(i);
    }

    return *this;
}

/*-------------------------------------------------------------------------------------------------------------------*/
// Свертка function c function через БПФ:

auto DMath::convFFT() -> DMath&
{
    convFFT(function);
    return *this;
}

/*-------------------------------------------------------------------------------------------------------------------*/
// Свертка:

auto DMath::convFT(vector_cd& f1, vector_cd& f2) -> vector_cd
{

    DMath t1, t2;
    t1.function = f1;
    t2.function = f2;

    /* Так как в случае пустого argument, discrete = 1, то dFrequency = 0.5 */
    t1.setRange(0, 0.5);
    t1.cmFT();

    t2.setRange(0, 0.5);
    t2.setDiscrete(t1.discrete);
    t2.cmFT();

    t1.function = t1.function * conj(t2.function);

    int size = f1.size() + f2.size();

    t1.setRange(-0.5 * size, 0.5 * size);
    t1.cmFT(-1).function;

    return t1.function;
}

/*-------------------------------------------------------------------------------------------------------------------*/
// Свертка function c f:

auto DMath::convFT(vector_cd& f) -> DMath&
{
    function = convFT(function, f);
    return *this;
}

/*-------------------------------------------------------------------------------------------------------------------*/
// Свертка function c function:

auto DMath::convFT() -> DMath&
{
    function = convFT(function, function);
    return *this;
}

/*===================================================================================================================*/