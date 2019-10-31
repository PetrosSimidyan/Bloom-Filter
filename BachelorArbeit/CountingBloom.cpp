#include "CountingBloom.h"



CountBloom::CountBloom(ull len, short k, short m):
	hashNum(k), tabLen(m*len/2) {init();}

CountBloom::CountBloom(const std::vector<ull>& inputVec, ull len, double eps) :
	//instead of usual factor of 1.44 we use the halved factor,
	//because the table need 1 element for 2 entrys 
	tabLen(0.72*len*log2(1.0 / eps) + 1),
	hashNum(0.6931*0.72*log2(1.0 / eps))
{
	init();
	ull i = 0;
	while (insertEntry(inputVec[i++]) && i < len);
}

CountBloom::CountBloom(const std::vector<ull>& inputVec, ull len, short k, short m):
	hashNum(k), tabLen(m*len/2)
{
	init();
	ull i = 0;
	while (insertEntry(inputVec[i++]) && i < inputVec.size());
}

CountBloom::CountBloom(const CountBloom & cb)
{
	hashNum = cb.hashNum; tabLen = cb.tabLen;
	table = new uchar[tabLen];
	hashFac = new ull[hashNum];
	for (short i = 0; i < hashNum; i++)
		hashFac[i] = cb.hashFac[i];
	for (ull i = 0; i < tabLen; i++)
		table[i] = cb.table[i];
}

bool CountBloom::isOverflow(ull ind)
{
	uchar temp = ((ind & 1) ? table[ind / 2]
		: (table[ind / 2] >> 4));
	return  ((temp & 0x0F) == 0x0f);
}

bool CountBloom::isUnderflow(ull ind)
{
	uchar temp = ((ind & 1) ? table[ind / 2]
		: (table[ind / 2] >> 4));
	return  ((temp & 0x0F) == 0);
}

void CountBloom::revOp(ull key, short i, bool ins)
{
	ull ind;
	for (short j = 0; j < i; j++) {
		ind = murMurHash(key, hashFac[j], tabLen * 2);
		if (ins)
			table[ind / 2] -= (ind & 1) ? 0x01 : 0x10;
		else
			table[ind / 2] += (ind & 1) ? 0x01 : 0x10;
	}
}

const bool CountBloom::insertEntry(ull key)
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
		ind = murMurHash(key, hashFac[i], tabLen * 2);
		if (isOverflow(ind))
		{
			revOp(key, i, 1);
			return false;
		}
		table[ind / 2] += (ind & 1) ? 0x01 : 0x10;;
	}
	return true;
}

const bool  CountBloom::deleteEntry(ull key)
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
		ind = murMurHash(key, hashFac[i], tabLen*2);
		if (isUnderflow(ind))
		{
			std::cout << "Ooops" << std::endl;
			revOp(key, i, 0);
			return false;
		}
		table[ind/2] -= (ind & 1) ? 0x01 : 0x10;
	}
	return true;
}

const bool CountBloom::lookUp(ull key) const
{
	ull tempKey;
	uchar curEntry;
	for (short i = 0; i < hashNum; i++)
	{
		tempKey = murMurHash(key, hashFac[i], tabLen*2);
		curEntry = table[tempKey / 2];
		if ((tempKey & 1) && (curEntry & 0x0f) == 0
			|| !(tempKey & 1) && ((curEntry & 0xf0) >> 4) == 0)
			return false;
	}
	return true;
}

const double & CountBloom::FNR(const std::vector<ull>& testTab,
	const std::vector<ull>& delTab) const
{
	double err = 0.0; 
	for (ull i = 0; i < testTab.size(); i++)
		if (!lookUp(testTab[i]) &&
			!std::binary_search(delTab.begin(), delTab.end(), testTab[i]))
			++err;
	return err / (double)testTab.size();
}

const double & CountBloom::FNR(const std::vector<ull>& testTab) const
{
	double err = 0.0;
	for (ull i = 0; i < testTab.size(); i++)
		if (!lookUp(testTab[i]))
			++err;
	return err / (double)testTab.size();
}
const double & CountBloom::FNR(const std::vector<ull>& testTab, ull maxTest) const
{
	std::mt19937_64 randVal(time(NULL));
	ull testVal;
	double err = 0.0;
	for (ull i = 0; i < maxTest; i++)
	{
		testVal = randVal();
		if (!lookUp(testVal)&&
			std::binary_search(testTab.begin(), testTab.end(), testVal))
			++err;
	}
	return err / (double)maxTest;
}
 

void CountBloom::clear()
{
	ull i = 0;
	while (i < tabLen)
		table[i++] = 0;
}

void CountBloom::printTab() const
{
	uchar temp;
	for (int i = 0; i < tabLen; i++)
	{
		temp = table[i];
		std::cout << (temp & 0x0f) << std::endl;
		std::cout << ((temp>>4) & 0x0f) << std::endl;
	}
}

CountBloom & CountBloom::operator=(const CountBloom & cb)
{
	if (this != &cb)
	{
		delete[] table; delete[] hashFac;
		hashNum = cb.hashNum; tabLen = cb.tabLen;
		table = new uchar[tabLen];
		hashFac = new ull[hashNum];
		for (short i = 0; i < hashNum; i++)
			hashFac[i] = cb.hashFac[i];
		for (ull i = 0; i < tabLen; i++)
			table[i] = cb.table[i];
	}
	return *this;
}

void CountBloom::init()
{
	hashFac = new ull[hashNum];
	//the function initialises the vector of factors
	//to build hashNum number of hash functions
	aVec(hashFac, hashNum);
	table = new uchar[tabLen];
	//assigning the table with zeros
	clear();
}

