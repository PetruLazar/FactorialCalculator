#include <iostream>
#include <fstream>
#include <chrono>
#include <list>
#include <string>

using namespace std;

typedef unsigned long long ull;
typedef unsigned int uint;

class BigNumber
{
	//keep 9 digits per value
	static constexpr ull digitsPerVal = 9;
	static constexpr ull decimalMask = 1000000000;
	//typedef 

	ull capacity,
		size,
		start = 0;
	uint* values;

public:

	BigNumber(ull digitCount) : size(1)
	{
		if (digitCount == 0)
			digitCount = 1;
		//calculate how many entries are needed and allocate the space
		capacity = (digitCount - 1) / digitsPerVal + 1;
		values = new uint[capacity];
		//init the number's value to 1
		values[0] = 1;
	}
	~BigNumber()
	{
		delete[] values;
	}
	inline void operator*=(ull val)
	{
		//skipping end zeros - only faster for longer operations
		ull carry = 0;
		for (ull i = start; i < size; i++)
		{
			ull result = val * values[i] + carry;
			values[i] = result % decimalMask;
			carry = result / decimalMask;
		}
		while (carry)
		{
			values[size++] = carry % decimalMask;
			carry /= decimalMask;
		}
		while (!values[start])
			start++;
	}
	void output(ostream& os)
	{
		ull pos = size;
		os << values[--pos];
		char oldFill = os.fill('0');
		for (pos--; pos != (ull)-1; pos--)
		{
			os.width(9);
			os << values[pos];
		}
		os.fill(oldFill);
	}
};
inline ostream& operator<<(ostream& os, BigNumber& nr)
{
	nr.output(os);
	return os;
}

void factorial(ull nr)
{
	// compute factorial in C++

	// determine number of digits of factorial
	double sum = 0;
	for (ull i = nr; i > 1; i--) sum += log10(i);
	ull digitCount = (ull)ceil(sum);
	cout << digitCount << " digits\n";

	//prepare file for writing
	ofstream out(to_string(nr) + "!.txt");

	// start timer
	auto start = chrono::high_resolution_clock::now();
	// compute
	BigNumber result(digitCount);
	ull buffer = 1;
	for (; nr > 0; nr--)
	{
		// try putting the factor in the buffer
		if (buffer * nr <= 0xffffffff)
		{
			buffer *= nr;
		}
		// otherwise apply the buffer
		else
		{
			result *= buffer;
			buffer = nr;
		}
	}
	result *= buffer;
	// stop timer
	auto end = chrono::high_resolution_clock::now();
	auto duration = chrono::duration_cast<chrono::milliseconds>(end - start);
	float secs = duration.count() / 1000.f;
	cout << "Computation lasted " << secs << " seconds for C++\n";

	// output to file
	out << "Computed " << digitCount << " in " << secs << " seconds:\n";
	out << result;
	out.close();
}

int main()
{
	ull number;
	cout << "n = ";
	cin >> number;

	factorial(number);

	system("pause");
	return 0;
}