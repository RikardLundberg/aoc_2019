#include <iostream>
#include <vector>

int containsDouble(int i);
void getIncreasingRange(std::vector<int>& range);

int main()
{
	std::vector<int> range;
	getIncreasingRange(range);

	int count = 0;
	for (auto itr = range.begin(); itr != range.end(); itr++)
		if (containsDouble(*itr))
			count++;
	std::cout << count;
}

int containsDouble(int i) 
{
	int doubleDigitCount = 1;
	int previousDigit = -1;
	while (i > 0) {
		int newDigit = i % 10;
		if (newDigit == previousDigit) {
			doubleDigitCount++;
		}
		else {
			if (doubleDigitCount == 2)
				return 1;
			else
				doubleDigitCount = 1;
		}
		previousDigit = newDigit;
		i /= 10;
	}
	return doubleDigitCount == 2;
}

void getIncreasingRange(std::vector<int>& range) 
{
	for (int i = 128392; i < 643281; i++) {
		int n = i;
		int previousDigit = 10;
		while (n > 0) {
			int newDigit = n % 10;
			if (newDigit > previousDigit)
				break;
			previousDigit = newDigit;
			n /= 10;
		}
		if (n <= 0)
			range.push_back(i);
	}
}
