#include "CountOctBloom.h"


void CountOctBloom::revOp(ull key, short i, bool ins)
{
	ull ind;
	for (short j = 0; j < i; j++) {
		ind = murMurHash(key, hashFac[j], tabLen);
		if (ins)
			--table[ind];
		else
			++table[ind];
	}
}

const bool CountOctBloom::insertEntry(ull key)
{
	isThere = 0;
	if (lookUp(key))
	{
		isThere = 1;
		return true;
	}
	ull ind;
	for (short i = 0; i < hashNum; i++)
	{
		ind = murMurHash(key, hashFac[i], tabLen );
		if (isOverflow(ind))
		{
			revOp(key, i, 1);
			return false;
		}
		++table[ind];	
	}
	return true;
}

const bool CountOctBloom::deleteEntry(ull key)
{
	isThere = 1;
	if (!lookUp(key))
	{
		isThere = 0;
		return true;
	}
	ull ind;
	for (short i = 0; i < hashNum; i++)
	{
		ind = murMurHash(key, hashFac[i], tabLen);
		if (isUnderflow(ind))
		{
			std::cout << "Oops" << std::endl;
			revOp(key, i, 0);
			return false;
		}
		--table[ind];
	}
	return true;
}

const bool CountOctBloom::lookUp(ull key) const
{
	ull tempKey;
	for (short i = 0; i < hashNum; i++)
	{
		tempKey = murMurHash(key, hashFac[i], tabLen);
		if (table[tempKey] == 0)
			return false;
	}
	return true;
}

const double & CountOctBloom::FNR(const std::vector<ull>& testTab) const
{
	double err = 0.0;
	for (ull i = 0; i < testTab.size(); i++)
		if (!lookUp(testTab[i]))
			++err;
	return err / (double)testTab.size();
}

const double & CountOctBloom::FNR(const std::vector<ull>& testTab,
	const std::vector<ull>& delTab) const
{
	double err = 0.0;
	for (ull i = 0; i < testTab.size(); i++)
		if (!lookUp(testTab[i]) &&
			!std::binary_search(delTab.begin(), delTab.end(), testTab[i]))
			++err;
	return err / (double)testTab.size();
}