#include <cmath>
#include "FuncInfo.cpp"

double FuncCalculate(double x) {
	return pow(3 + sin(x), -1);
}

double ApproximateFuncCalculate(double x)
{
	FuncInfo funcInfoReference;

	double result = 0;
	double trianArgument = 0;

	for (int i = 0; i < funcInfoReference.fluctuationForInegralCount; i++)
	{
		trianArgument = i * funcInfoReference.frequency * x;

		result += funcInfoReference.ACalculate(x, i) * cos(trianArgument)
			+ funcInfoReference.BCalculate(x, i) * sin(trianArgument);
	}

	return funcInfoReference.aZero + result;
}