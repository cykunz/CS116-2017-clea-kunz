#ifndef NETWORK_H
#define NETWORK_H
#include <iostream>
#include <vector>
#include "Neuron.hpp"

using namespace std;

class Network
{	
	private:
	/*	A network is caracterized by the neurons it contains, its global time, 
	 * 	the start and end time of its simulation.	*/
	 
	vector<Neuron*> neurons_;	/*	Neurons in network.	*/
	int clock_time_;	/*	Global time of network.	*/
	int timestart_;
	int timeend_;
	
	public:
	/*	By default, the vector of neurons it contains has a size of 0, and all times are set to 0. 	*/
	Network(vector<Neuron*> new_neur=vector<Neuron*>(0), int clock=0, int timestart=0, int timeend=0);
	~Network();

/***************************************************/
	/*	Getters	*/
	int getClockTime() const;
	vector<Neuron*> getNeurons() const;
	int getTimeEnd() const;
	int getTimeStart() const;
	
/***************************************************/
	/*	Setters	*/
	void setClockTime(int const& new_time);
	void setNeurons(vector<Neuron*> const& new_neurons);
	void setTimeStart(int const& new_timestart);
	void setTimeEnd(int const& new_timeend);

/***************************************************/
	/*	Method clearing all neurons in the vector of the network.	*/
	void clearNeurons();
	
	/*	Method linking two neurons; each neuron will appear in the other's linked_neurons_ list.	*/
	void createLink(vector<Neuron*> neurons_to_link);
	
	/*	Method passing on the spike signal of each neuron to its linked neurons. 	*/	
	void update(double const& timeA, double const& timeB);
	
	
};
#endif
