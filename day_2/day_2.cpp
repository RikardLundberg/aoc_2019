#include <iostream>
#include <vector>
#include <fstream>

int main()
{
	std::vector<int> data{ 1,0,0,3,1,1,2,3,1,3,4,3,1,5,0,3,2,1,13,19,1,9,19,23,2,13,23,27,2,27,13,31,2,31,10,35,1,6,35,39,1,5,39,43,1,10,43,47,1,5,47,51,1,13,51,55,2,55,9,59,1,6,59,63,1,13,63,67,1,6,67,71,1,71,10,75,2,13,75,79,1,5,79,83,2,83,6,87,1,6,87,91,1,91,13,95,1,95,13,99,2,99,13,103,1,103,5,107,2,107,10,111,1,5,111,115,1,2,115,119,1,119,6,0,99,2,0,14,0 };
	auto sp = 0;
	auto exit = false;
	data[1] = 65; //12
	data[2] = 33; //2

	while (!exit) {
		switch (data[sp]) {
		case 1:
			data[data[sp + 3]] = data[data[sp + 1]] + data[data[sp + 2]];
			break;
		case 2:
			data[data[sp + 3]] = data[data[sp + 1]] * data[data[sp + 2]];
			break;
		case 99:
			exit = true;
			break;
		default:
			std::cout << "error!";
			return 0;
		}
		sp += 4;
	}
	std::cout << data[0];
}