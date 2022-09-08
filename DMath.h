/*###################################################################################################################*/
// Класс операций над дискретными значениями

#pragma once

#include <tuple>
#include <cmath>
#include <vector>
#include <complex>
#include <fstream>
#include <iostream>
#include <algorithm> 

#include "DMTypes.h"

/*###################################################################################################################*/

class DMath
{
    friend class LabSource;

public:

    using string    = std::string;
    using vector_b  = std::vector<bool>;
    using vector_d  = std::vector<double>;
    using double_c  = std::complex<double>;
    using vector_cd = std::vector<std::complex<double>>;
    using tuple_id  = std::tuple<int, std::vector<std::complex<double>>>;
    using tuple_dd  = std::tuple<std::vector<double>, std::vector<double>>;

    using dFunction = double (*)(double);
    using cFunction = double_c (*)(int);

private:

    double lLimit{ 0 };                                          // Левый предел аргумента преобразованной функции
    double rLimit{ 0 };                                          // Правый предел аргумента преобразованной функции
    double discrete{ 0 };                                        // Дискрет вычисления
    vector_b setUp{ true, true };                                // Режим расчета границ и дискрета в ПФ

/*-------------------------------------------------------------------------------------------------------------------*/
// Вычислительные методы:

    auto preFFT(int N, int MODE)                 -> tuple_id;    // Вычисление комплексных экспонент

/*-------------------------------------------------------------------------------------------------------------------*/
// Методы вывода:

    auto getArgument(int p)                      -> double;      // Внутренний метод получения значения аргумента
    auto getParametr(double p)                   -> double;      // Внутренний метод получения значения параметра
    auto getTurnFactor(double mode,                              // Расчет поворачивающего множителя
                       double p1, 
                       double p2)                -> double_c;

public:
    
    vector_cd argument;                                          // Комплексный вектор аргументов функции
    vector_cd function;                                          // Комплексные вектор значений функции

    DMath() {};
    DMath(vector_cd f) : function{ f } {};
    DMath(vector_cd a, vector_cd f) :argument{ a }, function{ f }{};

/*-------------------------------------------------------------------------------------------------------------------*/
// Вычислительные методы:

    auto roll()                                  -> DMath&;      // Перестановка левой и правой половины function
    auto cmFT(int mode = 1)                      -> DMath&;      // Классическое преобразование Фурье
    auto frFFT(int mode = 1, double T = 1)       -> DMath&;      // Преобразование Фурье с частотной децимацией
    auto convFT()                                -> DMath&;      // Свертка function с function
    auto convFT(vector_cd& f1)                   -> DMath&;      // Свертка function с f1
    auto convFT(vector_cd& f1, vector_cd& f2)    -> vector_cd;   // Свертка f1 с f2
    auto convFFT()                               -> DMath&;      // Свертка function с function через БПФ
    auto convFFT(vector_cd& f1)                  -> DMath&;      // Свертка function с f1 через БПФ
    auto convFFT(vector_cd& f1, vector_cd& f2)   -> vector_cd;   // Свертка f1 с f2 через БПФ
    auto nullApp()                               -> void;        // Дополнение function нулями до первой степени двойки 
    auto fillArg(double start = 0,
                 double step = 1)                ->DMath&;       // Заполнение аргумента  


    static auto conj(vector_cd f)                -> vector_cd;   // Комплексное сопряжение значений вектора 
    static auto nullApp(vector_cd& f,
                        int app = 0)             -> void;        // Дополнение нулями до pow(2, app)
    static auto integral(dFunction function,                     
                  double a, 
                  double b, 
                  double step = 1)               -> double;      // Вычисление интеграла переданной функции

    auto friend operator*(vector_cd f1, 
                          vector_cd f2)          -> vector_cd;   // Перегрузка "*" умножением векторов
    auto friend operator*(DMath dm1,
                          DMath dm2)             -> DMath;       // Перегрузка "*" умножением объектов DMath

/*-------------------------------------------------------------------------------------------------------------------*/
// Методы ввода:

    auto setAuto()                               -> DMath&;      // Установка авторежима расчета дискрета и границ ПФ
    auto setRange(double lLimit, double rLimit)  -> DMath&;      // Установка границ аргумента преобразованной функции
    auto setDiscrete(double discrete)            -> DMath&;      // Установка величины дискрета аргумента в ПФ

    auto setValue(int num, double_c value)       -> DMath&;
    auto setFunction(int num, cFunction fill)    -> DMath&;

/*-------------------------------------------------------------------------------------------------------------------*/
// Методы вывода:

    auto getValue(Format format = Format::REAL)  -> tuple_dd;    // Получение тьюпла значений и аргумента
    auto getValue(Format format, Type type)      -> vector_d;    // Получение вектора значений/аргумента
    auto getFile(string name = "DMath.txt")      -> void;        // Вывод в файл
    
};

auto operator*(DMath dm1, DMath dm2) -> DMath;
auto operator*(DMath::vector_cd f1, DMath::vector_cd f2) -> DMath::vector_cd;

/*===================================================================================================================*/
