#include "Network.hpp"
#include <cassert>
#include <iostream>
#include <fstream>
#include <random>

Network::Network(vector<Neuron*> new_neur, unsigned int clock, unsigned int timestart, unsigned int timeend)
	: neurons_(new_neur), clock_time_(clock), timestart_(timestart), timeend_(timeend)
{		
	
	ofstream file;
	/*	Opening of file to contain membrane potentials of neurons.	*/
	file.open("neurontext.txt");
	if (file.fail())
	{	cerr<<"File failed to open."<<endl;
	}
	assert(!file.fail());
	file<<"";
	file.close();
	
	/*	Opening of a file containing the amount of spikes at each time step.	*/
	ofstream f;
	f.open("buffertext.txt");
	
	if (f.fail())
	{	cerr<<"File buffer failed to open."<<endl;
	}
	
	assert(!f.fail());
	f<<"";
	f.close();

}

Network::~Network()
{	/*	The destructor will set all neurons pointed at to nullptr, and then deletes them before
		clearing the vector.	*/
	clearNeurons();
}
/***************************************************/
/*	Getters	*/

unsigned int Network::getClockTime() const
{	return clock_time_;
}

vector<Neuron*> Network::getNeurons() const
{	return neurons_;
}

unsigned int Network::getTimeStart() const
{	return timestart_;
}

unsigned int Network::getTimeEnd() const
{	return timeend_;
}

/***************************************************/
/*	Setters	*/

void Network::setClockTime(unsigned int const& new_time)
{	clock_time_=new_time;
}

void Network::setNeurons(vector<Neuron*> const& new_neurons)
{	/*	Before affecting new pointers, clears the vector.	*/
	clearNeurons();
	for(size_t i(0);i<new_neurons.size();++i)
	{	
		/*	The new pointers on Neurons are added to the vector.	*/
		neurons_.push_back(new_neurons[i]);
	}
}

void Network::setTimeStart(unsigned int const& new_timestart)
{	timestart_=new_timestart;
}

void Network::setTimeEnd(unsigned int const& new_timeend)
{	timeend_=new_timeend;
}

/***************************************************/
void Network::clearNeurons()
{	/*	First sets all pointers to nullptr and deletes them.	*/
	for(size_t i(0);i<neurons_.size();++i)
	{	neurons_[i]=nullptr;
		delete neurons_[i];
	}
	
	/*	It will leave an empty vector with a size of 0.	*/
	neurons_.clear();
}

void Network::createLink(vector<Neuron*> neurons_to_link)
{	/*	Verifies if the vector given is empty or not.	*/
	assert(!neurons_to_link.empty());
	
	if(!neurons_to_link.empty())
	{ 
		/*	Iteration in all neurons in the list given.	*/
		for(size_t i(0);i<neurons_to_link.size()-1;++i)
		{	
			/*	Verifies that the neuron in the vector aren't nullptrs, and that
			 *	the vector given doesn't contain a single neuron, in which case
			 * 	the link wouldn't make sense. 	*/
			 assert(neurons_to_link[i]!=nullptr);
			 assert(neurons_to_link.size()>1);
			if((neurons_to_link[i]!=nullptr)and(neurons_to_link.size()>1))
			{	
				
				/*	For each neuron, we have to iterate in the rest of the list
				 * 	in order to add the present neuron to each list of linked_neurons_.	*/
				for(size_t j(i+1);j<neurons_to_link.size();++j)
				{	
					assert(neurons_to_link[j]!=nullptr);
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

void Network::update(double const& timeA, double const& timeB)
{	
	setClockTime(timeA/dt); /*	Time independent of dt.	*/
	unsigned int end(abs((timeB/dt)-getClockTime()));
	
	/*	While the clock time is within the interval...	*/
	while(getClockTime()<end)
	{	
		/*	Verifies if there are neurons in the network.	*/
		if(!getNeurons().empty())
		{  
			/*	Iteration in all neurons contained in the network.	*/
			for(auto& NetworkNeuron:getNeurons())
			{	
				
				/*	If the network neuron spikes, it transmits the signal to each of its linked neurons (if 
				 * 	it has any).	*/
				if((NetworkNeuron->update()) and (!(NetworkNeuron->getLinkedNeurons()).empty()))
				{	
					cout<<"Spike at time "<<getClockTime()*dt<<endl;
					
					
				/*	Iteration in all linked neurons to transmit the signal.	*/
					for(auto& LinkedNeuron: (NetworkNeuron->getLinkedNeurons()))
					{	
						LinkedNeuron->receive(getClockTime());
					}
					
				}
		
			}
		}
		/*	Makes the overall simulation time evolve.	*/
		setClockTime(getClockTime()+1);
		
	}
}




