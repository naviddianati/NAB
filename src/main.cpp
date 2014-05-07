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

int size, num_agents,num_steps;

void process_input(int argc, char* argv[]) {
	if (argc == 1) {
		size = 50;
		num_agents = 1000;
		num_steps = 100;
	} else if (argc == 4) {
		size = atoi(argv[1]);
		num_agents = atoi(argv[2]);
		num_steps = atoi(argv[3]);
	} else {
		printf("Invalid arguments.");
		exit(EXIT_FAILURE);
	}
}

int main(int argc, char* argv[]) {
	process_input(argc, argv);
	AgentBased model(size);
	model.doSomething();
	model.generateAgents(num_agents);

	model.run(num_steps,0);
	model.print_scores();

	exit(0);
	for (int i = 0; i < num_steps; i++) {
		model.step();
//		printf("%d\n", i);
//		cout<<"______________________________________________________________\n";
//		cin.ignore();
	}
//	model.listAll();
}

