#include <iostream>
#include <stdio.h>
#include <map>
#include <utility>
#include <cmath>
#include <stdlib.h>
#include <vector>
#include <exception>
#include <time.h>

using namespace std;

typedef std::map<int, int> List;
typedef std::map<std::pair<int, int>, List> Dict;

// Dict {id: point}
typedef std::map<int, std::pair<int, int> > DictPoints;
typedef std::pair<int, int> Point;

class AgentBased {
public:
	int size;
	Dict space;
	DictPoints dictpoints;

	AgentBased(int N) {
		/* initialize random seed: */
		srand(time(NULL));

		//Initialize
		size = N;

		Dict::iterator it;
		DictPoints::iterator itpoints;
	}

	void doSomething() {
		cout << "Hello World!\n";
	}

	void generateAgents(int n) {
		List list;
		for (int i = 0; i < n; i++) {
			Point p(rand() % size, rand() % size);
			dictpoints[i] = p;
			try {
				space.at(p)[i] = 1;
			} catch (exception& e) {
				space[p] = list;
				space[p][i] = 1;
				cout << e.what() << "\n";
			}
		}
	}

	void listAll() {
		Dict::iterator it;
		List::iterator itList;
		List list_of_indices;
		int i;
		Point p;
		for (it = space.begin(), i = 0; it != space.end(); ++it, i++) {
			p = (*it).first;
			list_of_indices = (*it).second;
			printf("(%d,%d) ->", p.first, p.second);
			for (itList = list_of_indices.begin();
					itList != list_of_indices.end(); ++itList) {
				printf("(%d:%d)", (*itList).first, (*itList).second);
			}
			cout << "\n";
		}
	}


	/* move the agent with the given agent id*/
	void move(int agent_id) {
		// determine the deltas
		// update dictpoints
		// update space:
		//		find the point in space containing the agent
		//		remove agen't id from that point's List
		//		add the agent's id to its new point in space
	}

	/* move all agents one step forward */
	void step(){
		// for each agent id, move the agent
		// (maybe?) remove empty points from space
	}
};

