#include "Neuron.hpp"
#include <iostream>

using namespace std;

int main()
{	
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
	neuron1.update(timeA, timeB, external_current);
	neuron1.showTimeValues();
	/*neuron1.createWindow(new sf::Vector2f(timeB, 0.04))
	neuron1.drawPotential(mRenderWindow);*/
	
	
	
	
	return 0;
}
