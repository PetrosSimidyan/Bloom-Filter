#pragma once
#ifndef _DIETZ_HASH_
#define _DIETZ_HASH_

#include <iostream>
#include <ctime>
#include <random>
#include <vector>
#include <algorithm>
#include <functional>
#include <thread>



typedef unsigned long long ull;
typedef unsigned char uchar;
typedef unsigned short ushort;
typedef unsigned int uint;

const short w = 22;
const short q = 18;
const short maxBit = 64;
const short maxHash = 5;
static const short num_threads = 4;


inline const ull maxPowOfTwo(ull input)
{
	ull temp = (ull)1;
	for (short i = 63; i > 0; i--)
		if ((temp << (i - 1)) <= input)
			return (temp << i);
}

inline const bool primitiveLookUp(ull* input, ull key, ull len)
{
	for (ull i = 0; i < len; i++)
		if (input[i] == key)
			return true;
	return false;
}

//creating pseudo random value 
//of length bits-shiftFac
template <class T>
inline const T primitivPRBG(short bits)
{
	T output = (T)rand();
	short shiftFac = 16;
	for (short i = 0; (i - 1)*shiftFac < bits; i++)
	{
		output <<= shiftFac;
		output ^= rand();
	}
	return (T)output;
}

template <class T>
inline const double & countErrRate(const T& bf, std::vector<ull> input, ull maxTest)
{
	std::mt19937 randVal(time(NULL));
	double err = 0.0;
	ull testVal;
	for (ull i = 0; i < maxTest; i++)
	{
		testVal = randVal();
		if (bf.lookUp(testVal)
			&& !std::binary_search(input.begin(), input.end(), testVal))
			err++;
	}
	return err / (double)maxTest;
}

template <class T>
inline const double & countNegErrRate(const T& bf, std::vector<ull> input, ull maxTest)
{
	std::mt19937 randVal(time(NULL));
	double err = 0.0;
	ull testVal;
	for (ull i = 0; i < maxTest; i++)
	{
		testVal = randVal();
		if (!bf.lookUp(testVal)
			&& std::binary_search(input.begin(), input.end(), testVal))
			err++;
	}
	return err / (double)maxTest;
}

template<class T> 
inline const short & shiftBit(const T val)
{
	short count = 0;
	for (short i = 1; i < maxBit; i++)
	{
		//carefull!
		if ((val >> i) == 0)
			break;
		++count;
	}
	return count;
}

const ull murMurHash(ull key, ull seed, ull max = 0xFFFFFFFFFFFFFFFF);

inline void aVec(ull * a, short max)
{
	std::mt19937_64 randVal(time(NULL));

	for (short i = 0; i < max; i++)
		a[i] = (ull)randVal();
}

//primitiv 
inline const ull hashVal(ull key, ull a, short max=w, short min=q)
{
	ull output = a * key;
	//counting (a*key%2^w)
	ull shiftFac = (ull)(maxBit - max);
	output <<= (ull)(shiftFac);
	output >>= (ull)(shiftFac);
	//output = output/2^(w-q)
	return output >> (ull)(max - min);
}



inline const ull murMurHash(ull key, ull seed, ull max)
{
	//mask make everything shity
	//ull mask = 0x00000000FFFFFFFF;
	ull h = seed, k;
	for(int i=0;i<2;i++)
	{
		k = (key >> i * 32);
		k *= 0xcc9e2d51;
		k = ((k << 15) | (k >> 17))/*&mask*/;
		k *= 0x1b873593;
		h ^= k;
		h = ((h << 13) | (h >> 19))/*&mask*/;
		h = h * 5 + 0xe6546b64;
	} 
	h ^= h >> 16;
	h *= 0x85ebca6b;
	h ^= h >> 13;
	h *= 0xc2b2ae35;
	h ^= h >> 16;
	if (h >= max)
		h = h%max;
		
	return h;
}


template <class T>
inline void printVec(const T * vec, ull len)
{
	for (ull i = 0; i < len; i++)
		std::cout << i + 1 << ": " << vec[i] << std::endl;
}


inline void assignVecPart(std::vector<ull> &vec, ull min, ull max)
{
	std::mt19937_64 randVal(primitivPRBG<ull>(64)*min);
	for (size_t i = min; i < max; i++)
		vec[i] = randVal();
}

inline void assignVec(std::vector<ull> &vec)
{
	ull len = (ull)vec.size();
	std::thread t[num_threads];
	for (short j = 0; j < num_threads; j++)
		t[j] = std::thread(assignVecPart, std::ref(vec),
			len / num_threads * j, len / num_threads * (j + 1));
	for (short j = 0; j < num_threads; j++)
		t[j].join();
}

#endif // !_DIETZ_HASH_

