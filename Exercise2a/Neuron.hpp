#ifndef NEURON_H
#define NEURON_H

#include <vector>
#include <SFML/Graphics.hpp>

using namespace std;

/*	Constants needed for the calculations	*/
const double dt = 0.001; 					/*	 1 ms	*/
const double MembraneThreshold = 0.02; 		/*	20 mV	*/
const double MembraneReset = 0.0; 			/*	0 mV	*/
const double RefractoryPeriod = 0.02; 		/*	2 ms, RefractoryPeriod= Resistance*Capacity	*/
const double Capacity =  1.0;
const double Resistance = RefractoryPeriod/Capacity;  
const double Amplitude= 0.03;

class Neuron /*:public Drawable*/ {
	private:	
		/*	The neuron is characterized by its membrane potential,
		 * 	number of spikes, time at which the spikes occured, the present time
		 * 	whether it is refractory or not, as well as the neurons it is linked to.	*/
		
		vector<Neuron*> linked_neurons_;
		vector<double> time_;
		double membrane_potential_;
		int spikes_;
		int present_time_;
		bool is_refractory_;
		int starttime_;
		int endtime_;
		
	
	public:
	Neuron(	vector<Neuron*> neurons_=vector<Neuron*>(0), vector<double> time = vector<double>(0.0), 
			double potential=0.0, int spikes=0,
			int present=0, bool refractory=false, int start=0, int stop=0); 
	~Neuron();
	
	/*	Getters	*/
	int getEndTime() const;
	double getMembranePotential() const;
	double getMembraneThreshold() const;
	vector<Neuron*> getLinkedNeurons() const;
	int getPresentTime() const;
	bool getRefractory() const;
	int getSpikes() const;
	int getStartTime() const;
	vector<double> getTime() const;

	
	
	/*	Setters	*/
	void setEndTime(int const& timeend);
	void setMembranePotential(double const& new_potential);
	void setPresentTime(int const& present);
	void setRefractory(bool const& is_refractory);
	void setSpikes(int const& new_spikes);
	void setStartTime(int const& timestart);
	void setTime(vector<double> const& new_time);
	
	/*	Method adding other neurons to the list of linked neurons.	*/
	void addNeurons(Neuron* neuron);
	
	/*	Method adding the time at which a spike occured to the vector.	*/
	void addTimeValue(int const& new_time_value);
	
	/*void createWindow(sf::Vector2f const& size);
	void drawPotential(sf::RenderTarget& target);*/
	
	/*	Method calculating the membrane potential depending the input current.	*/
	double MembranePotentialEquation(double const& input) const;
	
	/*	Method receiving a signal given by a presynaptic neuron.	*/
	void receive(int const& timeanddelay, double const& J);
	
	/*	Method displaying the time values of the spikes.	*/
	void showTimeValues() const;
	
	/*	Method updating the neuron's membrane potential during a 
	 * 	given time interval.	*/
	bool update(double const& input);

};

#endif
