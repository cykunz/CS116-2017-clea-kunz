#ifndef NEURON_H
#define NEURON_H

#include <vector>
#include <SFML/Graphics.hpp>
#include <math.h>

using namespace std;

//!	Constants needed for the calculations	*/
const double dt = 0.1;//0.0001; 					/**<	The time step, 0.1 milliseconds	*/
const double MembraneThreshold =20.0;//= 0.02; 		/**<	The membrane potential threshold, 20.0 milliVolts	*/
const double MembraneReset = 0.0; 			/**<	The membrane potential reset value, 0.0 Volts	*/
const double RefractoryPeriod = 2.0;//0.002; 		/**<	The refractory period, 2 milliseconds	*/
const double Tao = 20.0;//0.02;
const double Capacity =  1.0;				/**< 	The capacity, 1 Faraday	*/
const double Resistance = Tao/Capacity;  /**< The resistance, in Ohms	*/
const double Amplitude= 0.1;//0.0001;				/**< The amplitude, 0.1 milliVolts	*/
const double Delay=1.5;//0.0015;					/**< The delay, 1.5 milliseconds	*/
const unsigned int delay_steps=static_cast<unsigned long>(floor(Delay/dt));

class Neuron {
	private:	
		/*!	The neuron is characterized by its membrane potential,
		 * 	number of spikes, time at which the spikes occured, the present time
		 * 	whether it is refractory or not, as well as the neurons it is linked to.	*/
		
		double input_;	/**<	Input received from environment.	*/
		vector<Neuron*> linked_neurons_;	/**<	Neurons linked to this one.	*/
		vector<double> time_;	/**<	Record of times when a spike occured.	*/
		double membrane_potential_;	/**<	Present membrane potential.	*/
		int spikes_;	/**<	Number of spikes of neuron.	*/
		int present_time_;	/**<	Local clock of neuron.	*/
		bool is_refractory_;	/**<	Determines whether the neuron is refractory or not.	*/
		vector<unsigned int> buffer_;	/**<	Ring buffer associated with spikes received from linked neurons.	*/
	
	public:
	//!	Constructor	
	/*! Initialization of all number values to 0, boolean representing if is is refractory
	 * 	to false, and the buffer to the correct size.	*/
	Neuron(	double input=0.0, vector<Neuron*> neurons_=vector<Neuron*>(0), vector<double> time = vector<double>(0.0), 
			double potential=0.0, int spikes=0, int present=0, bool refractory=false,
			vector<unsigned int> b=vector<unsigned int>(0)); 
	//!	Destructor
	/*!	Clears the linked neurons vector of all pointers, by deleting them.	*/
	~Neuron();

/***************************************************/
	/*	Getters	*/
	//! Gets the buffer value at a certain index
	/*!	@param idx is the index at which we want to find the buffer value.	
	 * 	@return Buffer value at index.	*/
	int getBuffer(int const& idx) const;
	//! Getter of the overall buffer
	/*! @return Vector of buffer values, representing number of spikes at each time step.	*/
	vector<unsigned int> getBufferTotal() const;
	//!	Gets the input current
	/*!	@return Input current.	*/
	double getInput() const;
	//!	Gets the linked neurons
	/*!	@return Vector of pointers of the linked neurons.	*/
	vector<Neuron*> getLinkedNeurons() const;
	//!	Gets the membrane potential
	/*!	@return Membrane potential.	*/
	double getMembranePotential() const;
	//!	Gets the membrane threshold (constant)
	/*!	@return double: Membrane threshold.	*/
	double getMembraneThreshold() const;
	//!	Gets of the present time
	/*!	@return int: Present time of neuron.	*/
	int getPresentTime() const;
	//!	Gets the refractory state
	/*!	@return bool: if refractory or not.	*/
	bool getRefractory() const;
	//!	Gets the number of spikes
	/*!	@return Number of spikes overall.	*/
	int getSpikes() const;
	//!	Gets the times at which spikes occurred
	/*!	@return Vector of the times at which the spikes occurred.	*/
	vector<double> getTime() const;

/***************************************************/	
	/*	Setters	*/
	//!	Sets the buffer value at a certain index
	/*!	@param	idx: Index at which we want to affect buffer.
	 * 	@param	new_value: New value wanting to be introduced. */
	void setBuffer(int const& idx, int const& new_value);
	//!	Sets the input value
	/*!	@param	input: New input value. */
	void setInput(double const& input);
	//!	Sets the membrane potential
	/*!	@param	new_potential: New membrane potential.*/
	void setMembranePotential(double const& new_potential);
	//!	Sets the present time of neuron
	/*!	@param	present: New present time.*/
	void setPresentTime(int const& present);
	//!	Sets the refractory state
	/*!	@param	is_refractory: Bool of whether it will be refractory or not.	*/
	void setRefractory(bool const& is_refractory);
	//!	Sets the number of spikes it has received
	/*!	@param	new_spikes: New number of spikes received. */
	void setSpikes(int const& new_spikes);
	//!	Sets the vector of times of spikes
	/*!	@param	new_time: New vector of times of spikes.	*/
	void setTime(vector<double> const& new_time);

/***************************************************/
	//!A public function taking a pointer on neuron as argument
	/*!	Adds a pointer on a neuron to the list of linked neurons.
	 * 	@param neuron: Pointer on a neuron wanting to be added to the linked neurons.	*/
	void addNeurons(Neuron* neuron);
	
	//!A public function taking an integer argument
	/*!	Adds the time at which a spike occured to the vector.
	 * 	@param new_time_value: Time at which a spike occured, wanting to be recorded.	*/
	void addTimeValue(int const& new_time_value);
	
	/*void createWindow(sf::Vector2f const& size);
	void drawPotential(sf::RenderTarget& target);*/
	//!A public function taking a double and an integer as parameters
	/*!	Calculates the membrane potential depending on a certain input and number of spikes.
	 * 	@param input: Input current at which membrane potential is calculated.
	 * 	@param number_spikes: Number of spikes occurring.	*/
	double MembranePotentialEquation(double const& input, double const& amplitude) const;
	
	//!A public function taking an integer argument
	/*!	Receives signal given by presynaptic neuron.
	 * 	@param timeanddelay: Time + Delay at which the postsynaptic neuron will receive the signal.	*/
	void receive(int const& time);
	
	//!A public function 
	/*!	Displays the times at which all spikes occurred.*/
	void showTimeValues() const;
	//!A public function 
	/*! Updates the membrane potential.
	 * 	@return bool: Whether there has been a spike or not. 	*/
	bool update();

};

#endif
