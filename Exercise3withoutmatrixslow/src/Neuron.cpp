#include <iostream>
#include <cmath>
#include "Neuron.hpp"
#include <vector>
#include <fstream>
#include <cassert>

using namespace std;

Neuron::Neuron(	double input, vector<unsigned int> linked, vector<unsigned int> weight, vector<double> time, 
				double potential, int spikes, int present, bool refractory, vector<unsigned int> b, bool excitatory)
	: 	 input_(input), linked_neurons_(linked), weights_(weight), time_(time), membrane_potential_(potential), spikes_(spikes), 
		present_time_(present), is_refractory_(refractory), buffer_(b), excitatory_(excitatory)
{	
			
	/*	Initializing the buffer with value 0 at every box.	*/
		buffer_.resize(delay_steps+1);
		/*for(size_t i(0);i<delay_steps+1;++i)
			{ 	buffer_.push_back(0);
			}*/
}

Neuron::~Neuron()
{}
/***************************************************/
/*	Getters	*/

int Neuron::getBuffer(int const& idx) const
{	
	/*	Returns value at idx of the buffer.	*/
	return buffer_[idx%(delay_steps+1)];
}

vector<unsigned int> Neuron::getBufferTotal() const
{	return buffer_;
}

bool Neuron::getExcitatory() const
{
	return excitatory_;
}

double Neuron::getInput() const
{	return input_;
}

double Neuron::getMembranePotential() const
{	return membrane_potential_;
}

double Neuron::getMembraneThreshold() const
{	return MembraneThreshold;
}

vector<unsigned int> Neuron::getLinkedNeurons() const
{	return linked_neurons_;
}

int Neuron::getPresentTime() const
{	return present_time_;
}

bool Neuron::getRefractory() const
{	return is_refractory_;
}

int Neuron::getSpikes() const
{	return spikes_;
}

vector<double> Neuron::getTime() const
{	return time_;
}

vector<unsigned int> Neuron::getWeights() const
{	return weights_;
}

/***************************************************/
/*	Setters	*/
void Neuron::setBuffer(int const& idx, int const& new_value)
{	
	/*	Sets the value to the corresponding buffer index.	*/
	buffer_[idx%(delay_steps+1)]=new_value;
}

void Neuron::setExcitatory(bool const& excit)
{	excitatory_=excit;
}

void Neuron::setInput(double const& input)
{	input_=input;
}

void Neuron::setMembranePotential(double const& new_potential)
{	membrane_potential_=new_potential;
}

void Neuron::setPresentTime(int const& present)
{	present_time_=present;
}

void Neuron::setRefractory(bool const& new_refractory)
{	is_refractory_=new_refractory;
}

void Neuron::setSpikes(int const& new_spikes)
{	spikes_=new_spikes;
}

void Neuron::setTime(vector<double> const& new_time)
{	time_=new_time;
}

void Neuron::setWeight(unsigned int const& idx, unsigned int const& weight)
{	weights_[idx]=weight;
}
/***************************************************/

void Neuron::addLink(unsigned int const& neuron, unsigned int const& weight)
{	/*	Adds the pointer to the list of neurons linked.	*/
	assert(neuron>0);
	assert(weight>0);
	linked_neurons_.push_back(neuron);
	weights_.push_back(weight);
}

void Neuron::addTimeValue(int const& new_time_value)
{	/*	Adds the time at which a spike occured.	*/
	time_.push_back(new_time_value*dt);
}

double Neuron::MembranePotentialEquation(double const& input, double const& amplitude) const
{	
	
	/*	Equation based on the differential equation for the evolution of the neuron's membrane
	 * 	potential. This time, the number of spikes will play a role in the amount of 
	 * 	amplitude the linked neuron will receive.	*/
	return (getMembranePotential()*C)+(input*Resistance*(1-C))+(amplitude);
}

void Neuron::receive(int const& clock, unsigned int const& number_connections)
{	/*	We set the buffer at idx=present time and delay to the previous value +1 (1 more spike received at 
		that time.	*/
	setBuffer(clock +delay_steps, getBuffer(clock + delay_steps)+number_connections);
}
int Neuron::randomSpikes() const
{	
	random_device random;
	mt19937 gen(random());
	poisson_distribution<> d(ExternalFrequency*dt);
	
	return d(gen);
}
void Neuron::showTimeValues() const
{	
	if(!time_.empty()){
		for(size_t i(1); i<time_.size()+1; ++i)
		{	cout<<"Spike n°"<<i<<"	: "<< time_[i]<<endl;
			
		}
		cout<<"Total of "<<time_.size();
			if(abs(time_.size()-1)<10e-6)
			{	cout<<" spike.";
			} else {
			cout<<" spikes.";
			} cout<<endl;
	} else { 
		cout<<"No value present."<<endl;
	}
	
	
}


bool Neuron::update()
{	ofstream file;
	int spike_time(0);
	
	/*	Determines if there was a spike or not during this time step.	*/
	bool spike(false);

	/*	Sets the number of spikes during that time step to the corresponding value in
	 * 	buffer at present time.	*/
	int nspikes(getBuffer(getPresentTime())+(randomSpikes()));
	
	/*	If the membrane potential is higher than the threshold, there is a spike by definition.	*/
	if(getMembranePotential()>getMembraneThreshold())
	{	
		/*	Sets the spike time at the present, which is when the spike occurred.	*/
		spike_time=getPresentTime();
		//addTimeValue(spike_time);
		//++spikes_;
		/*	The spike value is set to true.	*/
		 spike=true;
		 
		 /*	The neuron is then in its refractory phase, and the membrane potential is set to the
		  * reset value.	*/
		 setRefractory(true);
		 setMembranePotential(MembraneReset);
	 }
	 
	 if(getRefractory())
	 {	
		 /*	If the present time is beyond the refractory period after the spike time, 
		  * the neuron is not refractory anymore.	*/
		 if((getPresentTime()*dt)>=(spike_time*dt)+RefractoryPeriod)
		 {
		 setRefractory(false);
		}
	 } else {
		 /*	If the neuron isn't refractory, then the membrane potential can be updated.	*/
		 setMembranePotential(MembranePotentialEquation(getInput(), nspikes*Amplitude));
	 }
	 
	 
	 	
	 /*		We reset the buffer at idx=getPresentTime() to 0.	*/
	 setBuffer(getPresentTime(), 0);
	 
	 /*	We add a time step to the present time.	*/
	 setPresentTime(getPresentTime()+1);

	  
	 
	 return spike;
 }
	
	
