#ifndef CONSTANTS_H
#define CONSTANTS_H


//!	Constants needed for the calculations	*/
const double dt = 0.1;					/**<	The time step, 0.1 milliseconds	*/
const double MembraneThreshold =20.0; 		/**<	The membrane potential threshold, 20.0 milliVolts	*/
const double MembraneReset = 0.0; 			/**<	The membrane potential reset value, 0.0 Volts	*/
const double RefractoryPeriod = 2.0;		/**<	The refractory period, 2 milliseconds	*/
const double Tao = 20.0;
const double Capacity =  1.0;				/**< 	The capacity, 1 Faraday	*/
const double Resistance = Tao/Capacity;  /**< The resistance, in Ohms	*/
const double Amplitude= 0.1;			/**< The amplitude, 0.1 milliVolts	*/
const double Delay=1.5;//0.0015;					/**< The delay, 1.5 milliseconds	*/
const unsigned int delay_steps=static_cast<unsigned long>(floor(Delay/dt));

#endif 
