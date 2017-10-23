#ifndef NETWORK_H
#define NETWORK_H
#include <iostream>
#include <vector>
#include "Neuron.hpp"

using namespace std;

class Network
{	
	private:
	/*!	A network is caracterized by the neurons it contains, its global time, 
	 * 	the start and end time of its simulation.	*/
	 
	vector<Neuron*> neurons_;	/**<	Neurons in network.	*/
	unsigned int clock_time_;	/**<	Global time of network.	*/
	unsigned int timestart_;		/**<	Start time of simulation.	*/
	unsigned int timeend_;		/**< End time of simulation.	*/
	
	public:
	//! Constructor
	/*! By default, the vector of neurons it contains has a size of 0, and all times are set to 0.*/
	Network(vector<Neuron*> new_neur=vector<Neuron*>(0), unsigned int clock=0, unsigned int timestart=0, unsigned int timeend=0);
	
	//! Destructor
	/*!	Clears the vector of neurons in the network by setting them to nullptr and deleting them.	*/
	~Network();

/***************************************************/
	/*	Getters	*/
	//! Gets the clock time (simulation time)
	/*!	@return Simulation time, as a dt step.	*/
	unsigned int getClockTime() const;
	//! Gets the neurons in the network
	/*!	@return Vector of pointers on neurons.	*/
	vector<Neuron*> getNeurons() const;
	//! Gets the end time of simulation
	/*!	@return End time, as a dt step.	*/
	unsigned int getTimeEnd() const;
	//! Gets the start time of simulation
	/*!	@return Start time, as a dt step.	*/
	unsigned int getTimeStart() const;
	
/***************************************************/
	/*	Setters	*/
	//!	Sets the clock time
	/*!	@param	new_time: New value for the clock time. */
	void setClockTime(unsigned int const& new_time);
	//!	Sets the neurons in the network
	/*!	@param	new_neurons: New vector of neurons wanting to be part of the network. */
	void setNeurons(vector<Neuron*> const& new_neurons);
	//!	Sets the time at which the simulation start
	/*!	@param	new_timestart= New start time value. */
	void setTimeStart(unsigned int const& new_timestart);
	//!	Sets the time at which the simulation ends
	/*!	@param	new_timeend: New end time value. */
	void setTimeEnd(unsigned int const& new_timeend);

/***************************************************/
	
	//!A public function
	/*!	Clears the vector of all neurons in the network.*/
	void clearNeurons();
	
	//!A public function taking vector of pointers on neurons as a parameter
	/*!	Links all neurons in the vector given.
	 * 	@param neurons_to_link: Vector of pointers on neurons wanting to be linked.	*/
	void createLink(vector<Neuron*> neurons_to_link);

	//!A public function taking two double arguments
	/*!	Method updating all neurons in the network, passing on the spike signal in case of spike.	
	 * 	@param timeA: Time at which simulation starts.
	 * 	@param timeB: Time at which simulation ends.		*/
	void update(double const& timeA, double const& timeB);
	
	
};
#endif
