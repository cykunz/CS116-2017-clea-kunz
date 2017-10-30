#include "Network.hpp"
#include <cassert>
#include <iostream>
#include <fstream>
#include <random>

Network::Network(vector<Neuron*> new_neur, int clock, int timestart, int timeend)
	: neurons_(new_neur), clock_time_(clock), timestart_(timestart), timeend_(timeend)
{		
	ofstream file;
	/*	Opening of file to contain membrane potentials of neurons.	*/
	file.open("spikes.txt");
	if (file.fail())
	{	cerr<<"File failed to open."<<endl;
	}
	assert(!file.fail());
	file<<"";
	file.close();
	
}

Network::~Network()
{	/*	The destructor will set all neurons pointed at to nullptr, and then deletes them before
		clearing the vector.	*/
	clearNeurons();
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
{	/*	Before affecting new pointers, clears the vector.	*/
	clearNeurons();
	for(size_t i(0);i<new_neurons.size();++i)
	{	
		/*	The new pointers on Neurons are added to the vector.	*/
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
void Network::addNeuron(Neuron* neuron_to_add)
{	neurons_.push_back(neuron_to_add);
}

void Network::clearNeurons()
{	/*	First sets all pointers to nullptr and deletes them.	*/
	for(size_t i(0);i<neurons_.size();++i)
	{	neurons_[i]=nullptr;
		delete neurons_[i];
	}
	
	/*	It will leave an empty vector with a size of 0.	*/
	neurons_.clear();
}


void Network::initializeConnections()
{	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<int> Weight(1, 10);
	uniform_int_distribution<int> Excitat(0, NumberExcitatoryNeurons-1);
	uniform_int_distribution<int> Inhib(NumberExcitatoryNeurons,getNeurons().size()-1);
	/*	Each neuron receives an input of 10% from all other neurons, from which 1000 connections
	 * 	are excitatory and 250 are inhibitory.	*/

	for(size_t i(0);i<getNeurons().size();++i)
	{	
	
			unsigned int excitatory_connections(0);
			unsigned int inhibitory_connections(0);

			/*	All excitatory neurons are within the index 0 and the number of excitatory neurons.	*/

				/*	Every neuron should have 1000 excitatory connections.	*/
				while(excitatory_connections<NumberExcitatoryConnections)
				{	
					/*	Useful to store a value of number of excitatory connections.	*/
					int ran(Weight(gen));
					
					/*	Adds a random excitatory connection.	*/
					getNeurons()[i]->addLink(Excitat(gen), ran);
					excitatory_connections+=ran;
				}
			
			/*	All other neurons should be inhibitory.	*/

				/*	Every neuron must have 250 inhibitory connections.	*/
				while(inhibitory_connections<NumberInhibitoryConnections)
				{	
					/*	Useful to store a value of number of inhibitory connections.	*/
					int r(Weight(gen));
					/*	Adds a random inhibitory connection.	*/
					getNeurons()[i]->addLink(Inhib(gen), r);
					inhibitory_connections+=r;
				}

	}

	
}

void Network::update(double const& timeA, double const& timeB)
{	double difference(timeA-0);
	unsigned int end(abs((timeB-timeA)/dt));
	unsigned int number_spikes(0);

	/*	While the clock time is within the interval...	*/
	while(getClockTime()<end)
	{	
		/*	Verifies if there are neurons in the network.	*/
		assert(!getNeurons().empty());
		
			/*	Iteration in all neurons contained in the network.	*/
			for(size_t i(0);i<getNeurons().size();++i)
			{	
				assert(!getNeurons()[i]->getLinkedNeurons().empty());
	
				if(getNeurons()[i]->update())
				{		++number_spikes;
						/*	The value parameter indicates us whether the amplitude added (used in receive)
						 * 	is negative (if neuron is inhibitory) or positive (excitatory neuron).	*/
						int value(-1);
						if(getNeurons()[i]->getExcitatory())
						{	
							value=1;
						}
						
						for(size_t j(0);j<getNeurons()[i]->getLinkedNeurons().size();++j)
						{	unsigned int index(getNeurons()[i]->getLinkedNeurons()[j]);				
							/*	Note that linkedneurons[j] gives us the index of the corresponding neuron in
							 * 	the network.	*/
							getNeurons()[index]->receive(getClockTime(), value*(getNeurons()[i]->getWeights()[j]));
						}
			
				}

				
			}
					
		
	ofstream file;
	file.open("spikes.txt", ios::out | ios::app);
	 if(file.fail())
	 {	cerr<<"File failed to open in Network."<<endl;
	 }
	 assert(!file.fail());
	 double density(number_spikes/dt);
	 file<<getClockTime()+difference<<" "<<density<<endl;
	 file.close();
	 number_spikes=0;
	
	/*	Makes the overall simulation time evolve.	*/
	setClockTime(getClockTime()+1);
		
	
	}	
}



