// TODO: implement move() and step()

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
typedef std::map<std::pair<int, int>, List> DictSpace;

// Dict {id: point}
typedef std::map<int, std::pair<int, int> > DictPoints;
typedef std::pair<int, int> Point;

class AgentBased {
public:
	int size, num_agents;

	DictSpace space;
	DictPoints points;
	List scores;

	AgentBased(int N) :
			origin(0, 0) {
		/* initialize random seed: */
		srand(time(NULL));
		dx = 0;
		dy = 0;

		//Initialize
		size = N;
		num_agents = 0;
		DictSpace::iterator it;
		DictPoints::iterator itpoints;

		for (int i = 0; i < num_agents; i++)
			scores[i] = 0;

	}

	void doSomething() {
	}

	void generateAgents(int n) {
		num_agents = n;
		List list;
		for (int i = 0; i < n; i++) {
			Point p(rand() % size, rand() % size);
			points[i] = p;
			try {
				space.at(p)[i] = 1;
			} catch (exception& e) {
				space[p] = list;
				space[p][i] = 1;
//				cout << e.what() << "\n";
			}
		}
	}

	void listAll() {
		DictSpace::iterator it;
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
				printf("'%d' ", (*itList).first);
			}
			cout << "\n";
		}
	}

	/* move the agent with the given agent id*/
	void move(int agent_id) {
		tmp_point_old = points[agent_id];
		// determine the deltas
		dx = rand() % 3 - 1;
		dy = rand() % 3 - 1;
		tmp_point.first = points[agent_id].first + dx;
		tmp_point.second = points[agent_id].second + dy;

		// update points
		points[agent_id] = tmp_point;

		// update space:
		//		find the point in space containing the agent
		//		remove agen't id from that point's List
		space[tmp_point_old].erase(agent_id);

		//		add the agent's id to its new point in space
		space[tmp_point][agent_id] = 1;
	}

	/* move all agents one step forward */
	void step() {

		// for each agent id, move the agent
		for (int i = 0; i < num_agents; i++)
			move(i);

		// (maybe?) remove empty points from space
		DictSpace::iterator it;
		for (it = space.begin(); it != space.end();)
			if ((*it).second.empty()) {
//				printf("Erasing point (%d,%d)\n", (*it).first.first,
//						(*it).first.second);
				space.erase(it++);
			} else
				++it;
		update_scores();
	}

	void update_scores() {
		DictSpace::iterator origin_it = space.find(origin);
		if (origin_it != space.end()) {
			List origin_list = (*origin_it).second;
			for (list_it = origin_list.begin(); list_it != origin_list.end();
					++list_it) {
				scores[(*list_it).first] += origin_list.size() - 1;
			}
		}
	}

	void print_scores() {
		for (int i = 0; i < num_agents; i++)
			printf("%d %d\n", i, scores[i]);

	}

	void run(int steps, bool verbose) {
		for (int i = 0; i < steps; i++) {
			if (verbose)
				printf("%d\n", i);
			step();

		}
	}

private:
	int dx, dy;
	Point tmp_point, tmp_point_old;
	List::iterator list_it;
	Point origin;

};

