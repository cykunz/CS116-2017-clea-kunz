#ifndef NETWORK_H
#define NETWORK_H
#include <iostream>
#include <vector>
#include "Neuron.hpp"

using namespace std;

const double Delay=0.1*dt;


class Network
{	
	private:
	vector<Neuron*> neurons_;
	int clock_time_;
	
	int timestart_;
	int timeend_;
	
	public:
	Network(vector<Neuron*> new_neur=vector<Neuron*>(0), int clock=0, int timestart=0, int timeend=0);
	~Network();
	
	/*	Getters	*/
	int getClockTime() const;
	vector<Neuron*> getNeurons() const;
	int getTimeEnd() const;
	int getTimeStart() const;
	
	/*	Setters	*/
	void setClockTime(int const& new_time);
	void setNeurons(vector<Neuron*> const& new_neurons);
	void setTimeStart(int const& new_timestart);
	void setTimeEnd(int const& new_timeend);
	
	void clearNeurons();
	/*	Method linking two neurons; each neuron will appear in the other's linked_neurons_ list.	*/
	void createLink(vector<Neuron*> neurons_to_link);
	
	/*	Method passing on the spike signal of each neuron having one. 	*/	
	void update(double const& timeA, double const& timeB, double const& input);
	
	
};
#endif
