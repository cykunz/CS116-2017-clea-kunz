#include <iostream>
#include <cmath>
#include "Neuron.hpp"
#include <vector>
#include <fstream>
#include <cassert>

using namespace std;

Neuron::Neuron(	double input, vector<Neuron*> linked, vector<double> time, double potential, int spikes, int present, bool refractory,
				int start, int end, vector<unsigned int> b)
	: 	 input_(input), linked_neurons_(linked), time_(time), membrane_potential_(potential), spikes_(spikes), present_time_(present),
		is_refractory_(refractory), starttime_(start), endtime_(end), buffer_(b)
	{		
		/*	Initializing the buffer with value 0 at every box.	*/
			for(auto& value: buffer_)
			{ 	value=0;
			}
	}
Neuron::~Neuron()
{	/*	Empties each pointer in linked_neurons_ and then clears the table.	*/
	for(auto& neur:linked_neurons_)
	{	neur=nullptr;
		delete neur;
	}
	linked_neurons_.clear();
	
}
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

double Neuron::getInput() const
{	return input_;
}

int Neuron::getEndTime() const
{	return endtime_;
}

double Neuron::getMembranePotential() const
{	return membrane_potential_;
}

double Neuron::getMembraneThreshold() const
{	return MembraneThreshold;
}

vector<Neuron*> Neuron::getLinkedNeurons() const
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

int Neuron::getStartTime() const
{	return starttime_;
}

vector<double> Neuron::getTime() const
{	return time_;
}
/***************************************************/
/*	Setters	*/
void Neuron::setBuffer(int const& idx, int const& new_value)
{	
	/*	Sets the value to the corresponding buffer index.	*/
	buffer_[idx%(delay_steps+1)]=new_value;
}

void Neuron::setInput(double const& input)
{	input_=input;
}

void Neuron::setEndTime(int const& timeend)
{	endtime_=timeend;
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

void Neuron::setStartTime(int const& starttime)
{	starttime_=starttime;
}

void Neuron::setTime(vector<double> const& new_time)
{	time_=new_time;
}
/***************************************************/

void Neuron::addNeurons(Neuron* neuron)
{	/*	Adds the pointer to the list of neurons linked.	*/
	linked_neurons_.push_back(neuron);
}

void Neuron::addTimeValue(int const& new_time_value)
{	/*	Adds the time at which a spike occured.	*/
	time_.push_back(new_time_value*dt);
}

/*void Neuron::createWindow(sf::Vector2f const& size)
{
			sf::ContextSettings contextSettings;
			contextSettings.antialiasingLevel = 4;
			sf::VideoMode vm(size.x,size.y);
			mRenderWindow.create(vm, "Membrane Potential", sf::Style::Close, contextSettings);
	
}

void Neuron::drawPotential(sf::RenderTarget& target)
{ 		
			sf::VertexArray graph(sf::Points, getPotentials().size());
			if(not getPotentials().empty()){
				for(size_t i(0); i<getPotentials().size(); ++i)
				{	graph[i].position=sf::Vector2f(i*dt, potentials_[i]);
				}
			}
		target.draw(graph);
}
*/

double Neuron::MembranePotentialEquation(double const& input, int const& number_spikes) const
{	
	/*	Declaration of a variable to facilitate calculations.	*/
	double e(exp(-dt/(RefractoryPeriod)));
	
	/*	Equation based on the differential equation for the evolution of the neuron's membrane
	 * 	potential. This time, the number of spikes will play a role in the amount of 
	 * 	amplitude the linked neuron will receive.	*/
	return (getMembranePotential()*e)+(input*Resistance*(1-e))+(Amplitude*number_spikes);
}

void Neuron::receive(int const& clockanddelay)
{	/*	We set the buffer at idx=present time and delay to the previous value +1 (1 more spike received at 
		that time.	*/
	setBuffer(clockanddelay, getBuffer(clockanddelay)+1);
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


bool Neuron::update(double const& input)
{	ofstream file;
	double spike_time(0.0);
	
	/*	Determines if there was a spike or not during this time step.	*/
	bool spike(false);

	/*	Sets the number of spikes during that time step to the corresponding value in
	 * 	buffer at present time.	*/
	int nspikes(getBuffer(getPresentTime()));
	
	/*	If the membrane potential is higher than the threshold, there is a spike by definition.	*/
	if(getMembranePotential()>getMembraneThreshold())
	{	
		/*	Sets the spike time at the present, which is when the spike occurred.	*/
		spike_time=getPresentTime();
		addTimeValue(spike_time);
		++spikes_;
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
		 //setMembranePotential(MembraneReset);
		}
	 } else {
		 /*	If the neuron isn't refractory, then the membrane potential can be updated.	*/
		 setMembranePotential(MembranePotentialEquation(input, nspikes));
	 }
	 
	 
	 /*	We write the values of the membrane potential in the file, and close it.	*/
	 file.open("neurontext.txt", ios::out | ios::app);
	 if(file.fail())
	 {	cerr<<"File failed to open in Neuron."<<endl;
	 }
	 assert(!file.fail());
	 
	 file<<getMembranePotential()<<endl;
	 file.close();
	 
	 /*	File useful to see when buffer gets the information to increment its value.	*/
	 ofstream f;
	 f.open("buffertext.txt", ios::out | ios::app);
	 if(f.fail())
	 {	cerr<<"File failed to open in Neuron:Buffer."<<endl;
	 }
	 assert(!f.fail());
	 f<<(getPresentTime()%(delay_steps+1))<<" : "<<getBuffer(getPresentTime())<<endl;
	 f.close();
	 
	 /*	We add a time step to the present time.	*/
	 setPresentTime(getPresentTime()+1);
	
	 /*		We reset the buffer at idx=getPresentTime() to 0.	*/
	 //setBuffer(getPresentTime(), 0);
	  
	 
	 return spike;
 }
	
	
