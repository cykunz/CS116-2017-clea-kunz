#ifndef NETWORK_H
#define NETWORK_H
#include <iostream>
#include <vector>
#include <array>
#include "Neuron.hpp"

using namespace std;

//! Network class
/*!	Class regrouping numerous amounts of neurons, and having its own clock in order to 
 * 	to the correct simulation.	*/
class Network
{	
	private:
	/*!	A network is caracterized by the neurons it contains, its global time, 
	 * 	the start and end time of its simulation.	*/
	 
	vector<Neuron*> neurons_;	/**<	Neurons in network.	*/
	int clock_time_;	/**<	Global time of network.	*/
	int timestart_;		/**<	Start time of simulation.	*/
	int timeend_;		/**< End time of simulation.	*/
	
	public:
	//! Constructor
	/*! By default, the vector of neurons it contains has a size of 0, and all times are set to 0.*/
	Network(vector<Neuron*> new_neur=vector<Neuron*>(0), int clock=0, int timestart=0, int timeend=0);
	
	//! Destructor
	/*!	Clears the vector of neurons in the network by setting them to nullptr and deleting them.	*/
	~Network();

/***************************************************/
	/*	Getters	*/
	//! Gets the clock time (simulation time)
	/*!	@return Simulation time, as a dt step.	*/
	int getClockTime() const;
	//! Gets the neurons in the network
	/*!	@return Vector of pointers on neurons.	*/
	vector<Neuron*> getNeurons() const;
	//! Gets the end time of simulation
	/*!	@return End time, as a dt step.	*/
	int getTimeEnd() const;
	//! Gets the start time of simulation
	/*!	@return Start time, as a dt step.	*/
	int getTimeStart() const;
	
/***************************************************/
	/*	Setters	*/
	//!	Sets the clock time
	/*!	@param	new_time: New value for the clock time. */
	void setClockTime(int const& new_time);
	//!	Sets the neurons in the network
	/*!	@param	new_neurons: New vector of neurons wanting to be part of the network. */
	void setNeurons(vector<Neuron*> const& new_neurons);
	//!	Sets the time at which the simulation start
	/*!	@param	new_timestart= New start time value. */
	void setTimeStart(int const& new_timestart);
	//!	Sets the time at which the simulation ends
	/*!	@param	new_timeend: New end time value. */
	void setTimeEnd(int const& new_timeend);

/***************************************************/
	//!A public function taking a Neuron pointer as parameter
	/**! Adds a neuron to the list of neurons in the network.
	 * @param neuron_to_add: Pointer on a neuron	*/
	 void addNeuron(Neuron* neuron_to_add);
	 
	//!A public function
	/*!	Clears the vector of all neurons in the network.*/
	void clearNeurons();
	
	//!A public function taking vector of pointers on neurons as a parameter
	/*!	Links all neurons in the vector given. This method was mostly used to link 2 neurons.
	 * 	@param neurons_to_link: Vector of pointers on neurons wanting to be linked.	*/
	void createLink(vector<Neuron*> neurons_to_link);

	//!A public function
	/*! Initializes the matrix of connections in the network.	*/
	void initializeConnections();
	
	//!A public function taking two double arguments
	/*!	Method updating all neurons in the network, passing on the spike signal in case of spike.	
	 * 	@param timeA: Time at which simulation starts.
	 * 	@param timeB: Time at which simulation ends.		*/
	void update(double const& timeA, double const& timeB);
	
	
};
#endif
