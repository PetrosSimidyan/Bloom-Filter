
#include "BFilter.h"

BFilter::BFilter(const std::vector<ull>& inputTab, ull len, short k, short m) :
	numOfHash(k),
	hashTabLen((m*len >> 6) + 1)
{
	hashTable = new ull[hashTabLen];
	for (ull i = 0; i < hashTabLen; i++)
		hashTable[i] = 0;
	ull i = 0;
	while (insert(inputTab[i++]) && i < len);
	std::thread t[num_threads];
	for (short j = 0; j < num_threads; j++)
		t[j] = std::thread(&BFilter::insertPart, this,
			inputTab, len / num_threads * j, len / num_threads * (j + 1));
	for (short j = 0; j < num_threads; j++)
		t[j].join();

}

BFilter::BFilter(const BFilter & bf)
{
	hashTabLen = bf.hashTabLen;
	numOfHash = bf.numOfHash;
	hashTable = new ull[hashTabLen];
	for (ull i = 0; i < hashTabLen; i++)
		hashTable[i] = bf.hashTable[i];
}

const bool BFilter::insert(ull key)
{
	
	ull hVal = murMurHash(key, seedVal);
	for (short i = 0; i < numOfHash; i++)
		setBit(ithHash(hVal,i));
	return true;
}

const bool BFilter::lookUp(ull key) const
{

	ull hVal = murMurHash(key, seedVal);
	for (short i = 0; i < numOfHash; i++)
		if (!isSet(ithHash(hVal,i)))
			return false;
	return true;
}

BFilter & BFilter::operator=(const BFilter & bf)
{
	delete[]hashTable;
	hashTabLen = bf.hashTabLen;
	numOfHash = bf.numOfHash;
	hashTable = new ull[hashTabLen];
	for (ull i = 0; i < hashTabLen; i++)
		hashTable[i] = bf.hashTable[i];
	return *this;
}

