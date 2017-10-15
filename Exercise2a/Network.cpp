#include "Network.hpp"
#include <cassert>
#include <iostream>
#include <fstream>
Network::Network(vector<Neuron*> new_neur, int clock, int timestart, int timeend)
	: neurons_(new_neur), clock_time_(clock), timestart_(timestart), timeend_(timeend)
{}

Network::~Network()
{	for (auto neuron: neurons_)
	{	neuron=nullptr;
		delete neuron;
		
	}
	neurons_.clear();
}
/***************************************************/
/*	Getters	*/

int Network::getClockTime() const
{	return clock_time_;
}

vector<Neuron*> Network::getNeurons() const
{	return neurons_;
}

int Network::getTimeStart() const
{	return timestart_;
}

int Network::getTimeEnd() const
{	return timeend_;
}

/***************************************************/
/*	Setters	*/

void Network::setClockTime(int const& new_time)
{	clock_time_=new_time;
}

void Network::setNeurons(vector<Neuron*> const& new_neurons)
{	clearNeurons();
	for(size_t i(0);i<new_neurons.size();++i)
	{	
		neurons_.push_back(new_neurons[i]);
	}
}

void Network::setTimeStart(int const& new_timestart)
{	timestart_=new_timestart;
}

void Network::setTimeEnd(int const& new_timeend)
{	timeend_=new_timeend;
}

/***************************************************/
void Network::clearNeurons()
{	for(size_t i(0);i<neurons_.size();++i)
	{	neurons_[i]=nullptr;
	}
	neurons_.clear();
}

void Network::createLink(vector<Neuron*> neurons_to_link)
{
	if(!neurons_to_link.empty())
	{ 
		/*	Iteration in all neurons in the list given.	*/
		for(size_t i(0);i<neurons_to_link.size()-1;++i)
		{	
			if((neurons_to_link[i]!=nullptr)and(neurons_to_link.size()>0))
			{	
				
				/*	For each neuron, we have to iterate in the rest of the list
				 * 	in order to add the present neuron to each list of linked_neurons_.	*/
				for(size_t j(i+1);j<neurons_to_link.size();++j)
				{	
					if(neurons_to_link[j]!=nullptr)
					{	
						/*	Both neurons add each other mutually.	*/
						neurons_to_link[i]->addNeurons(neurons_to_link[j]);

						//neurons_to_link[j]->addNeurons(neurons_to_link[i]);
						
					}
				}
			}
		}
	}
}
void Network::update(double const& timeA, double const& timeB, double const& input)
{	setClockTime(timeA/dt); /*	Time independent of dt.	*/
	int end((timeB-timeA)/dt); /*	Number of time steps to do */
	ofstream linkedtext("Linked.txt");
	ofstream maintext("NetworkNeuron.txt");
	while(getClockTime()<end)
	{	cout<<"Loop number "<<getClockTime()<<endl;
		if(!getNeurons().empty())
		{  
			for(auto& NetworkNeuron: getNeurons())
			{	cout<<"Network"<<endl;
				maintext<<NetworkNeuron->getMembranePotential()<<endl;
				if((NetworkNeuron->update(input)) and (!(NetworkNeuron->getLinkedNeurons()).empty()))
				{	
					cout<<"Neuron spikes."<<endl;
					cout<<"Network neuron potential: "<<NetworkNeuron->getMembranePotential()<<endl;
					
					
					for(auto& LinkedNeuron: (NetworkNeuron->getLinkedNeurons()))
					{	cout<<"Linked neuron potential: "<<LinkedNeuron->getMembranePotential()<<endl;
						LinkedNeuron->receive(getClockTime()+Delay, Amplitude);
						linkedtext<<LinkedNeuron->getMembranePotential()<<endl;
						/*while(LinkedNeuron->getMembranePotential()>0.0)
						{	LinkedNeuron->setMembranePotential(LinkedNeuron->MembranePotentialEquation(0.0));
							linkedtext<<LinkedNeuron->getMembranePotential()<<endl;
						}*/
						
					}
				}
			}
		}
		setClockTime(getClockTime()+1);
		
	}
	maintext.close();
	linkedtext.close();
}




