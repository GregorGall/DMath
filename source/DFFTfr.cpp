/*###################################################################################################################*/

#include "DMath.h"

/*-------------------------------------------------------------------------------------------------------------------*/
// БПФ с частотной децимацией (С.Л. Марпл Цифровой и спектральный анализ и его приложения Fortran) 

auto DMath::frFFT(int MODE, double T) -> DMath& 
{
	using namespace std;

	vector<complex<double>> W;
	vector<complex<double>> X;

	int NEXP;
	int N = static_cast<int>(function.size());

	/* Аргумент не переписывается -> T не зависит от MODE */
	if (!T) {
		T = (argument[1] - argument[0]).real();
	}
	

	tie(NEXP, W) = preFFT(N, MODE);
	N = static_cast<int>(pow(2, NEXP));
	X = function;

	int NN, JJ, KK = 0;
	int MM = 1;
	int LL = N;

	X.insert(X.begin(), 0);
	W.insert(W.begin(), 0);

	complex<double> C1, C2;

	for (int K = 1; K <= NEXP; K++) {
		NN = LL / 2;
		JJ = MM + 1;
		for (int I = 1; I <= N; I += LL) {
			KK = I + NN;
			C1 = X[I] + X[KK];
			X[KK] = X[I] - X[KK];
			X[I] = C1;
		}
		if (NN != 1) {
			for (int J = 2; J <= NN; J++) {
				C2 = W[JJ];
				for (int I = J; I <= N; I += LL) {
					KK = I + NN;
					C1 = X[I] + X[KK];
					X[KK] = (X[I] - X[KK]) * C2;
					X[I] = C1;
				}
				JJ = JJ + MM;
			}
			LL = NN;
			MM = MM * 2;
		}
	}

	int NV2 = N / 2;
	int NM1 = N - 1;
	int J = 1;

	for (int I = 1; I <= NM1; I++) {
		if (I < J) {
			C1 = X[J];
			X[J] = X[I];
			X[I] = C1;
		}
		int K = NV2;
		while (K < J) {
			J = J - K;
			K = K / 2;
		}
		J = J + K;
	}

	double S = 0;

	if (MODE == 1) { S = T; }
	else { S = 1 / (T * N); }

	for (int I = 1; I <= N; I++) {
		X[I] = X[I] * S;
	}

	X.erase(X.begin());
	function = X;

	return *this;
}

/*-------------------------------------------------------------------------------------------------------------------*/
// Предварительный синтез поворачивающих множителей

auto DMath::preFFT(int N, int MODE) -> tuple_id
{
	using namespace std;

	vector<complex<double>> W;
	complex<double> C1, C2;
	int NEXP, NT;
	double S, CHECK, N_temp;

	CHECK = modf(log2(N), &N_temp);

	if (CHECK == 0) {

		NEXP = int(N_temp);
		NT = static_cast<int>(pow(2, NEXP));
		S = 8 * atan(1) / (double)(NT);
		C1 = { cos(S), -sin(S) };
		if (MODE != 1) { C1 = std::conj(C1); }
		C2 = { 1,0 };
		
		for (int K = 1; K <= NT; K++) {
			W.push_back(C2);
			C2 = C2 * C1;
		}
	}
	else {
		NEXP = -1;
		cout << "Error: N - not degree of 2" << endl;
	}

	return { NEXP, W };
}

/*===================================================================================================================*/