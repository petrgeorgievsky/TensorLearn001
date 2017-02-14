#include <iostream>
#include <ctime>
#include <string>
#include <cmath>
#include <future>

typedef unsigned long (*FindPrime)(const unsigned long &n);

// Версия Руслана

bool Simple_Cheak(const unsigned long &n)
{
	if(n == 2)return true;
	if(n == 1)return true;
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

unsigned long finder(const unsigned long begin,unsigned long end)
{
    int count=0;
    for(int setNum=begin;setNum<end;setNum++)
    {
        bool isSimple = true;
        for(int j=2;j<=sqrt(setNum);j++)
        {
            if(setNum%j==0)
            {
                isSimple = false;
                break;
            }
        }
        if(isSimple)
            count++;
    }
    return count;
}


// Версия Александра Пономарева.
bool Medium_Cheak(const unsigned long &n)
{
	if(n >= 1 && n <= 2) return true;
	for(unsigned long i = 2; i < n/2+1; i++){
		if(n % i == 0){
			return false;
		}
	}
	return true;
}

unsigned long FindPrimeCount_DivBy2(const unsigned long &n)
{
unsigned long Summ = 0;
	for(unsigned long i = 2; i < n; i++)
	{
		if(Medium_Cheak(i))
		{
			Summ ++;
		}
	}
	return Summ;
}

// Версия Егора.
unsigned long FindPrimeCount_Sqrt(const unsigned long &n) //Единицу исключаем из простых чисел.
{
	int count = 0; //Счетчик простых чисел
	bool flag; //Флаг, показывающий текущее состояние числа "true - простое","false - не простое"
	for (int i = 2; i < n; i++)
	{
		flag = true;
		for (int j = 2; j <= sqrt(i); j++)
		{
			if ((j != i) && (i % j == 0))
			{
				flag = false;
				break;
			}
		}
		if (flag) count++;
	}
	return count;
}

// Версия Петра.
unsigned long FindPrimeCount_Eratosthenes(const unsigned long &n){
	size_t arrSize = n / 8 + (n % 8 != 0);
	unsigned char* arr = new unsigned char[arrSize];
	for (unsigned long i = 0; i<arrSize; i++) 
		arr[i] = 255;
	arr[0]=127;
	if(n%8!=0)
		arr[arrSize-1] &= (((1<<(n-1) % 8)-1) << (8- (n-1) % 8));// очень страшная побитовая херь, отсекает биты в конце
	
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
	    if(n<2) return 0;
    if(n==2) return 1;
    if(n<5) return 2;

    auto a = 2;
    auto b = n/4;
    auto c = n/2;
    auto d = b+c;

    std::future<unsigned long> fut [4]{std::async(finder,a,b),
                                      std::async(finder,b,c),
                                      std::async(finder,c,d),
                                      std::async(finder,d,n)};
    auto rez = 0;
    for(auto i= 0;i<4;i++)
        rez+=fut[i].get();

    return rez;
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
