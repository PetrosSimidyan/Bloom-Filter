
#include "CuckooFilter.h"


Num & Num::operator=(ushort input)
{
	for (short i = 0; i < numLen; i++)
		num[i] = (input >> i) & 1;
	return *this;
}

const bool Num::operator==(ushort input) const
{
	for (short i = 0; i < numLen; i++)
		if (num[i] != ((input >> i) & 1))
			return false;
	return true;
}

const ushort Num::value() const
{
	ushort temp = 0;
	for (short i = 0; i < numLen; i++)
		if (num[i])
			temp += pow(2, i);
	return (ushort)temp;
}

void Num::print() const
{
	if (!this->value())
		std::cout << "----";
	else
		std::cout << (unsigned)(this->value());
	std::cout << std::endl;
}

void Num::setEmpty()
{
	for (short i = 0; i < numLen; i++)
		num[i] = 0;
}


const bool Bucket::insert(ushort fp)
{
	short ind = isEmpty();
	if (ind == -1)
		return false;
	b[ind] = fp;
	return true;
}

const bool Bucket::erase(ushort fp)
{
	short ind = lookUp(fp);
	if (ind == -1)
		return false;
	b[ind].setEmpty();
	return true;
}

const short Bucket::lookUp(ushort fp)
{
	for (short i = 0; i < buckSize; i++)
		if (b[i] == fp)
			return i;
	return -1;
}

const short Bucket::isEmpty() const
{
	for (short i = 0; i < buckSize; i++)
		if (b[i].isEmpty())
			return i;
	return -1;
}


const ushort Bucket::swap(ushort fp)
{
	short ind = rand() % buckSize;
	ushort temp = b[ind].value();
	b[ind] = fp;
	return (ushort)temp;
}

void Bucket::clear()
{
	for (short i = 0; i < buckSize; i++)
		if (!b[i].isEmpty())
			b[i].setEmpty();
}

void Bucket::printBucket() const
{
	for (short i = 0; i < buckSize; i++)
	{
		std::cout << i + 1 << ": ";
		b[i].print();
	}
}

const bool CuckFilter::erase(ull key)
{
	ushort fp = fingerPrint(key);
	ull i = hash(key);
	ull j = i ^ hash(fp);
	if (bucket[i].erase(fp) ||
		bucket[j].erase(fp))
		return true;
	return false;
}

const bool CuckFilter::insert(ull key)
{
	ushort fp = fingerPrint(key);
	ull i = hash(key);
	ull j = i ^ hash(fp);
	if (bucket[i].insert(fp) ||
		bucket[j].insert(fp))
		return true;
	i = ((rand() % 2) ? i : j);
	for (short x = 0; x < maxKicks; x++)
	{
		fp = bucket[i].swap(fp);
		i = i ^ murMurHash(fp, aFac, tabLen);
		if (bucket[i].insert(fp))
			return true;
	}
	return false;
}

const bool CuckFilter::lookUp(ull key)
{
	ushort fp = fingerPrint(key);
	ull i = hash(key);
	ull j = i ^ hash(fp);
	if (bucket[i].lookUp(fp) != -1 ||
		bucket[j].lookUp(fp) != -1)
		return true;
	return false;
}

void CuckFilter::clear()
{
	for (ull i = 0; i < tabLen; i++)
		bucket[i].clear();
}

void CuckFilter::print() const
{
	for (ull i = 0; i < tabLen; i++)
	{
		std::cout << i + 1 << ": Bucket" << std::endl;
		bucket[i].printBucket();
	}
}
