#include <iostream>
#include <vector>
#include <string>

struct coordinates {
	std::vector<int> x;
	std::vector<int> y;
	void add(int xc, int yc) { x.push_back(xc); y.push_back(yc); }
};

void readWire(coordinates &wire);

int main()
{
	coordinates wire1, wire2;
	readWire(wire1);
	readWire(wire2);

	int intersection = 2147483647;
	int totalSteps = 2147483647;
	int w1steps = 0;
	for (int npos = 1; npos < wire1.x.size(); npos++) {
		int w2steps = 0;
		int x11 = wire1.x[npos];
		int x12 = wire1.x[npos - 1];
		int y11 = wire1.y[npos];
		int y12 = wire1.y[npos - 1];
		for (int i = 1; i < wire2.x.size(); i++)
		{
			if (wire2.x[i] == wire1.x[npos] && wire2.y[i] == wire1.y[npos])
			{
				int manDist = std::abs(wire2.x[i]) + std::abs(wire2.y[i]);
				if (manDist < intersection && manDist > 0)
					intersection = manDist;
				//meh does not seem to happen
				continue;
			}

			int x21 = wire2.x[i];
			int x22 = wire2.x[i - 1];
			int y21 = wire2.y[i];
			int y22 = wire2.y[i - 1];

			if (x22 - x21 == 0 && y12 - y11 == 0) { //wire2 y, wire1 x
				if ((x12 > x21 && x11 < x21) || x12 < x21 && x11 > x21) {
					if ((y22 > y11 && y21 < y11) || y22 < y11 && y21 > y11) {
						int manDist = std::abs(wire2.x[i]) + std::abs(wire1.y[npos]);
						if (manDist < intersection && manDist > 0)
							intersection = manDist;
						int steps = w1steps + std::abs(wire1.x[npos - 1] - wire2.x[i]) + w2steps + std::abs(wire1.y[npos] - wire2.y[i - 1]);

						if (steps < totalSteps && steps > 0)
							totalSteps = steps;
					}
				}
			}
			else if (y22 - y21 == 0 && x12 - x11 == 0) { //wire2 x, wire1 y
				if ((y12 > y21 && y11 < y21) || y12 < y21 && y11 > y21) {
					if ((x21 > x11 && x22 < x11) || x21 < x11 && x22 > x11) {
						int manDist = std::abs(wire2.y[i]) + std::abs(wire1.x[npos]);
						if (manDist < intersection && manDist > 0)
							intersection = manDist;
						int steps = w1steps + std::abs(wire1.y[npos] - wire2.y[i - 1]) + w2steps + std::abs(wire1.x[npos - 1] - wire2.x[i]);

						if (steps < totalSteps && steps > 0)
							totalSteps = steps;
					}
				}
			}
			w2steps += (x22 - x21 == 0) ? std::abs(y21 - y22) : std::abs(x21 - x22);
		}
		w1steps += (x12 - x11 == 0) ? std::abs(y11 - y12) : std::abs(x11 - x12);
	}
	std::cout << intersection << ", " << totalSteps;
}

void readWire(coordinates& wire) {
	std::string input;
	int currX = 0;
	int currY = 0;
	wire.add(currX, currY); //central port

	std::cin >> input;
	std::vector<std::string> inputs;
	while (input.find(',') != std::string::npos) {
		inputs.push_back(input.substr(0, input.find(',')));
		input.erase(0, input.find(',') + 1);
	}
	inputs.push_back(input);

	for(auto itr = inputs.begin(); itr != inputs.end(); itr++) {
		int sub = std::stoi(itr->substr(1, itr->length()));
		switch ((*itr)[0]) {
		case 'R':
			currX += sub;
			break;
		case 'U':
			currY += sub;
			break;
		case 'L':
			currX -= sub;
			break;
		case 'D':
			currY -= sub;
			break;
		}
		wire.add(currX, currY);
	}
}
