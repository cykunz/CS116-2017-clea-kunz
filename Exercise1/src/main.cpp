#include "Neuron.hpp"
#include <iostream>

using namespace std;

int main()
{	/*	The terminal enters the values for external current and simulation time.	*/
	cout<<"Enter the value of the external current: ";
	double external_current(0.0);
	cin>>external_current;
	
	double timeA(0.0);
	double timeB(0.0);
	cout<<"Enter the value of the the inferior limit of the time interval :";
	do{	cin>>timeA;
	} while(timeA<0.0);
	
	cout<<"Enter the value of the the superior limit of the time interval :";
	do{
		cin>>timeB;
	} while((timeB<=timeA)or(timeB<0.0));
	
	
	Neuron neuron1; /*	Initialization of a neuron.	*/
    neuron1.update(timeA, timeB, external_current); /*	Update of the membrane potential.	*/
	neuron1.showTimeValues();	/*	Shows the spike time values to show the evolution of the membrane potential.	*/
	
	/*	These were initially created to be able to draw a graph showing the membrane potentials and keeping
	 * 	track of them.	*/
	/*neuron1.createWindow(new sf::Vector2f(timeB, 0.04))
	neuron1.drawPotential(mRenderWindow);*/
	
	
	
	
	return 0;
}
