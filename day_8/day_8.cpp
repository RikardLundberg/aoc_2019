#include <iostream>
#include <vector>
#include <string>
#include <fstream>

void part1(const std::vector<int> data);
void part2(const std::vector<int> data);

int main()
{
	std::string input;
	std::ifstream in("input.txt");
	if (in.is_open()) {
		std::getline(in, input);
	}
	else {
		std::cout << "error"; 
		return 0;
	}

	std::vector<int> data;

	while (input.size() > 0) {
		data.push_back(std::stoi(input.substr(0, 1)));
		input = input.substr(1, input.length());
	}

	part2(data);
}


void part2(const std::vector<int> data)
{
	const int width = 25, height = 6, layerSize = width * height;
	char img[layerSize];
	for (int i = 0; i < layerSize; i++)
		img[i] = 0;


	for (int i = 0; i < data.size(); i++)
	{
		int space = i % layerSize;

		if (img[space] == 'X' || img[space] == '.')
			continue;
		switch (data[i])
		{
		case 0:
			img[space] = 'X'; //'black'
			break;
		case 1:
			img[space] = '.'; //'white'
			break;
		default:
			break;
		}
	}

	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++) {
			int space = (width * i) + j;
			std::cout << img[space];
		}
		std::cout << std::endl;
	}
	std::cout << "done";
}


void part1(const std::vector<int> data)
{

	int current[3]{ 2147483647,0,0 }, record[3]{ 2147483647,0,0 }; //0=0, 1=1, 2=2

	std::vector<int> layerCount;

	bool newLayer = false;
	int layerSize = 25 * 6;
	for (int i = 0; i < data.size(); i++)
	{
		if (i % layerSize == 0)
			newLayer = true;
		if (newLayer) {
			layerCount.push_back(current[0]);
			if (record[0] > current[0]) {
				record[0] = current[0];
				record[1] = current[1];
				record[2] = current[2];
			}
			current[0] = current[1] = current[2] = 0;
			newLayer = false;
		}
		switch (data[i]) {
		case 0:
			current[0]++;
			break;
		case 1:
			current[1]++;
			break;
		case 2:
			current[2]++;
		}

	}
	std::cout << record[1] * record[2];
}
