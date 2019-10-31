//uncomment the header for needed data structure and 
// block of code of the needed test  and run the code
//do not run more than one test at the same time!


//#include "IBF.h"
//#include "CountOctBloom.h"
//#include "ParBloom.h"
//#include "CuckooFilter.h"
#include <iomanip>
#include "BFilter.h"

using namespace std;

const ull maxTestTabLen = 100000;
const ull maxKeyTest = 100000;
const ull maxLoop = 1;


int main()
{
	srand(time(NULL));
	std::mt19937_64 randVal(time(NULL));
	//////////////////////////
	//tests for IBF (Tests 1-2 
	//from Eppstein, Goodrich)
	//////////////////////////
	//ull tempVal = randVal(), delta = 5;
	//std::vector<ull> mainTab(maxTestTabLen), diffTab, testTab;
	//assignVec(mainTab);
	//uchar hash_count = 4;
	//const ull littleMax = 50;
	//cout << "Initialising the first IBF" << endl;
	//IBF b1(mainTab, littleMax, hash_count);
	//cout << "Initialising the second IBF" << endl;
	//IBF b2(mainTab, littleMax, hash_count); double succRate;
	//cout << "(DELTA, SR*)" <<endl;
	//for (; hash_count < 5; hash_count++)
	//{
	//	cout << "Tests for k = " << (unsigned)hash_count << endl;
	//	for (delta = 5; delta <= littleMax; delta += 5)
	//	{
	//		succRate = 0.0;
	//		for (short i = 0; i < maxLoop; i++)
	//		{
	//			diffTab.clear(); testTab.clear();
	//			tempVal = randVal() % maxTestTabLen;
	//			diffTab.resize(maxTestTabLen - delta);
	//			for (ull i = 0; i < maxTestTabLen - delta; i++)
	//				diffTab[i] = mainTab[(i + tempVal) % maxTestTabLen];
	//			b2 = IBF(diffTab, littleMax, hash_count);
	//			b1 -= b2;
	//			//cout << b1;
	//			//std::sort(testTab.begin(), testTab.end());
	//			succRate += b1.decode(testTab); 
	//			b1 = IBF(mainTab, littleMax, hash_count);
	//		}
	//		cout << "(" << delta << "," << succRate / maxLoop * 100.0 << ")" << endl;
	//	}
	//}
	//////////////////////////
	//tests for IBF (Tests 3
	//from Eppstein, Goodrich)
	//////////////////////////
	/*ull tempVal = randVal(), delta = 10;
	std::vector<ull> mainTab(maxTestTabLen), diffTab, testTab;
	assignVec(mainTab);
	uchar hash_count = 3;
	const ull littleMax = 50;
	IBF b1, b2;
	double succRate;
	double load_fac;
	cout << "(d, m/d)" << endl;
	for (hash_count = 3; hash_count < 4; hash_count++)
	{
		cout << "Tests for k = " << (unsigned)hash_count << endl;
		for (delta = 54; delta <98; delta += 22.5)
		{
			load_fac = 1.65;
			do
			{
				succRate = 0.0;
				load_fac += 0.05;
				for (short i = 0; i < maxLoop; i++)
				{
					diffTab.clear(); testTab.clear();
					tempVal = randVal() % maxTestTabLen;
					diffTab.resize(maxTestTabLen - delta);
					for (ull i = 0; i < maxTestTabLen - delta; i++)
						diffTab[i] = mainTab[(i + tempVal) % maxTestTabLen];
					b1 = IBF(mainTab, delta, hash_count, load_fac);
					b2 = IBF(diffTab, delta, hash_count, load_fac);
					b1 -= b2;
					succRate += b1.decode(testTab);
				}
				succRate = succRate / maxLoop * 100.0;
				cout << "(" << delta << "," << load_fac
					<< ", "<< succRate  << ")" << endl;
			} while (succRate < 99.0);
			cout << "(" << delta << "," << load_fac << ")" << endl;
		}
	}*/
	////////////////////////////
	//// Two tests with Cuckoo-Filter
	////////////////////////////
	////this part is necessary for both tests
	////do not run both test together!
	////maxTestTabLen should be pow(2,i)-1
	//cout << "Begin of initialising the filter!" << endl;
	//CuckFilter bf( maxTestTabLen);
	//double err = 0.0;
	//ull vecLen = (maxTestTabLen +1)* buckSize;
	//ull testVal=randVal(), tempErr=0;
	//std::vector<ull> testTab(vecLen);
	////////////////////////////
	//////tests for loadfactor of Cuckoo-Filter
	////////////////////////////
	/*for (int j = 0; j < maxLoop; j++)
	{
		tempErr = 0;
		while (bf.insert(testVal) && tempErr < vecLen)
		{
			tempErr++;
			testVal = randVal();
		}
		bf.clear();
		err += (double)tempErr;
		cout <<j+1<<": "<< tempErr << endl;
	}
	std::cout << "(" << buckSize << ", " << err / maxLoop / vecLen* 100.0 << ")" << endl;*/
	////////////////////////////
	//////tests for FPR of Cuckoo-Filter
	////////////////////////////
	//while ((tempErr < vecLen*loadFac)&&bf.insert(testVal))
	//{
	//	testTab[tempErr++] = testVal;
	//	testVal = randVal();
	//}
	//cout <<(double) tempErr / vecLen<<endl;
	//std::sort(testTab.begin(), testTab.end());
	//cout << "Begin of the testing!" << endl;

	//for (ull j = 0; j < maxLoop; j++)
	//{
	//	tempErr = 0;
	//	for (ull i = 0; i < maxKeyTest; i++)
	//	{
	//		testVal = randVal();
	//		if (bf.lookUp(testVal) && !std::binary_search(testTab.begin(), testTab.end(), testVal))
	//			tempErr++;
	//	}
	//	err += (double)tempErr / (double)maxKeyTest;
	//}
	//err /= (double)maxLoop;
	//cout << "FPR (%): " << endl;
	//cout << "(" << numLen << ", "
	//	<< err * 100.0 << ")" << endl;
	//cout << "Error to expected FPR: " << endl;
	//cout << "(" << numLen << ", "
	//	<< err - (2.0*buckSize/pow(2,numLen)) << ")" << endl;

		////////////////////////////
		////tests with PBF
		////////////////////////////
	//	std::vector<ull> testTab(maxTestTabLen);
	//	assignVec(testTab);
	//	cout << "Begin of initialising the Bloom filter!" << endl;
	//	ParBloom bf(testTab, maxTestTabLen, 5, 8);
	//	cout << "Sorting the vector!" << endl;
	//	std::sort(testTab.begin(), testTab.end());
	//	cout << "Begin the testing of the Bloom filter!" << endl;
	//	double err = 0.0; ull tempErr = 0, tempVal;
	//	for(short m=8;m<9;m+=2)
	//for (short k = 3; k < 4; k++)
	//{
	//	bf = ParBloom(testTab, maxTestTabLen, k, m);

	//	for (ull j = 0; j < maxLoop; j++)
	//	{
	//		tempErr = 0;
	//		for (ull i = 0; i < maxKeyTest; i++)
	//		{
	//			tempVal = randVal();
	//			if (bf.lookUp(tempVal) && !std::binary_search(testTab.begin(), testTab.end(), tempVal))
	//				tempErr++;
	//		}
	//		err += (double)tempErr / (double)maxKeyTest;
	//		/*std::cout << err << std::endl;
	//		std::cout << tempErr << std::endl;*/
	//	}
	//	err /= (double)maxLoop;
	//	std::cout << "FPR for m/n = " << m << " and k = " << k << ": " << 100.0*err << "%" << std::endl;
	//	std::cout << "Deviation: " << endl;
	//	cout << "(k = " << k << ":" << err - pow(1 - exp(-(k / (double)m)), k) << ")" << endl;
	//	err = 0;
	//}

		////////////////////////////
		////tests with BF
		////////////////////////////
	std::vector<ull> testTab(maxTestTabLen);
	assignVec(testTab);
	cout << "Begin of initialising the Bloom filter!" << endl;
	BFilter bf(testTab, maxTestTabLen, 5, 8);
	cout << "Sorting the vector!" << endl;
	std::sort(testTab.begin(), testTab.end());
	cout << "Begin the testing of the Bloom filter!" << endl;
	double err = 0.0; ull tempErr = 0, tempVal;
	for (short m = 8; m < 9; m += 2)
		for (short k = 3; k < 8; k++)
		{
			bf = BFilter(testTab, maxTestTabLen, k, m);

			for (ull j = 0; j < maxLoop; j++)
			{
				tempErr = 0;
				for (ull i = 0; i < maxKeyTest; i++)
				{
					tempVal = randVal();
					if (bf.lookUp(tempVal) && !std::binary_search(testTab.begin(), testTab.end(), tempVal))
						tempErr++;
				}
				err += (double)tempErr / (double)maxKeyTest;
			}
			err /= (double)maxLoop;
			std::cout << "FPR for m/n = " << m << " and k = " << k << ": " << 100.0*err << "%" << std::endl;
			std::cout << "Deviation: " << endl;
			cout << "(k = " << k << ":" << err - pow(1 - exp(-(k / (double)m)), k) << ")" << endl;
			err = 0;
		}


	//////////////////////////
	//tests for overflow of CountBF
	//////////////////////////
	//CountOctBloom cb(maxTestTabLen, 5, 8);
	//	std::vector<ull> testTab;
	//	double err = 0.0; ull tempErr =0;
	//	ull tempVal;
	//	tempErr = 0;
	//	cout << "(LoadFac., FPR%)" << endl;
	//	while (tempErr < 3 * maxTestTabLen+1)
	//	{
	//		tempVal = randVal();
	//		cb.insertEntry(tempVal);
	//		/*if (!cb.isThere)
	//		{*/
	//			testTab.push_back(tempVal);
	//			if (++tempErr >= maxTestTabLen && (tempErr % (maxTestTabLen/5) == 0))
	//			{
	//				std::sort(testTab.begin(), testTab.end());
	//				err = countErrRate<CountOctBloom>(cb, testTab, maxKeyTest);
	//				cout << "("
	//					<<(double) tempErr / maxTestTabLen << ": " << err*100.0<<")" << endl;
	//			}
	//		//}
	//	}

	////////////////////////////
	////tests for FNR
	////with CountBloom 
	////(deleting already inserted elements)
	////////////////////////////
	/*std::vector<ull> testTab(maxTestTabLen);
	assignVec(testTab);
	CountOctBloom cb(testTab, maxTestTabLen, 5, 8);
	ull tempErr, step = maxTestTabLen / 20, index;
	double negErr[10];
	for (ull j = 0; j < 10; j++)
		negErr[j] = 0;
	for (ull j = 0; j < maxLoop; j++)
	{
		tempErr = 0;
		while (tempErr < maxTestTabLen / 2)
		{
			index = randVal() % testTab.size();
			cb.deleteEntry(testTab[index]);
			if (cb.isThere)
			{
				testTab.erase(testTab.begin() + index);
				tempErr++;
				if (tempErr % step == 0)
				{
					negErr[tempErr / step - 1] += cb.FNR(testTab);
					cout << 5 * tempErr / step << "% : "
						<< negErr[tempErr / step - 1]*100.0 << "% FNR" << endl;

				}
			}
		}
		testTab.clear(); testTab.resize(maxTestTabLen);
		assignVec(testTab); cb=CountOctBloom(testTab, maxTestTabLen, 5, 8);
	}
	for (ull j = 0; j < 10; j++)
		cout << "For "<<5 * (j+1) << "% deletion: "
		<< negErr[j]/maxLoop * 100.0 << "% FNR" << endl;*/


		////////////////////////////
		////tests for FNR
		////with CountBloom 
		////(deleting random elements)
		////////////////////////////
		//std::vector<ull> testTab(maxTestTabLen);
		//assignVec(testTab);
		//CountBloom cb(testTab, maxTestTabLen, 5, 8);
		//std::sort(testTab.begin(), testTab.end());
		//ull counter, step = maxTestTabLen / 20, tempVal;
		//const uchar maxErrArr=10;
		//double negErr[maxErrArr], tempNegErr=0.0;
		//for (ull j = 0; j < maxErrArr; j++)
		//	negErr[j] = 0;
		//for (ull j = 0; j < maxLoop; j++)
		//{
		//	counter = 0;
		//	cout << "Results of " << (j + 1) << "-th run" << endl;
		//	while (counter < maxTestTabLen/2 + 1)
		//	{
		//		tempVal = randVal();
		//		cb.deleteEntry(tempVal);
		//		counter++;
		//		if (std::binary_search(testTab.begin(), testTab.end(), tempVal))
		//		{
		//			auto i = std::find(testTab.begin(), testTab.end(), tempVal);
		//			testTab.erase(i);
		//		}
		//		if (counter % step == 0)
		//		{
		//			tempNegErr=cb.FNR(testTab);
		//			cout << "For load factor " << counter
		//				/(double)maxTestTabLen << ": "<< tempNegErr*100 << "% FNR" << endl;
		//			negErr[counter / step - 1] += tempNegErr;
		//		}
		//	}
		//	testTab.clear(); testTab.resize(maxTestTabLen);
		//	assignVec(testTab); cb = CountBloom(testTab, maxTestTabLen, 5, 8);
		//	std::sort(testTab.begin(), testTab.end());
		//}
		//cout << "ALPHA, FNR%" << endl;
		//for (ull j = 0; j < maxErrArr; j++)
		//	cout << "("<<0.05* (j+1) << ", "
		//	<< negErr[j]/maxLoop * 100.0 << ")" << endl;

			////////////////////////////
			////simulation of real world
			//// for CountBloom 
			////////////////////////////
	//std::vector<ull> testTab(maxTestTabLen);
	//assignVec(testTab);
	//CountBloom cb(testTab, maxTestTabLen, 5, 8);
	//std::sort(testTab.begin(), testTab.end());
	//ull counter, step = maxTestTabLen / 20, tempVal;
	//const uchar maxErrArr = 10;
	//double negErr[maxErrArr], tempNegErr = 0.0;
	//double posErr[maxErrArr], tempPosErr = 0.0;
	//for (ull j = 0; j < maxErrArr; j++)
	//{
	//	negErr[j] = 0; posErr[j] = 0;
	//}
	//for (ull j = 0; j < maxLoop; j++)
	//{
	//	counter = 0;
	//	while (counter < maxTestTabLen / 2 + 1)
	//	{
	//		tempVal = randVal();
	//		counter++;
	//		if (rand() % 2)
	//		{
	//			cb.deleteEntry(tempVal);
	//			if (std::binary_search(testTab.begin(), testTab.end(), tempVal))
	//			{
	//				auto i = std::find(testTab.begin(), testTab.end(), tempVal);
	//				testTab.erase(i);
	//			}
	//		}
	//		else
	//		{
	//			cb.insertEntry(tempVal);
	//			//if(!cb.isThere)
	//			if(!std::binary_search(testTab.begin(), testTab.end(), tempVal))
	//			testTab.insert(std::upper_bound(testTab.begin(),
	//				testTab.end(), tempVal), tempVal);
	//		}
	//		if (counter % step == 0)
	//		{
	//			tempNegErr = cb.FNR(testTab);
	//			cout << "For load factor " << (double)counter
	//				/ maxTestTabLen << ": " << tempNegErr * 100 << "% FNR" << endl;
	//			negErr[counter / step - 1] += tempNegErr;
	//			tempPosErr = countErrRate<CountBloom>(cb, testTab, maxKeyTest);
	//			cout << "For load factor  "
	//				<< (double)counter / maxTestTabLen << ": "
	//				<< tempPosErr * 100.0 << "% FPR" << endl;
	//			posErr[counter / step - 1] += tempPosErr;

	//		}
	//	}
	//	testTab.clear(); testTab.resize(maxTestTabLen);
	//	assignVec(testTab); cb = CountBloom(testTab, maxTestTabLen, 5, 8);
	//	std::sort(testTab.begin(), testTab.end());
	//}
	//for (ull j = 0; j < maxErrArr; j++)
	//	cout << "For load factor " << 0.05* (j + 1) << ": "
	//	<< negErr[j] / maxLoop * 100.0 << "% FNR" << endl;
	//for (ull j = 0; j < maxErrArr; j++)
	//	cout << "For load factor " << 0.05* (j + 1) << ": "
	//	<< posErr[j] / maxLoop * 100.0 << "% FPR" << endl;

	////////////////////////////
	////simulation of realworld for 
	//// CountBloom with deleteing of 
	//// already inserted elements  
	////////////////////////////	
	/*std::vector<ull> testTab(maxTestTabLen);
	assignVec(testTab);
	CountOctBloom cb(testTab, maxTestTabLen, 5, 8);
	std::sort(testTab.begin(), testTab.end());
	ull counter, step = maxTestTabLen/5, tempVal;
	const uchar maxErrArr = 10;
	double negErr[maxErrArr], tempNegErr = 0.0;
		double posErr[maxErrArr], tempPosErr = 0.0;
		for (ull j = 0; j < maxErrArr; j++)
		{
			negErr[j] = 0; posErr[j] = 0;
		}
		for (ull j = 0; j < maxLoop; j++)
		{
			counter = 0;
			cout << "Results of " << (j + 1) << "-th run" << endl;
			while (counter < maxTestTabLen * 2 + 1)
			{
				tempVal = randVal();
				counter++;
				if (rand() % 2)
				{
					tempVal %= testTab.size();
					cb.deleteEntry(testTab[tempVal]);
					testTab.erase(testTab.begin() + tempVal);
				}
				else
				{
					while (std::binary_search(testTab.begin(), testTab.end(), tempVal))
						tempVal = randVal();
					testTab.insert(std::upper_bound(testTab.begin(),
						testTab.end(), tempVal), tempVal);
					cb.insertEntry(tempVal);
				}
				if (counter % step == 0)
				{
					tempNegErr = cb.FNR(testTab);
					cout << "For load factor " << (double)counter
						/ maxTestTabLen << ": " << tempNegErr * 100 << "% FNR" << endl;
					negErr[counter / step - 1] += tempNegErr;
					tempPosErr = countErrRate<CountOctBloom>(cb, testTab, maxKeyTest);
					cout << "For load factor  "
						<< (double)counter / maxTestTabLen << ": "
						<< tempPosErr * 100.0 << "% FPR" << endl;
					posErr[counter / step - 1] += tempPosErr;

				}
			}
			testTab.clear(); testTab.resize(maxTestTabLen);
			assignVec(testTab); cb = CountOctBloom(testTab, maxTestTabLen, 5, 8);
			std::sort(testTab.begin(), testTab.end());
		}
		cout << "ALPHA, FNR%" << endl;
		for (ull j = 0; j < maxErrArr; j++)
			cout << "(" << ((double)step/maxTestTabLen)* (j + 1) << ", "
			<< negErr[j] / maxLoop * 100.0 << ")" << endl;
		cout << "ALPHA, FPR%" << endl;
		for (ull j = 0; j < maxErrArr; j++)
			cout << "(" << ((double)step / maxTestTabLen)* (j + 1) << ", "
			<< posErr[j] / maxLoop * 100.0 << ")" << endl;*/

	return 0;
}