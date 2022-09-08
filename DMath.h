/*###################################################################################################################*/
// ����� �������� ��� ����������� ����������

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

    double lLimit{ 0 };                                          // ����� ������ ��������� ��������������� �������
    double rLimit{ 0 };                                          // ������ ������ ��������� ��������������� �������
    double discrete{ 0 };                                        // ������� ����������
    vector_b setUp{ true, true };                                // ����� ������� ������ � �������� � ��

/*-------------------------------------------------------------------------------------------------------------------*/
// �������������� ������:

    auto preFFT(int N, int MODE)                 -> tuple_id;    // ���������� ����������� ���������

/*-------------------------------------------------------------------------------------------------------------------*/
// ������ ������:

    auto getArgument(int p)                      -> double;      // ���������� ����� ��������� �������� ���������
    auto getParametr(double p)                   -> double;      // ���������� ����� ��������� �������� ���������
    auto getTurnFactor(double mode,                              // ������ ��������������� ���������
                       double p1, 
                       double p2)                -> double_c;

public:
    
    vector_cd argument;                                          // ����������� ������ ���������� �������
    vector_cd function;                                          // ����������� ������ �������� �������

    DMath() {};
    DMath(vector_cd f) : function{ f } {};
    DMath(vector_cd a, vector_cd f) :argument{ a }, function{ f }{};

/*-------------------------------------------------------------------------------------------------------------------*/
// �������������� ������:

    auto roll()                                  -> DMath&;      // ������������ ����� � ������ �������� function
    auto cmFT(int mode = 1)                      -> DMath&;      // ������������ �������������� �����
    auto frFFT(int mode = 1, double T = 1)       -> DMath&;      // �������������� ����� � ��������� ����������
    auto convFT()                                -> DMath&;      // ������� function � function
    auto convFT(vector_cd& f1)                   -> DMath&;      // ������� function � f1
    auto convFT(vector_cd& f1, vector_cd& f2)    -> vector_cd;   // ������� f1 � f2
    auto convFFT()                               -> DMath&;      // ������� function � function ����� ���
    auto convFFT(vector_cd& f1)                  -> DMath&;      // ������� function � f1 ����� ���
    auto convFFT(vector_cd& f1, vector_cd& f2)   -> vector_cd;   // ������� f1 � f2 ����� ���
    auto nullApp()                               -> void;        // ���������� function ������ �� ������ ������� ������ 
    auto fillArg(double start = 0,
                 double step = 1)                ->DMath&;       // ���������� ���������  


    static auto conj(vector_cd f)                -> vector_cd;   // ����������� ���������� �������� ������� 
    static auto nullApp(vector_cd& f,
                        int app = 0)             -> void;        // ���������� ������ �� pow(2, app)
    static auto integral(dFunction function,                     
                  double a, 
                  double b, 
                  double step = 1)               -> double;      // ���������� ��������� ���������� �������

    auto friend operator*(vector_cd f1, 
                          vector_cd f2)          -> vector_cd;   // ���������� "*" ���������� ��������
    auto friend operator*(DMath dm1,
                          DMath dm2)             -> DMath;       // ���������� "*" ���������� �������� DMath

/*-------------------------------------------------------------------------------------------------------------------*/
// ������ �����:

    auto setAuto()                               -> DMath&;      // ��������� ���������� ������� �������� � ������ ��
    auto setRange(double lLimit, double rLimit)  -> DMath&;      // ��������� ������ ��������� ��������������� �������
    auto setDiscrete(double discrete)            -> DMath&;      // ��������� �������� �������� ��������� � ��

    auto setValue(int num, double_c value)       -> DMath&;
    auto setFunction(int num, cFunction fill)    -> DMath&;

/*-------------------------------------------------------------------------------------------------------------------*/
// ������ ������:

    auto getValue(Format format = Format::REAL)  -> tuple_dd;    // ��������� ������ �������� � ���������
    auto getValue(Format format, Type type)      -> vector_d;    // ��������� ������� ��������/���������
    auto getFile(string name = "DMath.txt")      -> void;        // ����� � ����
    
};

auto operator*(DMath dm1, DMath dm2) -> DMath;
auto operator*(DMath::vector_cd f1, DMath::vector_cd f2) -> DMath::vector_cd;

/*===================================================================================================================*/
