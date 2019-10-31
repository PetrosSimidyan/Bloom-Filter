#pragma once
#include "DietzHash.h"
#include <thread>
#ifndef _PAR_BLOOM_
#define _PAR_BLOOM_

class ParBloom
{
private:
	ull hashTabLen;
	short numOfHash;
	bool **hashTable;
	ull seedVal = primitivPRBG<ull>(64);

	const ull ithHash(ull val, short i) const
	{
		return (((val >> 32) + i * (val & 0xFFFFFFFF)) % hashTabLen);
	}
public:
	ParBloom() = delete;
	ParBloom(const ParBloom& bf);
	ParBloom(const std::vector<ull>& inputTab, ull len, short k = 4, short m = 8);

	const bool insert(ull key);
	const bool lookUp(ull key) ;

	void clear(short row);

	void printTab() const;
	ParBloom& operator=(const ParBloom& bf);
};
#endif // !_PAR_BLOOM_
