#include "BloomFilter.h"

BloomFilter::BloomFilter(std::vector<ull> inputTab, ull len, short k, short m) :
	numOfHash(k),
	hashTabLen(m*len)
{
	hashTable = new bool[hashTabLen];
	for (ull i = 0; i < hashTabLen; i++)
		hashTable[i] = 0;
	facVec = new ull[numOfHash];
	aVec(facVec, numOfHash);
	ull i = 0;
	while (insert(inputTab[i++]) && i < len);
}

BloomFilter::BloomFilter(std::vector<ull> inputTab, ull len, double err) :
	hashTabLen(1.44*len*log2(1.0 / err)),
	numOfHash(1.44*log2(1.0 / err)*0.6931)
{
	hashTable = new bool[hashTabLen];
	for (ull i = 0; i < hashTabLen; i++)
		hashTable[i] = 0;
	facVec = new ull[numOfHash];
	aVec(facVec, numOfHash);
	ull i = 0;
	while (insert(inputTab[i++]) && i < len);
}

BloomFilter::BloomFilter(const BloomFilter & bf)
{
	hashTabLen = bf.hashTabLen;
	numOfHash = bf.numOfHash;
	hashTable = new bool[hashTabLen];
	facVec = new ull[numOfHash];
	for (ull i = 0; i < hashTabLen; i++)
		hashTable[i] = bf.hashTable[i];
	for (short j = 0; j < numOfHash; j++)
		facVec[j] = bf.facVec[j];
}

//have to work on it, if I want to use multithreading
const bool BloomFilter::insert(ull key, short hashKey)
{
	hashTable[murMurHash(key, facVec[hashKey], hashTabLen)] = 1;
	return true;
}
const bool BloomFilter::insert(ull key)
{
	ull tempKey;
	for (short i = 0; i < numOfHash; i++)
	{
		tempKey = murMurHash(key, facVec[i], hashTabLen);
		hashTable[tempKey] = 1;
	}
	return true;
}
const bool BloomFilter::lookUp(ull key) const
{
	ull index;
	for (short j = 0; j < numOfHash; j++)
	{
		index = murMurHash(key, facVec[j], hashTabLen);
		if (!hashTable[index])
			return false;
	}
	return true;
}

BloomFilter & BloomFilter::operator=(const BloomFilter & bf)
{
	delete[]hashTable; delete[]facVec;
	hashTabLen = bf.hashTabLen;
	numOfHash = bf.numOfHash;
	hashTable = new bool[hashTabLen];
	facVec = new ull[numOfHash];
	for (ull i = 0; i < hashTabLen; i++)
		hashTable[i] = bf.hashTable[i];
	for (short j = 0; j < numOfHash; j++)
		facVec[j] = bf.facVec[j];
	return *this;
}
