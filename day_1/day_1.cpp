#include <iostream>

int main()
{
	int n;
	int sum = 0;
	while (std::cin >> n) {
		while (n > 0) {
			auto fuel = n / 3 - 2;
			if (fuel < 0)
				break;
			sum += fuel;
			n = fuel;
		}
		std::cout << sum << std::endl;
	}
}