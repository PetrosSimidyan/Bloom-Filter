#pragma once
#ifndef _BFILTER_
#define _BFILTER_


#include "DietzHash.h"

static const ull seedVal = 13634516963058010950;

class BFilter
{
private:
	ull hashTabLen;
	short numOfHash;
	ull *hashTable;
	const ull ithHash(ull val, short i) const 
	{
		return ((val >> 32) + i * (val & 0xFFFFFFFF))%(hashTabLen*64);
	}

	void setBit(const ull ind)
	{
		hashTable[(ind>>6)] |= ((ull)1 << 63 - (ind & 0x3f));
	}

	const bool isSet(ull ind) const
	{
		return (hashTable[ind >> 6] >>(63 - (ind & 0x3f)) & 1);
	}

	void insertPart(std::vector<ull> input, ull min, ull max)
	{
		for (ull i = min; i < max; i++)
			insert(input[i]);
	}
public:
	BFilter() = delete;
	BFilter(const std::vector<ull>& inputTab, ull len, short k = 4, short m = 8);
	BFilter(const BFilter& bf);

	~BFilter() { delete[]hashTable; }
	const bool insert(ull key);
	const bool lookUp(ull key) const;
	BFilter& operator=(const BFilter& bf);

};

#endif // !_BFILTER_
