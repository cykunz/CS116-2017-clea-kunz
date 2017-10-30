#include "Network.hpp"
#include <iostream>
#include <vector>

using namespace std;

int main()
{	

	double timeA(0);
	double timeB(0.0);
	cout<<"Enter the value of the the inferior limit of the time interval :";
	do{	cin>>timeA;
	} while(timeA<0.0);
	
	cout<<"Enter the value of the the superior limit of the time interval :";
	do{
		cin>>timeB;
	} while((timeB<=timeA)or(timeB<0.0));
	
	Network network;
	/*	Addition of 10000 excitatory neurons,
	 * 	and 2500 inhibitory neurons to the network.	*/
	for(size_t i(0);i<NumberExcitatoryNeurons;++i)
	{	
		network.addNeuron(new Neuron(true));
	}
	for(size_t j(0);j<NumberInhibitoryNeurons;++j)
	{	
		network.addNeuron(new Neuron);
	}
	
	network.initializeStates();
	network.initializeConnections();
	cout<<"Done"<<endl;

	network.update(timeA, timeB);






	return 0;
}
