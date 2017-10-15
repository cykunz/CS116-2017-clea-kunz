#include <iostream>
#include <cmath>
#include "Neuron.hpp"
#include <vector>
#include <fstream>

using namespace std;

Neuron::Neuron(	vector<Neuron*> linked, vector<double> time, double potential, int spikes, int present, bool refractory,
				int start, int end)
	: 	linked_neurons_(linked), time_(time), membrane_potential_(potential), spikes_(spikes), present_time_(present),
		is_refractory_(refractory), starttime_(start), endtime_(end)
	{}
Neuron::~Neuron()
{	for(auto neur:linked_neurons_)
	{	neur=nullptr;
		delete neur;
	}
	linked_neurons_.clear();
}
/***************************************************/
/*	Getters	*/

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
{
	linked_neurons_.push_back(neuron);
}

void Neuron::addTimeValue(int const& new_time_value)
{	time_.push_back(new_time_value*dt);
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

double Neuron::MembranePotentialEquation(double const& input) const
{	/*	Declaration of a variable to facilitate calculations.	*/
	double e(exp(-dt/(RefractoryPeriod)));

	return (getMembranePotential()*e)+(input*Resistance*(1-e));
}

void Neuron::receive(int const& timeanddelay, double const& J)
{	
	/*	We introduce the delay into the neuron.	*/
	/*	And set its membrane potential.	*/
	cout<<"Membrane Potential (linked) before receive :"<<getMembranePotential()<<endl;
	setMembranePotential((MembranePotentialEquation(0.0))+J);
	cout<<"Membrane Potential (linked) after receive "<<getMembranePotential()<<endl;
	setPresentTime(timeanddelay);
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
{

	double spike_time(0.0);
	/*	The file we want to keep membrane potential values in.	*/
	ofstream file("neurontext.txt");
	bool spike(false);

	
	if(this->getMembranePotential()>getMembraneThreshold())
	{	cout<<"Spike occurs."<<endl;
		spike_time=getPresentTime();
		addTimeValue(spike_time);
		++spikes_;
		 spike=true;
		 setRefractory(true);
		 setMembranePotential(MembraneReset);
	 }
	 if(getRefractory())
	 {	cout<<"Refractory."<<endl;
		 if((getPresentTime()*dt)>=(spike_time*dt)+RefractoryPeriod)
		 {
		 setRefractory(false);
		}
	 } else {
		 setMembranePotential(MembranePotentialEquation(input));
	 }
	 cout<<"Membrane Potential end neuronupdate: "<<getMembranePotential()<<endl;
	 file<<getMembranePotential()<<endl;
	 setPresentTime(getPresentTime()+1);
	 file.close();
	 
	 return spike;
 }
	
	
