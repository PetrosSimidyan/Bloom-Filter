#pragma once
#ifndef _BLOOM_FILTER_
#define _BLOOM_FILTER_

#include "DietzHash.h"
#include <cmath>

class BloomFilter
{
private:
	ull hashTabLen;
	short numOfHash;
	bool *hashTable;
	ull * facVec;
public:

	BloomFilter() = delete;
	BloomFilter(std::vector<ull> inputTab, ull len, short k = 4, short m = 8);
	BloomFilter(std::vector<ull> inputTab, ull len, double err);
	BloomFilter(const BloomFilter& bf);

	~BloomFilter() { delete[]hashTable; delete[]facVec; }
	const bool insert(ull key, short hashKey);
	const bool insert(ull key);
	const bool lookUp(ull key) const;
	BloomFilter& operator=(const BloomFilter& bf);
	/*void printTab() const
	{	printVec<bool>(hashTable, hashTabLen);}*/
};

#endif // !_BLOOM_FILTER_