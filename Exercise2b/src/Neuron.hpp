#ifndef NEURON_H
#define NEURON_H

#include <vector>
#include <SFML/Graphics.hpp>

using namespace std;

/*	Constants needed for the calculations	*/
const double dt = 0.0001; 					/*	 0.1 ms	*/
const double MembraneThreshold = 0.02; 		/*	20 mV	*/
const double MembraneReset = 0.0; 			/*	0 mV	*/
const double RefractoryPeriod = 0.02; 		/*	20 ms, RefractoryPeriod= Resistance*Capacity	*/
const double Capacity =  1.0;
const double Resistance = RefractoryPeriod/Capacity;  
const double Amplitude= 0.0001;
const double Delay=0.0015;
const int delay_steps=Delay/dt;	/*	Integers */

class Neuron {
	private:	
		/*	The neuron is characterized by its membrane potential,
		 * 	number of spikes, time at which the spikes occured, the present time
		 * 	whether it is refractory or not, as well as the neurons it is linked to.	*/
		
		double input_;	/*	Input received from environment.	*/
		vector<Neuron*> linked_neurons_;	/*	Neurons linked to this one.	*/
		vector<double> time_;	/*	Record of times when a spike occured.	*/
		double membrane_potential_;	/*	Present membrane potential.	*/
		int spikes_;	/*	Number of spikes of neuron.	*/
		int present_time_;	/*	Local clock of neuron.	*/
		bool is_refractory_;	/*	Determines whether the neuron is refractory or not.	*/
		int starttime_;		/*	Start time of simulation.	*/
		int endtime_;	/*	End time of simulation.	*/
		vector<unsigned int> buffer_;	/*	Ring buffer associated with spikes received from linked neurons.	*/
		
	
	public:
	/*	Constructor	*/
	Neuron(	double input=0.0, vector<Neuron*> neurons_=vector<Neuron*>(0), vector<double> time = vector<double>(0.0), 
			double potential=0.0, int spikes=0, int present=0, bool refractory=false, int start=0, int stop=0, 
			vector<unsigned int> b=vector<unsigned int>(delay_steps+1,0)); 
	/*	Destructor	*/
	~Neuron();

/***************************************************/
	/*	Getters	*/
	int getBuffer(int const& idx) const;
	vector<unsigned int> getBufferTotal() const;
	double getInput() const;
	int getEndTime() const;
	double getMembranePotential() const;
	double getMembraneThreshold() const;
	vector<Neuron*> getLinkedNeurons() const;
	int getPresentTime() const;
	bool getRefractory() const;
	int getSpikes() const;
	int getStartTime() const;
	vector<double> getTime() const;

/***************************************************/	
	/*	Setters	*/
	void setBuffer(int const& idx, int const& new_value);
	void setEndTime(int const& timeend);
	void setInput(double const& input);
	void setMembranePotential(double const& new_potential);
	void setPresentTime(int const& present);
	void setRefractory(bool const& is_refractory);
	void setSpikes(int const& new_spikes);
	void setStartTime(int const& timestart);
	void setTime(vector<double> const& new_time);

/***************************************************/
	/*	Method adding other neurons to the list of linked neurons.	*/
	void addNeurons(Neuron* neuron);
	
	/*	Method adding the time at which a spike occured to the vector.	*/
	void addTimeValue(int const& new_time_value);
	
	/*void createWindow(sf::Vector2f const& size);
	void drawPotential(sf::RenderTarget& target);*/
	
	/*	Method calculating the membrane potential depending the input current.	*/
	double MembranePotentialEquation(double const& input, int const& number_spikes) const;
	
	/*	Method receiving a signal given by a presynaptic neuron.	*/
	void receive(int const& timeanddelay);
	
	/*	Method displaying the time values of the spikes.	*/
	void showTimeValues() const;
	
	/*	Method updating the neuron's membrane potential during a 
	 * 	given time interval.	*/
	bool update(double const& input);

};

#endif
