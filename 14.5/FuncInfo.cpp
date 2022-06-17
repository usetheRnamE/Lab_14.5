#define _USE_MATH_DEFINES

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

#include <cmath>
#include <fstream>
#include <iostream>
#include <string>


double FuncCalculate(double x);

class FuncInfo {
public:

	int fluctuationCount;
	int fluctuationForInegralCount;

	double period;
	double frequency;
	double presicion;
	double aZero;

	struct KoefFile {
		std::ofstream fileRef;
		std::string fileName;
		std::string fileType;
	} aKoefFile, bKoefFile;

	FuncInfo() {

		std::cout << "The constructor is called" << '\n';

		fluctuationCount = 100;
		fluctuationForInegralCount = fluctuationCount * 3;

		period = 2 * M_PI;
		presicion = period / fluctuationForInegralCount;
		frequency = 2 * M_PI / period;

		aKoefFile.fileName = "AKoef";
		aKoefFile.fileType = ".txt";

		bKoefFile.fileName = "BKoef";
		bKoefFile.fileType = aKoefFile.fileType;

		CreateAFiles();

		for (double i = 0; i < period; i += presicion)
		{
			aZero += AZeroCalculate(i);
		}
	};

public:
	double ACalculate(double x, int currentFluctuation)
	{
		double a = 2 / period * FuncCalculate(x) * cos(currentFluctuation * frequency * x);

		WriteToTheFile(aKoefFile.fileRef, std::to_string(a));

		return a;
	}
public:
	double BCalculate(double x, int currentFluctuation) {
		double b = 2 / period * FuncCalculate(x) * sin(currentFluctuation * frequency * x);

		WriteToTheFile(bKoefFile.fileRef, std::to_string(b));

		return b;
	}
public:
	double AZeroCalculate(double x) {
		return pow(period, -1) * FuncCalculate(x);
	}

	void CreateAFiles()
	{
		aKoefFile.fileRef.open(aKoefFile.fileName + aKoefFile.fileType);
		bKoefFile.fileRef.open(bKoefFile.fileName + bKoefFile.fileType);

		std::cout << "Files are created" << '\n';
	}

	void WriteToTheFile(std::ofstream& currentFile, std::string txtToWrite)
	{

		if (currentFile)
			currentFile << txtToWrite;
		else
			std::cout << "Eror: file is null ref" << '\n';
	}

public:
	void CloseAllFiles()
	{
		_fcloseall();

		std::cout << "Files are Closed" << '\n';
	}
};