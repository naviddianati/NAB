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

	size_origin = size/10;
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
	process_input(argc, argv);
	AgentBased model(size, 10);
	model.resetAgents(num_agents);

	model.setDebug(0);

	if (mode == "single") {
		/*odel.run(num_steps, 0);
		 model.printScores(0);*/
		measureDisplacements(model);
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

