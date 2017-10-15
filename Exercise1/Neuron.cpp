#include <iostream>
#include <cmath>
#include "Neuron.hpp"
#include <vector>
#include <fstream>

using namespace std;

Neuron::Neuron(vector<double> time, vector<double> pot, double potential, int spikes, double present, bool refractory)
	: 	time_(time), potentials_(pot), membrane_potential_(potential), spikes_(spikes), present_time_(present),
		is_refractory_(refractory)
	{}
/***************************************************/
/*	Getters	*/

double Neuron::getMembranePotential() const
{	return membrane_potential_;
}

double Neuron::getMembraneThreshold() const
{	return MembraneThreshold;
}

vector<double> Neuron::getPotentials() const
{	return potentials_;
}

double Neuron::getPresentTime() const
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
/***************************************************/
/*	Setters	*/

void Neuron::setMembranePotential(double const& new_potential)
{	membrane_potential_=new_potential;
}

void Neuron::setPotentials(vector<double> const& pot)
{	potentials_=pot;
}

void Neuron::setPresentTime(double const& present)
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
/***************************************************/
void Neuron::addTimeValue(double const& new_time_value)
{	time_.push_back(new_time_value);
}

void Neuron::addPotential(double const& new_potential)
{	potentials_.push_back(new_potential);
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


double Neuron::MembranePotentialEquation(double const& input) const
{	/*	Declaration of a variable to facilitate calculations.	*/
	double e(exp(-dt/(RefractoryPeriod)));

	return (getMembranePotential()*e) + (input*Resistance*(1-e));
}

void Neuron::update(double const& timeA, double const& timeB, double const& input)
{
	
	/*	We start the simulation at timeA.	*/
	setPresentTime(timeA);
	double spike_time(0.0);
	
	/*	The file we want to keep membrane potential values in.	*/
	ofstream file("neurontext.txt");
	
	/*	While the present time is inferior to the superior time limit...	*/
	while(getPresentTime()<timeB){
		
			/*	If the neuron is refractory, its membrane potential is reset.	*/
			 if(getRefractory())
			{	
				
				/*	If the neuron is beyond its refractory period, it isn't refractory anymore.	*/
				if(getPresentTime()>=spike_time+RefractoryPeriod)
				{
					setRefractory(false);
					setMembranePotential(MembraneReset);
				}	
					
			} else if(getMembranePotential()>=getMembraneThreshold())
			{
					/*	If the membrane potential reaches the threshold, we have to record 
					* 	the time value of the spike. By definition, the neuron is then
					* 	refractory.	*/

						spike_time=getPresentTime();
						addTimeValue(spike_time);
						setRefractory(true);
						setMembranePotential(0.0);

				
			} 
							
			/*	We write in the file the value of the current membrane potential.	*/
			file<<getMembranePotential()<<endl;
			addPotential(getMembranePotential());		
			/*	Then make the membrane potential evolve.	*/
			setMembranePotential(MembranePotentialEquation(input));
			
			/*	We make the time of simulation evolve.	*/
			setPresentTime(getPresentTime()+dt);

		}
	
	file.close();

}
