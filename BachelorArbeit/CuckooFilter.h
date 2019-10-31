#pragma once

#include "DietzHash.h"

static short const numLen = 8;
static short const buckSize = 4;
static double const loadFac = 0.95;
#ifndef _CUCKOO_FILTER_
#define _CUCKOO_FILTER_

class Num
{
	bool  num[numLen];
public:
	Num() :num() { setEmpty(); }
	Num(const Num& n) = delete;
	~Num() {  }

	void setEmpty();
	const bool isEmpty() const { return this->value() == 0; }

	Num& operator=(ushort input);
	const bool operator==(ushort input)const;

	const ushort value() const;
	void print() const;
	friend class Bucket;
	friend class CuckFilter;
};
class Bucket
{
	Num b[buckSize];
public:
	Bucket() : b() { }
	Bucket(const Bucket& n) = delete;

	~Bucket() { }

	const bool insert(ushort fp);
	const bool erase(ushort fp);

	const short lookUp(ushort fp);
	const short isEmpty() const;

	const ushort swap(ushort fp);

	void clear();
	void printBucket() const;
	friend class  CuckFilter;
};

class CuckFilter
{
	Bucket *bucket;
	ull tabLen;
	ull aFac = primitivPRBG<ull>(64);
	short maxKicks;
public:
	CuckFilter() = delete;
	CuckFilter( ull len) :
		tabLen(maxPowOfTwo(len)),
		bucket(new Bucket[maxPowOfTwo(len)]),
		maxKicks(1000.0 /buckSize*log2(len) ) {}
	CuckFilter(const std::vector<ull>& inputVec, ull len) :
		tabLen(maxPowOfTwo(len)),
		bucket(new Bucket[maxPowOfTwo(len)]),
		maxKicks(1000.0 / buckSize * log2(len))
	{
		for (ull i = 0; i < len; i++)
			insert(inputVec[i]);
	}
	~CuckFilter() { delete[] bucket; }


	const bool erase(ull key);
	const bool insert(ull key);

	const bool lookUp(ull key);

	const ull hash(ull key)
	{
		return murMurHash(key, aFac, tabLen);
	}
	const ushort fingerPrint(ull key)
	{
		return (ushort)murMurHash(key, aFac, pow(2, numLen) - 1) + 1;
	}

	void clear();

	void print() const;
};
#endif // !_CUCKOO_FILTER_


