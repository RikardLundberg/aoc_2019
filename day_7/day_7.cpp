#include <iostream>
#include <vector>
#include <fstream>

struct Thruster {
public:
	std::vector<int> data{ 3,8,1001,8,10,8,105,1,0,0,21,30,51,76,101,118,199,280,361,442,99999,3,9,102,5,9,9,4,9,99,3,9,102,4,9,9,1001,9,3,9,102,2,9,9,101,2,9,9,4,9,99,3,9,1002,9,3,9,1001,9,4,9,102,5,9,9,101,3,9,9,1002,9,3,9,4,9,99,3,9,101,5,9,9,102,4,9,9,1001,9,3,9,1002,9,2,9,101,4,9,9,4,9,99,3,9,1002,9,2,9,1001,9,3,9,102,5,9,9,4,9,99,3,9,1002,9,2,9,4,9,3,9,1002,9,2,9,4,9,3,9,1002,9,2,9,4,9,3,9,1001,9,2,9,4,9,3,9,102,2,9,9,4,9,3,9,102,2,9,9,4,9,3,9,1002,9,2,9,4,9,3,9,101,2,9,9,4,9,3,9,1002,9,2,9,4,9,3,9,1002,9,2,9,4,9,99,3,9,1001,9,1,9,4,9,3,9,1002,9,2,9,4,9,3,9,1002,9,2,9,4,9,3,9,101,2,9,9,4,9,3,9,102,2,9,9,4,9,3,9,102,2,9,9,4,9,3,9,101,1,9,9,4,9,3,9,102,2,9,9,4,9,3,9,101,1,9,9,4,9,3,9,102,2,9,9,4,9,99,3,9,1001,9,1,9,4,9,3,9,1001,9,2,9,4,9,3,9,101,1,9,9,4,9,3,9,101,1,9,9,4,9,3,9,1002,9,2,9,4,9,3,9,1001,9,2,9,4,9,3,9,101,1,9,9,4,9,3,9,1002,9,2,9,4,9,3,9,1001,9,1,9,4,9,3,9,101,1,9,9,4,9,99,3,9,1001,9,1,9,4,9,3,9,1002,9,2,9,4,9,3,9,1002,9,2,9,4,9,3,9,1002,9,2,9,4,9,3,9,101,2,9,9,4,9,3,9,1001,9,2,9,4,9,3,9,101,2,9,9,4,9,3,9,1001,9,1,9,4,9,3,9,1001,9,1,9,4,9,3,9,1002,9,2,9,4,9,99,3,9,102,2,9,9,4,9,3,9,1001,9,2,9,4,9,3,9,101,1,9,9,4,9,3,9,102,2,9,9,4,9,3,9,101,2,9,9,4,9,3,9,1001,9,1,9,4,9,3,9,101,1,9,9,4,9,3,9,101,1,9,9,4,9,3,9,1001,9,2,9,4,9,3,9,1001,9,2,9,4,9,99 };
	int saveState = 0;
	bool done = false;
	bool doneFirst = false;
};

void interpretInstruction(int data, int& opcode, int& mode1, int& mode2, int& mode3);
bool usesTwoParams(int opcode);
long runProgramOnThruster(int phaseSetting, long input, Thruster &t);
void getPermutations(std::vector<std::vector<int>> &permutations, std::vector<int> &permutation, int maxDepth, int depth);

int main()
{
	std::vector<int> phaseSettings{5,6,7,8,9};
	std::vector<std::vector<int>> permutations;
	getPermutations(permutations, phaseSettings, 4, 0);

	int max = 0;
	long input = 0;

	for (int i = 0; i < permutations.size(); i++) {
		std::vector<int> iteration;
		for (int j = 0; j < permutations[i].size(); j++)
		{
			iteration.push_back(permutations[i][j]);
		}
		Thruster t1, t2, t3, t4, t5;
		while (!t1.done || !t2.done || !t3.done || !t4.done || !t5.done)
		{
			input = runProgramOnThruster(iteration[0], input, t1);
			input = runProgramOnThruster(iteration[1], input, t2);
			input = runProgramOnThruster(iteration[2], input, t3);
			input = runProgramOnThruster(iteration[3], input, t4);
			input = runProgramOnThruster(iteration[4], input, t5);
			if (input > max)
				max = input;
		}
		
		input = 0;
	}

	std::cout << max;
}

