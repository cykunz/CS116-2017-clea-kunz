#include "Network.hpp"
#include <iostream>
#include <vector>

using namespace std;

int main()
{
	cout<<"Enter the value of the external current for the network: ";

	double input(0.0);

	cin>>input;
	
	double timeA(0);
	double timeB(0.0);
	cout<<"Enter the value of the the inferior limit of the time interval :";
	do{	cin>>timeA;
	} while(timeA<0.0);
	
	cout<<"Enter the value of the the superior limit of the time interval :";
	do{
		cin>>timeB;
	} while((timeB<=timeA)or(timeB<0.0));
	
	Neuron neuron1;
	Neuron neuron2;
	Network network;
	
	
	/*try{
		network.setNeurons(vector<Neuron*>{ new Neuron(neuron1), new Neuron(neuron2)});
		throw 3.5;
		
	network.createLink(network.getNeurons());
	throw  2;
		network.update(timeA, timeB);
	throw "network";
	} 
	catch(double t)
	{	cerr<<"No neurons set.";
		cout<<endl;
	}

	
	catch(int i)
	{	cerr<<"Unable to create link.";
		cout<<endl;
	}
	
	
	catch(string s)
	{	cerr<<"Network update failed.";
		cout<<endl;
	}*/
	network.setNeurons(vector<Neuron*>{ new Neuron(neuron1), new Neuron(neuron2)});
	network.createLink(network.getNeurons());

	network.update(timeA, timeB, input);
	/*neuron1.showTimeValues();
	neuron2.showTimeValues();*/
	return 0;
}
