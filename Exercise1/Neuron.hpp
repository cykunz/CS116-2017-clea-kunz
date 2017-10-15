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

class Neuron /*:public Drawable*/ {
	private:	
		/*	The neuron is characterized by its membrane potential,
		 * 	number of spikes, time at which the spikes occured, the present time
		 * 	and whether it is refractory or not.	*/
		
		vector<double> time_;
		vector<double> potentials_;
		double membrane_potential_;
		int spikes_;
		double present_time_;
		bool is_refractory_;
		
	
	public:
	Neuron(vector<double> time = vector<double>(0.0), vector<double> pot=vector<double>(0.0), double potential=0.0, int spikes=0, double present=0.0, bool refractory=false); 
	~Neuron()=default;
	
	/*	Getters	*/
	double getMembranePotential() const;
	double getMembraneThreshold() const;
	vector<double> getPotentials() const;
	double getPresentTime() const;
	bool getRefractory() const;
	int getSpikes() const;
	vector<double> getTime() const;

	
	
	/*	Setters	*/
	void setMembranePotential(double const& new_potential);
	void setPotentials(vector<double> const& pot);
	void setPresentTime(double const& present);
	void setRefractory(bool const& is_refractory);
	void setSpikes(int const& new_spikes);
	void setTime(vector<double> const& new_time);
	
	/*	Method adding the time at which a spike occured to the vector.	*/
	void addTimeValue(double const& new_time_value);
	
	void addPotential(double const& new_potential);
	/*void createWindow(sf::Vector2f const& size);
	void drawPotential(sf::RenderTarget& target);*/
	
	/*	Method displaying the time values of the spikes.	*/
	void showTimeValues() const;
	/*	Method calculating the membrane potential depending the input current.	*/
	double MembranePotentialEquation(double const& input) const;
	/*	Method updating the neuron's membrane potential during a 
	 * 	given time interval.	*/
    void update(double const& timeA, double const& timeB, double const& input);

};

#endif
