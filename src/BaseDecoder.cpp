#include <cmath>
#include <functional>

#include "../include/Exceptions.h"
#include "../include/BaseDecoder.h"
#include "../include/Domain.h"
#include "../include/OperationsCount.h"

BaseDecoder::BaseDecoder(PolarCode * codePtr) {
	_codePtr = codePtr;
	_sigma = 0;

	_crcPtr = new CRC(_codePtr->CrcPoly());

	ClearOperationsCount();
}

OperationsCount BaseDecoder::GetOperationsCount() {
	return _operationsCount;
}

void BaseDecoder::ClearOperationsCount() {

	_operationsCount.Sums = 0;
	_operationsCount.Muls = 0;
	_operationsCount.Comps = 0;
	_operationsCount.Xors = 0;
	_operationsCount.Normilizer = 0;
	_operationsCount.Iterations = 0;
}

void BaseDecoder::SetSigma(double sigma) {
	_sigma = sigma;
}

void BaseDecoder::SetDecoderAnswer(std::vector<int> codeword) {
	_codeword = codeword;
}

domain BaseDecoder::GetDomain() {
#ifdef DOMAIN_LLR
	return LLR;
#elif DOMAIN_P1
	return P1;
#endif
}

#ifdef DOMAIN_LLR

#ifdef MINSUM
double BaseDecoder::f(double x, double y) {
	double sign = 1.0;

	if (x < 0) {
		sign *= -1;
		x *= -1;
	}
	if (y < 0) {
		sign *= -1;
		y *= -1;
	}


	return ((x < y) ? x : y) * sign;
}
#else
double BaseDecoder::f(double llr1, double llr2) {
	double prod = tanh(llr1 / 2) * tanh(llr2 / 2);
	double limit = 0.9999999999999999;

	if (prod > limit)
		prod = limit;
	if (prod < -limit)
		prod = -limit;

	return 2 * atanh(prod);
}

#endif // MINSUM

double BaseDecoder::g(double x, double y, int b) {

	return y + (1 - 2 * b) * x;
}

int BaseDecoder::L(double llr) {
	
	return llr < 0;
}
#elif DOMAIN_P1

double BaseDecoder::f(double p1, double p2) {
	
	return p1 * (1 - p2) + p2 * (1 - p1);
}

double BaseDecoder::g(double p1, double p2, int b) {
	double p1_b = f(b, p1);


	if (p1_b == 0 && p2 == 1 || p2 == 0 && p1_b == 1)
		return 1 / 2;

	return p1_b * p2 / (p1_b * p2 + (1 - p1_b) * (1 - p2));
}

int BaseDecoder::L(double p1) {

	return p1 >= (0.5);
}
#endif


std::string BaseDecoder::GetStatistic() {
	return "";
}
void BaseDecoder::ClearStatistic() {
	
}

bool BaseDecoder::IsCrcPassed(std::vector<int> codeword) {
	size_t n = codeword.size();
	size_t k = _codePtr->k();
	size_t deg = _codePtr->CrcDeg();

	// if there is no CRC then all checks will be passed
	if (deg == 0)
		return true;

	auto wordBits = _codePtr->UnfrozenBits();
	std::vector<int> word(k, 0);
	for (size_t i = 0; i < k; i++)
	{
		word[i] = codeword[wordBits[i]];
	}

	auto crcBits = _codePtr->CrcUnfrozenBits();
	std::vector<int> crc(deg, 0);
	for (size_t i = 0; i < deg; i++)
	{
		crc[i] = codeword[crcBits[i]];
	}

	auto crcReal = _crcPtr->Calculate(word);

	return crc == crcReal;
}

//std::string BaseDecoder::GetPathInfo() {
//	return "";
//}
