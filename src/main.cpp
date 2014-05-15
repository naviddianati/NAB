/*
 * main.cpp
 *
 *  Created on: May 6, 2014
 *      Author: navid
 */
#include "AgentBased.cpp"
#include <string.h>
#include <cstdlib>

using namespace std;

int size, size_origin, num_agents, num_steps, num_ensembles;
string mode; // "single" or "ensemble"
bool is_debug = false;
void process_input(int argc, char* argv[]) {
	if (argc == 1) {
		size = 50;
		num_agents = 1000;
		num_steps = 100;
	} else if (argc == 4) {
		size = atoi(argv[1]);
		num_agents = atoi(argv[2]);
		num_steps = atoi(argv[3]);
		mode = "single";
	} else if (argc == 5) {
		size = atoi(argv[1]);
		num_agents = atoi(argv[2]);
		num_steps = atoi(argv[3]);
		num_ensembles = atoi(argv[4]);
		mode = "ensemble";
	} else {
		printf("Invalid arguments.");
		exit(EXIT_FAILURE);
	}

	size_origin = size / 10;
}

void measureDisplacements(AgentBased model) {
	if (mode == "ensemble") {
		cout << "ERROR: Need to run under 'single' mode.\n";
		return;
	}
	model.run(num_steps, 0);
	ListDouble dist = model.getDisplacements();
	model.printList<ListDouble>(dist);
}

int main(int argc, char* argv[]) {
	is_debug = false;
	process_input(argc, argv);
	AgentBased model(size, size_origin, is_debug);
	model.resetAgents(num_agents);

//	model.setDebug(1);

	if (mode == "single") {
		model.run(num_steps, 0);
		model.printScores(1);
//		measureDisplacements(model);
//		model.ensembleFixedTime(1, num_steps, 0);
	}

	if (mode == "ensemble") {
		model.ensembleFixedTime(num_ensembles, num_steps, 0);
	}

	exit(0);
	for (int i = 0; i < num_steps; i++) {
		model.step();
//		printf("%d\n", i);
//		cout<<"______________________________________________________________\n";
//		cin.ignore();
	}
//	model.listAll();
}

