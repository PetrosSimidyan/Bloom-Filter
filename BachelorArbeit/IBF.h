#pragma once
#ifndef _IBF_
#define _IBF_

#include "DietzHash.h"
#include <queue>

static ull seed_vec[10] = { 7358878947471794938,
6901742714010858581,
11516813271470962004,
14218281702521213795,
3079046350847566188,
692266667422012757,
15996969593210129199,
3482462223231162458,
12573961674444138596,
17345632729303220594};
static const ull cell_seed = 10771977009191949239;

const ull& cellHash(ull key);

class Cell
{
private:
	int counter;
	ull keySum;
	ull hashSum;
public:
	Cell() :counter(0), keySum(0), hashSum(0) {}
	Cell(const Cell& c) :counter(c.counter),
		keySum(c.keySum), hashSum(c.hashSum) {}
	

	Cell& operator=(const Cell& c);
	Cell& operator+=(const Cell& src);
	Cell& operator-=(const Cell& src);

	friend std::ostream& operator<<(std::ostream& os, const Cell & c);
	friend const Cell operator+(const Cell&c1, const Cell& c2);
	friend const Cell operator-(const Cell&c1, const Cell& c2);

	const bool& insert(ull key);
	const bool& erase(ull key);

	const bool& isUnique() 
	{
		ull temp = cellHash(keySum);
		return ((counter == 1 || counter == -1) &&
			cellHash(keySum)==hashSum);
	}
	friend class IBF;
}; 

class IBF
{
private:
	ull  hashTabLen;
	short hashNum;
	Cell* hashTable;
	const ull ithHash(ull val, short i) const
	{
		return ((val >> 32) + i * (val & 0xFFFFFFFF)) % (hashTabLen);
	}
	void delAllOcc(ull key, int counter, std::queue<ull> &q );
public:
	IBF() :hashNum(0) {}
	IBF(const std::vector<ull>& input,
		ull len, short k, double loadFac);
	IBF(const std::vector<ull>& input, ull len, short k);
	IBF(const IBF& ibf);
	~IBF() { delete[] hashTable; }

	const bool& insert(ull key);
	const bool& erase(ull key);

	IBF& operator=(const IBF& ibf);
	IBF& operator-=(const IBF& ibf);
	IBF& operator+=(const IBF& ibf);
		
	const bool& decode(std::vector<ull>& plus);
	const bool & decode(std::vector<ull>& plus, std::vector<ull>& minus);


	void init(const std::vector<ull>& input)
	{
		for (ull i = 0; i < input.size(); i++)
			insert(input[i]);
	}

	friend std::ostream& operator<<(std::ostream& os, const IBF & c);
	friend const IBF operator-(const IBF& i, const IBF& j);
	friend const IBF operator+(const IBF& i, const IBF& j);
};

#endif