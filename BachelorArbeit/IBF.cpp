#include "IBF.h"

Cell & Cell::operator=(const Cell & c)
{
	if (this != &c)
	{
		counter = c.counter;
		keySum = c.keySum;
		hashSum = c.hashSum;
	}
	return *this;
}

Cell & Cell::operator+=(const Cell & src)
{
	keySum ^= src.keySum;
	hashSum ^= src.hashSum;
	counter += src.counter;
	return *this;
}

Cell & Cell::operator-=(const Cell & src)
{
	keySum ^= src.keySum;
	hashSum ^= src.hashSum;
	counter -= src.counter;
	return *this;
}

const bool& Cell::insert(ull key)
{
	keySum ^= key;
	hashSum ^= cellHash(key);
	++counter;
	return true;
}

const bool & Cell::erase(ull key)
{
	keySum ^= key;
	hashSum ^= cellHash(key);
	--counter;
	return true;
}

const ull& cellHash(ull key)
{
	return murMurHash(key, cell_seed);
}

std::ostream & operator<<(std::ostream & os, const Cell & c)
{
	os << "//-----------------------//" << std::endl;
	os << "Counter: " << c.counter << std::endl;
	os << "Sum of inserted keys: " << c.keySum<< std::endl;
	os << "Sum of hash values: " << c.hashSum<< std::endl;
	return os << "//-----------------------//" << std::endl;
}

const Cell operator+(const Cell & c1, const Cell & c2)
{
	Cell temp(c1);
	temp += c2;
	return temp;
}

const Cell operator-(const Cell & c1, const Cell & c2)
{
	Cell temp(c1);
	temp -= c2;
	return temp;
}

std::ostream & operator<<(std::ostream & os, const IBF & ibf)
{
	for (ull i = 0; i < ibf.hashTabLen; i++)
		os <<i<<". Cell"<<std::endl<< ibf.hashTable[i];
	return os;
}

const IBF operator-(const IBF & i, const IBF & j)
{
	IBF temp(i);
	temp -= j;
	return temp;
}

const IBF operator+(const IBF & i, const IBF & j)
{
	IBF temp(i);
	temp += j;
	return temp;
}

void IBF::delAllOcc(ull key, int counter, std::queue<ull> &q)
{
	ull ind;
	for (short i = 0; i < hashNum; i++)
	{
		ind = murMurHash(key, seed_vec[i], hashTabLen);
		hashTable[ind].keySum ^= key;
		hashTable[ind].hashSum ^= cellHash(key);
		hashTable[ind].counter -= counter;
		if (hashTable[ind].isUnique())
			q.push(ind);
	}
}

IBF::IBF(const std::vector<ull>& input, ull len, short k, double loadFac) :
	hashTabLen(loadFac*len),
	hashNum(k),
	hashTable(new Cell[loadFac*len])
{
	init(input);
}

IBF::IBF(const std::vector<ull>& input, ull len, short k) :
	hashTabLen(len),
	hashNum(k),
	hashTable(new Cell[len])
{
	init(input);
}

IBF::IBF(const IBF & ibf) :
	hashTabLen(ibf.hashTabLen),
	hashNum(ibf.hashNum),
	hashTable(new Cell[ibf.hashTabLen])
{
	for (ull i=0; i < hashTabLen; i++)
		hashTable[i] = ibf.hashTable[i];
}

const bool & IBF::insert(ull key)
{
	for (short i = 0; i < hashNum; i++)
		hashTable[murMurHash(key,
			seed_vec[i], hashTabLen)].insert(key);
	return true;
}

const bool & IBF::erase(ull key)
{
	for (short i = 0; i < hashNum; i++)
		hashTable[murMurHash(key,
			seed_vec[i], hashTabLen)].erase(key);
	return true;
}

IBF & IBF::operator=(const IBF & ibf)
{
	if (this != &ibf)
	{
		delete[] hashTable; 
		hashTabLen = ibf.hashTabLen;
		hashNum = ibf.hashNum;
		hashTable = new Cell[ibf.hashTabLen];
		for (ull i=0; i < hashTabLen; i++)
			hashTable[i] = ibf.hashTable[i];
	}
	return *this;
}

IBF & IBF::operator-=(const IBF & ibf)
{
	if (hashTabLen == ibf.hashTabLen
		&&hashNum == ibf.hashNum)
	{
		for (ull i=0; i < hashTabLen; i++)
			hashTable[i] -= ibf.hashTable[i];
	}
	return *this;
}

IBF & IBF::operator+=(const IBF & ibf)
{
	if (hashTabLen == ibf.hashTabLen
		&&hashNum == ibf.hashNum)
	{
		for (ull i=0; i < hashTabLen; i++)
			hashTable[i] += ibf.hashTable[i];
	}
	return *this;
}

const bool & IBF::decode(std::vector<ull>& plus)
{
	std::queue<ull> temp;
	for (ull i = 0; i < hashTabLen; i++)
		if (hashTable[i].isUnique())
			temp.push(i);
	ull tempKey, ind; int tempCount;
	while (!temp.empty())
	{
		ind = temp.front();
		temp.pop();
		if (!hashTable[ind].isUnique())
			continue;
		tempKey = hashTable[ind].keySum;
		tempCount = hashTable[ind].counter;
			plus.insert(std::upper_bound(plus.begin(),
				plus.end(), tempKey), tempKey);
		delAllOcc(tempKey, tempCount, temp);
	}
	for (ull i = 0; i < hashTabLen; i++)
		if (hashTable[i].keySum != 0 ||
			hashTable[i].hashSum != 0 ||
			hashTable[i].counter != 0)
			return false;
	return true;
}

const bool & IBF::decode(std::vector<ull>& plus, std::vector<ull>& minus)
{
	std::queue<ull> temp;
	for (ull i = 0; i < hashTabLen; i++)
		if (hashTable[i].isUnique())
			temp.push(i);
	ull tempKey, ind; int tempCount;
	while (!temp.empty())
	{
		ind = temp.front();
		temp.pop();
		if (!hashTable[ind].isUnique())
			continue;
		tempKey = hashTable[ind].keySum;
		tempCount = hashTable[ind].counter;
		if (tempCount > 0)
			plus.insert(std::upper_bound(plus.begin(),
				plus.end(), tempKey), tempKey);
		else
			minus.insert(std::upper_bound(minus.begin(),
				minus.end(), tempKey), tempKey);
		delAllOcc(tempKey, tempCount,temp);
	}
	for (ull i = 0; i < hashTabLen; i++)
		if (hashTable[i].keySum != 0 ||
			hashTable[i].hashSum != 0 ||
			hashTable[i].counter != 0)
			return false;
	return true;
}
