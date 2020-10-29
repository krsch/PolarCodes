#pragma once

#include <vector>
#include <tuple>

// for (256, 128) code!!!!
class FlipStatistic {
private:
	static const std::vector<int> _singles;
	static const std::vector<std::tuple<int, int>> _pairs;

public:
	static std::vector<int> GetSingles() {
		return _singles;
	}

	static std::vector<std::tuple<int, int>> GetPairs() {
		return _pairs;
	}

};

const std::vector<int> FlipStatistic::_singles = { 154, 79, 166, 156, 61, 153, 62, 165, 169, 224, 208, 87, 114, 170, 113, 116, 150, 108, 172, 195, 120, 91, 177, 197, 198, 106, 178, 143, 93, 180, 201, 151, 94, 209, 202, 107, 103, 184, 155, 204 };
const std::vector<std::tuple<int, int>> FlipStatistic::_pairs = {
{61, 62},
{153, 154},
{165, 166},
{154, 156},
{153, 156},
{61, 79},
{79, 87},
{165, 169},
{113, 114},
{113, 116},
{150, 153},
{150, 154},
{208, 224},
{169, 170},
{169, 172},
{166, 170},
{154, 165},
{106, 108},
{62, 79},
{154, 166},
{153, 165},
{166, 169},
{113, 120},
{108, 113},
{108, 114},
{114, 116},
{154, 155},
{150, 156},
{61, 87},
{79, 91},
{153, 166},
{166, 172},
{87, 91},
{114, 120},
{154, 169},
{165, 170},
{156, 166},
{106, 113},
{156, 165},
{79, 108}
};