#include <iostream>
#include <ctime>
#include <string>
#include <cmath>

typedef unsigned long (*FindPrime)(const unsigned long &n);

// Версия Руслана

bool Simple_Cheak(const unsigned long &n)
{
	if(n == 2) return true;
	for(unsigned long i = 2; i < n; i++)
	{
		if(n % i == 0)
		{
			return false;
		}
	}
	return true;
}

unsigned long FindPrimeCount_Simple(const unsigned long &n)
{
	unsigned long Summ = 0;
	for(unsigned long i = 2; i < n; i++)
	{
		if(Simple_Cheak(i))
		{
			Summ ++;
		}
	}
	return Summ;
}



// Версия Александра Пономарева.
unsigned long FindPrimeCount_DivBy2(const unsigned long &n){
	return -1;
}

// Версия Егора.
unsigned long FindPrimeCount_Sqrt(const unsigned long &n){
	return -1;
}

// Версия Петра.
unsigned long FindPrimeCount_Eratosthenes(const unsigned long &n){
	size_t arrSize = n / 8 + (n % 8 != 0);
	unsigned char* arr = new unsigned char[arrSize];
	for (unsigned long i = 0; i<arrSize; i++) 
		arr[i] = 255;
	
	if(n%8!=0)
		arr[arrSize-1] &= (((1<<n % 8)-1) << (8- n % 8));// очень страшная побитовая херь, отсекает биты в конце
	
	// Проходим по всем числам от 2 до половины расстояния
	for (unsigned long i = 2; i<n / 2+1; i++)
	for (unsigned long j = i*2; j<n+1; j += i) // Проходим через все числа и
		arr[(j - 1) / 8] &= (j%8!=0) ? ~((1 << (8 - j % 8))):254;
		
	unsigned long summ = 0;
	for (unsigned long i = 0; i < arrSize; i++) {
		// Считаем количество бит, опять дикострашная побитовая херь
		summ += (arr[i] & 128) >> 7;
		summ += (arr[i] & 64) >> 6;
		summ += (arr[i] & 32) >> 5;
		summ += (arr[i] & 16) >> 4;
		summ += (arr[i] & 8) >> 3;
		summ += (arr[i] & 4) >> 2;
		summ += (arr[i] & 2) >> 1;
		summ +=  arr[i] & 1;
	}
	delete[] arr;
	return summ;
}

// Версия Александра Соболева.
unsigned long FindPrimeCount_Async(const unsigned long &n){
	return -1;
}

void PerfCheck(const std::string &name,FindPrime findFunc,const int &n){
	clock_t t = clock();
	int retVal = findFunc(n);
	t = clock() - t;
	std::cout << name << " Method " << 	 " returned: " << retVal <<
										"; required: " << t << " clocks and " 
<< (static_cast<double>(t))/CLOCKS_PER_SEC << " seconds." << std::endl;
}

// Entrypoint.
int main()
{
	int N = 0;
	std::cout << "Input 'N' to find prime count in range from 1 to N\n";
	std::cin >> N;
	
	if(N>0){
		PerfCheck("Simple",						FindPrimeCount_Simple,		N);
		PerfCheck("Simple optimized 'divby2'",	FindPrimeCount_DivBy2,		N);
		PerfCheck("Simple optimized 'sqrt'",	FindPrimeCount_Sqrt,		N);
		PerfCheck("Eratosthenes",				FindPrimeCount_Eratosthenes,N);
		PerfCheck("Async",						FindPrimeCount_Async,		N);
	}
	else
		std::cout << "'N' must be positive and greater than zero.\n";
	
	return 0;
}
