#pragma once
#ifndef _COUNTING_BLOOM_
#define _COUNTING_BLOOM_

#include "DietzHash.h"
#include <cmath>



class CountBloom
{
protected:
	ull tabLen;
	short hashNum;
	ull* hashFac;
	uchar* table;
	void init();
	bool isOverflow(ull ind);
	bool isUnderflow(ull ind);
	void revOp(ull key, short i, bool ins);
public:
	bool isThere = 0;
	CountBloom() = delete;
	CountBloom(ull len, short k = 5, short m = 8);
	CountBloom(const std::vector<ull>& inputVec, ull len, double eps);
	CountBloom(const std::vector<ull>& inputVec, ull len, short k = 5, short m = 8);
	CountBloom(const CountBloom& cb);

	const bool insertEntry(ull key);
	const bool deleteEntry(ull key);

	 virtual const bool lookUp(ull key) const;

	const bool& isFP(const std::vector<ull>& testTab,
		const std::vector<ull>& insTab,
		const std::vector<ull>& delTab,
		const ull & key)
	{
		return (lookUp(key) &&
			(!std::binary_search(testTab.begin(), testTab.end(), key) &&
				!std::binary_search(insTab.begin(), insTab.end(), key) ||
				std::binary_search(delTab.begin(), delTab.end(), key)));
	}

	const double & FNR(const std::vector<ull>& testTab,
		const std::vector<ull>& delTab) const;
	const double & FNR(const std::vector<ull>& testTab) const;

	const double & FNR(const std::vector<ull>& testTab, ull maxTest) const;

	void clear();
	void printTab() const;

	CountBloom& operator=(const CountBloom& cb);
	~CountBloom() { delete[] table; delete[]hashFac; }
};
#endif // !_COUNTING_BLOOM_

