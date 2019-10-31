#pragma once
#include "CountingBloom.h"
#ifndef _COUNT_OCT_BLOOM_
#define _COUNT_OCT_BLOOM_

class CountOctBloom:public CountBloom
{
private:
	bool isOverflow(ull ind){ return table[ind] == 0xff;
	}
	bool isUnderflow(ull ind) { return table[ind] == 0; }
	void revOp(ull key, short i, bool ins);
public:
	CountOctBloom() = delete;
	CountOctBloom(ull len, short k = 5, short m = 8) :
		CountBloom( 2*len, k, m) {}
	CountOctBloom(const std::vector<ull>& inputVec,
		ull len, short k = 5, short m = 8) :
		CountBloom(2 * len, k, m)
	{
		ull i = 0;
		while (insertEntry(inputVec[i++])
			&& i < inputVec.size());
	}

	const bool insertEntry(ull key);
	const bool deleteEntry(ull key);
	const bool lookUp(ull key) const;

	const double & FNR(const std::vector<ull>& testTab) const;

	const double & FNR(const std::vector<ull>& testTab, const std::vector<ull>& delTab) const;

};
#endif // !_COUNT_OCT_BLOOM_
