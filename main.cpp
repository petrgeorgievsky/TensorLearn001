#include <iostream>
#include <ctime>
#include <string>
#include <cmath>

typedef int (*FindPrime)(const int &n);

// ������ �������.
int FindPrimeCount_Simple(const int &n){
	return -1;
}

// ������ ���������� ����������.
int FindPrimeCount_DivBy2(const int &n){
	return -1;
}

// ������ �����.
int FindPrimeCount_Sqrt(const int &n){
	return -1;
}

// ������ �����.
int FindPrimeCount_Eratosthenes(const int &n){
	size_t arrSize = n / 8 + (n % 8 != 0);
	unsigned char* arr = new unsigned char[arrSize];
	for (int i = 0; i<arrSize; i++) 
		arr[i] = 255;
	
	if(n%8!=0)
		arr[arrSize-1] &= (((1<<n % 8)-1) << (8- n % 8));// ����� �������� ��������� ����, �������� ���� � �����
	
	// �������� �� ���� ������ �� 2 �� �������� ����������
	for (int i = 2; i<n / 2+1; i++)
	for (int j = i*2; j<n+1; j += i) // �������� ����� ��� ����� �
		arr[(j - 1) / 8] &= (j%8!=0) ? ~((1 << (8 - j % 8))):254;
		
	int summ = 0;
	for (int i = 0; i < arrSize; i++) {
		// ������� ���������� ���, ����� ������������ ��������� ����
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

// ������ ���������� ��������.
int FindPrimeCount_Async(const int &n){
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