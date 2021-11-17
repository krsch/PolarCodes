#include "PolarCode.h"
#include "ScCreeperDecoder.h"
#include "ScDecoder.h"
#include "ScOptimized.h"
#include <mex_cast.h>
#include <mex_commands.h>
#include <stdexcept>

void mex(mexbind0x::MXCommands & m) {
	m.on("free code", [](PolarCode * code) { delete code; });
	m.on("free decoder opt", [](ScOptimizedDecoder * ptr) { delete ptr; });
	m.on("code by used", [](int m, std::vector<int> usedBits) {
		return new PolarCode(m, std::move(usedBits));
	});
	m.on("code by reliability",
		[](int m, int k, std::vector<int> reliabilitySequence,
			std::vector<int> crcPoly) {
			return new PolarCode(m, k, std::move(reliabilitySequence),
				std::move(crcPoly));
		});
	m.on("make decoder",
		[](mexbind0x::matlab_string name, PolarCode * code, double delta) {
			if (name == u"creeper")
				return static_cast<ScOptimizedDecoder *>(
					new ScCreeperDecoder(code, delta));
			else
				throw std::invalid_argument("Unknown decoder");
		});
	m.on("decoder opt", &ScOptimizedDecoder::Decode);
	if (!m.has_matched())
		throw std::invalid_argument("Command not found");
}

MEX_SIMPLE(mex);
