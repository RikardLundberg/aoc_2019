#include <iostream>
#include <string>
#include <vector>

struct Node {
	std::string name;
	//int totalOrbits;
	std::string parentName;
	int totalCount;
	Node(std::string _name, std::string _parentName) { name = _name; parentName = _parentName; totalCount = 0; }
};

int countParents(const Node node, const std::vector<Node> nodes);
void sanityCheck(std::vector<Node> &nodes);
void getParentsNames(const Node node, const std::vector<Node> nodes, std::vector<std::string> &parents);

int main()
{
	std::vector<Node> nodes;
	Node com("COM", "");
	nodes.push_back(com);
	int totalCount = 0;

	std::string input;
	while (std::cin >> input) {
		if (input.compare("kill") == 0)
			break;
		std::string orbits = input.substr(0,input.find(")"));
		std::string name = input.substr(input.find(")")+1, input.length());
		Node node(name, orbits);
		nodes.push_back(node);
	}

	//part1
	/*for (int i = 0; i < nodes.size(); i++) {
		Node *n = &nodes[i];
		n->totalCount = countParents(*n, nodes);
		totalCount += n->totalCount;
	}
	
	std::cout << totalCount;
	*/

	//part2
	std::vector<std::string> yourParents, santasParents;
	for (int i = 0; i < nodes.size(); i++) {
		Node* n = &nodes[i];
		if (n->name.compare("YOU") == 0)
			getParentsNames(*n, nodes, yourParents);
		if (n->name.compare("SAN") == 0)
			getParentsNames(*n, nodes, santasParents);
	}

	std::reverse(yourParents.begin(), yourParents.end());
	std::reverse(santasParents.begin(), santasParents.end());
	int sameParentCount = 0;
	size_t limit = santasParents.size() > yourParents.size() ? yourParents.size() : santasParents.size();
	for (size_t i = 0; i < limit; i++) {
		if (santasParents[i].compare(yourParents[i]) == 0)
			sameParentCount++;
	}

	std::cout << yourParents.size() + santasParents.size() - 2 * sameParentCount;
}

void getParentsNames(const Node node, const std::vector<Node> nodes, std::vector<std::string> &parents)
{
	if (node.parentName.compare("") == 0)
		return;
	parents.push_back(node.parentName);

	for (Node n : nodes) {
		if (node.parentName.compare(n.name) == 0) {
			getParentsNames(n, nodes, parents);
		}
	}
}

int countParents(const Node node, const std::vector<Node> nodes) 
{
	if (node.parentName.compare("") == 0)
		return 0;

	for (Node n : nodes) {
		if (node.parentName.compare(n.name) == 0) {
			if (n.totalCount != 0)
				return n.totalCount + 1;
			else
				return countParents(n, nodes) + 1;
		}
	}
}

void sanityCheck(std::vector<Node>& nodes)
{
	for (Node n : nodes) {
		if (n.parentName.compare("") == 0)
			continue;
		for (Node p : nodes) {
			if (p.name.compare(n.parentName) == 0) {

			}
		}
	}

}
