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
typedef std::map<int, double> ListDouble;
typedef std::pair<int, int> Point;
typedef std::map<Point, List> DictSpace;

// Dict {id: point}
typedef std::map<int, Point> DictPoints;

class AgentBased {
public:
	int size, num_agents;

	DictSpace space;
	DictPoints points, points_initial;
	List scores;
	ListDouble distances;
	bool debug;

	AgentBased(int N, int N_origin) {
		/* initialize random seed: */
		srand(time(NULL));
		dx = 0;
		dy = 0;

		//Initialize
		size = N;
		size_origin = N_origin;
		num_agents = 0;
		DictSpace::iterator it;
		DictPoints::iterator itpoints;
		debug = false;

		setOrigin();
		resetScores();

	}

	void setDebug(bool isDebug) {
		debug = isDebug;
	}
	void resetScores() {
		for (int i = 0; i < num_agents; i++)
			scores[i] = 0;
	}

	void doSomething() {
	}

	/* populate dict_origin which is a dictionary of points that constitute the origin*/
	void setOrigin() {
		int counter = 0;
		for (int i = -size_origin / 2; i < size_origin / 2; i++)
			for (int j = -size_origin / 2; j < size_origin / 2; j++) {
				Point p(i, j);
				dict_origin[counter] = p;
				counter++;
			}
	}

	void resetAgents(int n) {
		num_agents = n;

		// empty space
		space.clear();
		points.clear();
		List list;
		for (int i = 0; i < n; i++) {
			Point p(rand() % size - (size / 2), rand() % size - (size / 2));
			points[i] = p;
			points_initial[i] = p;
			try {
				space.at(p)[i] = 1;
			} catch (exception& e) {
				space[p] = list;
				space[p][i] = 1;
//				cout << e.what() << "\n";
			}
		}

		if (debug)
			listAll();
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

//		dx = rand() % 3 - 1;
//		dy = rand() % 3 - 1;

		dx = (rand() % 2 * 2) - 1;
		dy = (rand() % 2 * 2) - 1;

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

	/* compute distance between two Points*/
	double distance(Point p1, Point p2) {
		double x = p1.first - p2.first;
		double y = p1.second - p2.second;
		return sqrt(x * x + y * y);
	}

	/* This function lists the distances of all agents from their respective initial positions */
	ListDouble getDisplacements() {
		ListDouble dist;
		for (int i = 0; i < num_agents; i++) {
			dist[i] = distance(points[i], points_initial[i]);
		}
		return dist;
	}

	/* Print a list with keys =0,1,2,...,N. T can be List or ListDouble */
	template<class T>
	void printList(T list) {
		for (int i = 0; i < list.size(); i++)
			printf("%d %f\n", i, list[i]);
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
	}

	void updateScores() {
		for (DictPoints::iterator it = dict_origin.begin();
				it != dict_origin.end(); ++it) {
			DictSpace::iterator origin_it = space.find((*it).second);
			if (origin_it != space.end()) {
				List origin_list = (*origin_it).second;
				for (list_it = origin_list.begin();
						list_it != origin_list.end(); ++list_it) {
					scores[(*list_it).first] += origin_list.size() - 1;
				}
			}
		}
	}

	void printScores(int remove_zeros) {
		for (int i = 0; i < num_agents; i++) {
			if (remove_zeros)
				if (scores[i] == 0)
					continue;
			printf("%d %d\n", i, scores[i]);
		}

	}

	void run(int steps, bool verbose) {
		for (int i = 0; i < steps; i++) {
			if (verbose)
				printf("%d\n", i);
			step();
			updateScores();
		}
	}

	void runFixedTime(int steps, bool verbose) {
		for (int i = 0; i < steps; i++) {
			if (verbose)
				printf("%d\n", i);
			step();
		}
		updateScores();
	}

	void ensembleFixedTime(int ensemble_size, int steps, bool verbose) {
		for (int i = 0; i < ensemble_size; i++) {
			if (verbose)
				printf("Ensemble no %d\n", i);
			resetAgents(num_agents);
			resetScores();
			runFixedTime(steps, 0);
			printScores(1);
			if (debug)
				listAll();
		}
	}

private:
	int dx, dy;
	int size_origin;
	Point tmp_point, tmp_point_old;
	List::iterator list_it;
//	Point origin;
	DictPoints dict_origin;

};

