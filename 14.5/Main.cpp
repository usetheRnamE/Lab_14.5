#include "pbPlots.hpp"
#include "supportLib.hpp"
#include "FuncInfo.cpp"

#include <vector>
#include <iostream>

double FuncCalculate(double x);
double ApproximateFuncCalculate(double x);

FuncInfo funcInfoReference;

struct Vectors {
	std::vector<double> X;
	std::vector<double> Y;
} FuncVec, AppFuncVec;

struct ImgReference {
	RGBABitmapImageReference* ImgRef = CreateRGBABitmapImageReference();
} funcImgRef, appFuncImgRef;

struct FileName {
	std::string fileName;
	std::string fileType = ".png";
} funcFile, appFuncFile;

void FuncVectorSetUp(double x)
{
	FuncVec.X.push_back(x);
	FuncVec.Y.push_back(FuncCalculate(x));
}

void AppFuncVectorSetUp(double x)
{
	AppFuncVec.X.push_back(x);
	AppFuncVec.Y.push_back(FuncCalculate(x));
}

void DrawTheFunc(RGBABitmapImageReference* currentImgRef, std::string fileName, std::string fileType)
{
	std::cout << "Drawing has been started" << '\n';

	DrawScatterPlot(currentImgRef, 600, 400, &FuncVec.X, &FuncVec.Y, nullptr);

	std::vector<double>* pngData = ConvertToPNG(currentImgRef->image);
	WriteToFile(pngData, fileName + fileType);
	DeleteImage(currentImgRef->image);
}

int main()
{
	std::cout << "Program has been started" << '\n';

	for (double x = 0; x < funcInfoReference.fluctuationCount; x += funcInfoReference.presicion)
	{
		FuncVectorSetUp(x);
		AppFuncVectorSetUp(x);
	}

	funcFile.fileName = "Func";
	appFuncFile.fileName = "AppFunc";

	DrawTheFunc(funcImgRef.ImgRef, funcFile.fileName, funcFile.fileType);
	DrawTheFunc(appFuncImgRef.ImgRef, appFuncFile.fileName, appFuncFile.fileType);

	funcInfoReference.CloseAllFiles();
	std::cout << "Program has been finished" << '\n';
}

