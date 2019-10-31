#include "ParBloom.h"

ParBloom::ParBloom(const ParBloom & bf)
{
	numOfHash = bf.numOfHash;
	hashTabLen = bf.hashTabLen;
	hashTable = new bool*[numOfHash];
	for (short i = 0; i < numOfHash; i++)
		hashTable[i] = new bool[hashTabLen];
	for (short j = 0; j < numOfHash; j++)
	for (ull i = 0; i < hashTabLen; i++)
		hashTable[j][i] = bf.hashTable[j][i];
}


ParBloom::ParBloom(const std::vector<ull>&
	inputTab, ull len, short k, short m):
numOfHash(k),
hashTabLen(m*len/k)
{
	hashTable = new bool*[numOfHash];
	for (short i = 0; i < numOfHash; i++)
	{
		hashTable[i] = new bool[hashTabLen];
		clear(i);
	}
	ull i = 0;
	while (insert(inputTab[i++]) && i < len);
}


const bool ParBloom::insert(ull key)
{
	ull ind = murMurHash(key, seedVal);
	for (short i = 0; i < numOfHash; i++)
		hashTable[i][ithHash(ind, i)] = 1;
	return true;
}


const bool ParBloom::lookUp(ull key) 
{
	ull ind = murMurHash(key, seedVal);
	for (short i = 0; i < numOfHash; i++)
		if (!(hashTable[i][ithHash(ind, i)]))
			return false;
	return true;
}

void ParBloom::clear(short row)
{
	for (ull j = 0; j < hashTabLen; j++)
		hashTable[row][j] = 0;
}

void ParBloom::printTab() const
{
	for (int i = 0; i < numOfHash; i++)
	{
		std::cout << i + 1 << ". table: " << std::endl;
		for (int j = 0; j < hashTabLen; j++)
			std::cout << j + 1 << ": " << hashTable[i][j] << std::endl;
	}
}

ParBloom & ParBloom::operator=(const ParBloom & bf)
{
	if (this != &bf)
	{
		delete[] hashTable;
		numOfHash = bf.numOfHash;
		hashTabLen = bf.hashTabLen;
		hashTable = new bool*[numOfHash];
		for (short i = 0; i < numOfHash; i++)
			hashTable[i] = new bool[hashTabLen];
		for (short j = 0; j < numOfHash; j++)
			for (ull i = 0; i < hashTabLen; i++)
				hashTable[j][i] = bf.hashTable[j][i];
	}
	return *this;
}
	
