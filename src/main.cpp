/*
 * main.cpp
 *
 *  Created on: May 6, 2014
 *      Author: navid
 */
#include "AgentBased.cpp"

using namespace std;

int main(){
	AgentBased model(40);
	model.doSomething();
	model.generateAgents(1000);
	model.listAll();
}