void Swap(std::vector<int>& perm, int a, int b) {
	if (perm[a] == perm[b])
		return;

	auto temp = perm[a];
	perm[a] = perm[b];
	perm[b] = temp;
}

// kudos to https://stackoverflow.com/questions/756055/listing-all-permutations-of-a-string-integer
void getPermutations(std::vector<std::vector<int>> &permutations, std::vector<int>& perm, int maxDepth, int depth) 
{
	if (maxDepth == depth) {
		permutations.push_back(perm);
	}
	else {
		for (int i = depth; i <= maxDepth; i++) {
			Swap(perm, i, depth);
			getPermutations(permutations, perm, maxDepth, depth+1);
			Swap(perm, i, depth);
		}
	}
}


long runProgramOnThruster(int phaseSetting, long input, Thruster& t) {
	int sp = t.saveState;
	auto exit = false;
	auto sp_inc = 4;
	auto jump = false;
	long output = -1;

	while (!exit) {
		sp_inc = 4;
		jump = false;
		int opcode, mode1, mode2, mode3, t1;
		interpretInstruction(t.data[sp], opcode, mode1, mode2, mode3);
		int data1 = opcode != 99 ? (mode1 ? t.data[sp + 1] : t.data[t.data[sp + 1]]) : 0;
		int data2 = (usesTwoParams(opcode)) ? (mode2 ? t.data[sp + 2] : t.data[t.data[sp + 2]]) : 0;
		// data3 unnecessary, only writes to atm
		switch (opcode) {
		case 1:
			t1 = t.data[sp + 3];
			t.data[t.data[sp + 3]] = data1 + data2;
			break;
		case 2:
			t1 = t.data[sp + 3];
			t.data[t.data[sp + 3]] = data1 * data2;
			break;
		case 3:
			sp_inc = 2;

			int in;
			//std::cin >> in;
			if (t.doneFirst)
				in = input;
			else
			{
				t.doneFirst = true;
				in = phaseSetting;
			}
			t.data[t.data[sp + 1]] = in;
			break;
		case 4:
			sp_inc = 2;
			//std::cout << data1 << std::endl;
			output = data1;
			t.saveState = sp + 2;
			return output;
			break;
		case 5:
			if (data1) {
				jump = true;
				sp = data2;
			}
			else sp_inc = 3;
			break;
		case 6:
			if (!data1) {
				jump = true;
				sp = data2;
			}
			else sp_inc = 3;
			break;
		case 7:
			t.data[t.data[sp + 3]] = data1 < data2 ? 1 : 0;
			break;
		case 8:
			t.data[t.data[sp + 3]] = data1 == data2 ? 1 : 0;
			break;
		case 99:
			exit = true;
			break;
		default:
			std::cout << "error!";
			return 0;
		}
		if (!jump)
			sp += sp_inc;
	}
	t.done = true;
	return output;
}

void interpretInstruction(int data, int& opcode, int& mode1, int& mode2, int& mode3)
{
	opcode = data > 10 ? data % 100 : data % 10;
	data > 10 ? data /= 100 : data /= 10;
	mode1 = data > 0 ? data % 10 : 0;
	if (data > 0) data /= 10;
	mode2 = data > 0 ? data % 10 : 0;
	if (data > 0) data /= 10;
	mode3 = data > 0 ? data % 10 : 0;
	if (data > 0) data /= 10;
}

bool usesTwoParams(int opcode)
{
	switch (opcode) {
	case 1:
	case 2:
	case 5:
	case 6:
	case 7:
	case 8:
		return true;
	default:
		return false;
	}
}