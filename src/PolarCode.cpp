#include "../include/PolarCode.h"
#include "../include/Exceptions.h"
#include <algorithm>
PolarCode::PolarCode() {

}
PolarCode::PolarCode(int m, int k, std::vector<int> reliabilitySequence, std::vector<int> crcPoly) {
	_m = m;
	_k = k;
	_N = 2 << (m - 1);
	size_t sequenceLength = reliabilitySequence.size();
	if (_N != sequenceLength)
		throw IncorrectSequenceSizeException("Sequence length does not match with code length");

	_crcPoly = crcPoly;
	_crcDeg = _crcPoly.size();

	if (_k + _crcDeg > _N)
		throw CrcPolyException("Dimensions of a message with crc do not fit with dimension of a codeword ");

	_k_extended = _k + _crcDeg;

	_bitsMask = std::vector<int>(_N, 0);
	_maskWithCrc = std::vector<int>(_N, 0);
	_unfrozenPolarSequence = std::vector<int>(k, 0);
	for (size_t i = sequenceLength - k, j = 0; i < sequenceLength; i++, j++)
	{
		_bitsMask[reliabilitySequence[i]] = 1;
		_maskWithCrc[reliabilitySequence[i]] = 1;
		_unfrozenPolarSequence[j] = reliabilitySequence[i];
	}
	_unfrozenBits = _unfrozenPolarSequence;
	sort(_unfrozenBits.begin(), _unfrozenBits.end());

	// the mask and the set with crc
	_crcMask = std::vector<int>(_N, 0);
	if (IsCrcUsed()) {
		_crcUnfrozenPolarSequence = std::vector<int>(_crcDeg, 0);
		for (size_t i = sequenceLength - _k_extended, j = 0; i < sequenceLength - k; i++, j++)
		{
			_maskWithCrc[reliabilitySequence[i]] = 1;
			_crcMask[reliabilitySequence[i]] = 1;
			_crcUnfrozenPolarSequence[j] = reliabilitySequence[i];
		}
		_crcUnfrozenBits = _crcUnfrozenPolarSequence;
		sort(_crcUnfrozenBits.begin(), _crcUnfrozenBits.end());
	}
	_unfrozenPolarSequenceWithCrc = _unfrozenPolarSequence;
	_unfrozenPolarSequenceWithCrc.insert(_unfrozenPolarSequenceWithCrc.begin(), _crcUnfrozenPolarSequence.begin(), _crcUnfrozenPolarSequence.end());

	_unfrozenBitsWithCrc = _unfrozenPolarSequenceWithCrc;
	sort(_unfrozenBitsWithCrc.begin(), _unfrozenBitsWithCrc.end());
}

// CRC is not supported yet
PolarCode::PolarCode(int m, std::vector<int> usedBits)
	: _m(static_cast<size_t>(m)), _N(1 << _m), _bitsMask(_N), _maskWithCrc(_N) {
	_crcPoly = {};
	_crcDeg = 0;

	_k_extended = _k = usedBits.size();

	for (size_t i = 0; i < _k; i++) {
		_bitsMask[usedBits[i]] = 1;
		_maskWithCrc[usedBits[i]] = 1;
	}

	_unfrozenPolarSequence = usedBits;
	_unfrozenBits = _unfrozenPolarSequence;
	sort(_unfrozenBits.begin(), _unfrozenBits.end());

	_unfrozenPolarSequenceWithCrc = _unfrozenPolarSequence;
	_unfrozenBitsWithCrc = _unfrozenBits;
}

// CRC is not supported yet
void PolarCode::InitWithNewSequence(int m, std::vector<int> usedBits) {
	_crcPoly = {};
	_crcDeg = 0;

	_m = m;
	_k_extended = _k = usedBits.size();
	_N = 1 << _m;

	_bitsMask = std::vector<int>(_N, 0);
	for (size_t i = 0; i < _k; i++)
		_bitsMask[usedBits[i]] = 1;

	_unfrozenPolarSequence = usedBits;
	_unfrozenBits = _unfrozenPolarSequence;
	sort(_unfrozenBits.begin(), _unfrozenBits.end());

	_unfrozenPolarSequenceWithCrc = _unfrozenPolarSequence;
	_unfrozenBitsWithCrc = _unfrozenBits;
}

size_t PolarCode::m() {
	return _m;
}
size_t PolarCode::N() {
	return _N;
}
size_t PolarCode::k() {
	return _k;
}
size_t PolarCode::kExt() {
	return _k_extended;
}

std::vector<int> PolarCode::BitsMask() {
	return _bitsMask;
}

std::vector<int> PolarCode::UnfrozenBits() {
	return _unfrozenBits;
}

std::vector<int> PolarCode::BitsMaskWithCrc() {
	
	return _maskWithCrc;
}

std::vector<int> PolarCode::UnfrozenPolarSequence() {
	return _unfrozenPolarSequence;
}

std::vector<int> PolarCode::UnfrozenPolarSequenceWithCrc() {
	return _unfrozenPolarSequenceWithCrc;
}

std::vector<int> PolarCode::CrcMask() {
	return _crcMask;
}

std::vector<int> PolarCode::UnfrozenBitsWithCrc() {
	return _unfrozenBitsWithCrc;
}

std::vector<int> PolarCode::CrcUnfrozenBits() {
	return _crcUnfrozenBits;
}

bool PolarCode::IsCrcUsed() {
	return !_crcPoly.empty();
}

std::vector<int> PolarCode::CrcPoly() {
	return _crcPoly;
}

size_t PolarCode::CrcDeg() {
	return _crcDeg;
}
