#include "Network.hpp"
#include <cassert>
#include <iostream>
#include <fstream>
#include <random>

Network::Network(vector<Neuron*> new_neur, int clock, int timestart, int timeend, vector<vector<unsigned int>> connect)
	: neurons_(new_neur), clock_time_(clock), timestart_(timestart), timeend_(timeend), connections_(connect)
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
	/*ofstream file;
	/*	Opening of file to contain membrane potentials of neurons.	*/
	/*file.open("neurontext.txt");
	if (file.fail())
	{	cerr<<"File failed to open."<<endl;
	}
	assert(!file.fail());
	file<<"";
	file.close();*/
	
	/*	Opening of a file containing the amount of spikes at each time step.	*/
	/*ofstream f;
	f.open("buffertext.txt");
	
	if (f.fail())
	{	cerr<<"File buffer failed to open."<<endl;
	}
	
	assert(!f.fail());
	f<<"";
	f.close();*/
	
	/*	Initialization of a 12500 by 12500 matrix.	*/
	for(size_t i(0);i<connections_.size();++i)
	{	connections_[i].resize(12500);
	}
	
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

vector<vector<unsigned int>> Network::getConnectionsMatrix() const
{	return connections_;
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

void Network::initializeStates()
{	/*	For simplicity reasons, all excitatory neurons will be the first indexes until
		the total number of excitatory neurons, and all the rest will be inhibitory.	*/
		for(size_t i(0);i<NumberExcitatoryNeurons;++i)
	{	getNeurons()[i]->setExcitatory(true);
	}
}

void Network::initializeConnections()
{	
	/*	Each neuron receives an input of 10% from all other neurons, from which 1000 connections
	 * 	are excitatory and 250 are inhibitory.	*/

	for(size_t i(0);i<getNeurons().size();++i)
	{	
	
			unsigned int excitatory_connections(0);
			unsigned int inhibitory_connections(0);
			
			/*	All excitatory neurons are within the index 0 and the number of excitatory neurons.	*/

				/*	Every neuron should have 1000 excitatory connections.	*/
				while(excitatory_connections<NumberExcitatoryConnections)
				{	random_device random;
					mt19937 gen(random());
					uniform_int_distribution<int> l(0, NumberExcitatoryNeurons-1);
					
					/*	Adds a random excitatory connection.	*/
					++connections_[i][l(gen)];
					++excitatory_connections;
				}
			
			/*	All other neurons should be inhibitory.	*/

				/*	Every neuron must have 250 inhibitory connections.	*/
				while(inhibitory_connections<NumberInhibitoryConnections)
				{	random_device random;
					mt19937 gen(random());
					uniform_int_distribution<int> o(NumberExcitatoryNeurons,getNeurons().size()-1);
					
					/*	Adds a random inhibitory connection.	*/
					++connections_[i][o(gen)];
					++inhibitory_connections;
				}
			
		
	}

	
}

void Network::update(double const& timeA, double const& timeB)
{	
	setClockTime(timeA/dt); /*	Time independent of dt.	*/
	unsigned int end(abs((timeB/dt)-getClockTime()));
	unsigned int number_spikes(0);
	/*	While the clock time is within the interval...	*/
	while(getClockTime()<end)
	{	
		/*	Verifies if there are neurons in the network.	*/
		if(!getNeurons().empty())
		{  
			/*	Iteration in all neurons contained in the network.	*/
			for(size_t i(0);i<getNeurons().size();++i)
			{	
				/*	If a certain neuron spikes, it will pass on its spike to all its linked
				 * 	neurons, this information is contained in the connection matrix. */
				if(getNeurons()[i]->update())
				{	++number_spikes;
					for(size_t j(0);j<connections_.size();++j)
					
					/*	If both neurons are connected, the postsynaptic neuron
					 * 	will receive the signal.	*/
					if(connections_[j][i]!=0)
					{	
						/*	If the neuron giving a signal is excitatory, it will later give 
						 * 	an amplitude of +Amplitude, whereas if it is inhibitory, the amplitude
						 * 	given will be of -Amplitude.	*/	
						if(getNeurons()[i]->getExcitatory())
						{	getNeurons()[j]->receive(getClockTime(), connections_[j][i]);
						} else{
		
							getNeurons()[j]->receive(getClockTime(), -connections_[j][i]);
						}
							
					}
				}
			}
					
		}
	ofstream file;
	file.open("spikes.txt", ios::out | ios::app);
	 if(file.fail())
	 {	cerr<<"File failed to open in Network."<<endl;
	 }
	 assert(!file.fail());
	 
	 file<<getClockTime()<<" "<<number_spikes/dt<<endl;
	 file.close();
	 number_spikes=0;
		/*	Makes the overall simulation time evolve.	*/
		setClockTime(getClockTime()+1);
		
	}
}




