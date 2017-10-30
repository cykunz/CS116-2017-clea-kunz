#include <iostream>
#include "Neuron.hpp"
#include "Network.hpp"
#include "gtest/gtest.h"

TEST (NeuronTest, MembranePotential) {
	/*	We test if the membrane potential value is the correct 1 after 1 time step update.	*/
	Neuron neuron;
	neuron.setInput(1.0);
	
	
	neuron.update();
	EXPECT_EQ(20.0*(1.0-std::exp(-0.1/20.0)), neuron.getMembranePotential());
}
TEST(NeuronTest, NumberSpikesWithoutInput) {
	/*	We check if there are spikes without input (there shouldn't be).	*/
	Neuron neuron1;
	Network network;
	network.setNeurons(vector<Neuron*> {new Neuron(neuron1)});
	network.update(0, 1000);

	EXPECT_EQ(0, network.getNeurons()[0]->getTime().size());
	EXPECT_NEAR(0, network.getNeurons()[0]->getMembranePotential(), 1e-3);
}
	
TEST(NeuronTest, NumberSpikesWithInput1 /*	1	*/) {
	/*	We expect no spikes when the input is 1, and the membrane potential should tend to 20.	*/
	Neuron neuron1;
	neuron1.setInput(1.0);
	Network network;
	network.setNeurons(vector<Neuron*> {new Neuron(neuron1)});
	network.update(0, 400);
	EXPECT_EQ(0, network.getNeurons()[0]->getTime().size());
	EXPECT_GT(1e-3, std::fabs(19.999-network.getNeurons()[0]->getMembranePotential()));
}
TEST(NeuronTest, NumberSpikesWithInput2 /*	1.01	*/ ) {
	/*	We check if the spikes arrive at the correct time and if there 
	 * 	are the correct number of them.	*/
	Neuron neuron1;
	neuron1.setInput(1.01);
	Network network;
	network.setNeurons(vector<Neuron*> {new Neuron(neuron1)});
	network.update(0, 400);
	
	EXPECT_EQ(4, network.getNeurons()[0]->getTime().size());
		
	EXPECT_NEAR(92.3, network.getNeurons()[0]->getTime()[0], 92.5);
	EXPECT_NEAR(186.7, network.getNeurons()[0]->getTime()[1],186.9 );
	EXPECT_NEAR(281.1, network.getNeurons()[0]->getTime()[2], 281.3);
	EXPECT_NEAR(375.5, network.getNeurons()[0]->getTime()[3], 375.7);
}
/*TEST(NeuronTest, NegativeInput)
{	Neuron neuron;
	neuron.setInput(-1.0);
	neuron.update();
	EXPECT_EQ(-0.02*(1.0-std::exp(-0.0001/-0.02)), neuron.getMembranePotential());

}*/
TEST(NetworkTest, WithoutSpikes)
{	/*	We check that the spike does not get transmitted if the first neuron
		doesn't spike.	*/
	Neuron neuron1, neuron2;
	neuron1.setInput(1.01);
	
	for(size_t i(0);i<925+15 /*	Delay in steps	*/;++i)
	{	if(neuron1.update())
		{	neuron2.receive(i+15 /*	Delay in steps	*/);
			EXPECT_EQ(0, neuron1.getMembranePotential());
		}
		neuron2.update();
	}
	/*	The second neuron's potential should  equal the amplitude.	*/
	EXPECT_NEAR(0.09, neuron2.getMembranePotential(), 0.1); // <----- ??
}
TEST(NetworkTest, WithSpikes)
{	/*	We connect two neurons in the network, and see if the spike from neuron1 gets transmitted
		to neuron2.	*/
	Neuron neuron1, neuron2;
	neuron1.setInput(1.01);
	Network network;
	network.setNeurons(vector<Neuron*> {new Neuron(neuron1), new Neuron(neuron2)});
	network.createLink(network.getNeurons());
	
	/*	We start at the second spike of neuron1.	*/
	for(size_t i(0);i<1869+15 /*	Delay in steps	*/;++i)
	{	if(neuron1.update())
		{	
			neuron2.receive(i+15 /*	Delay in steps	*/);
			/*	The neuron1's potential should be reset to 0 since it has spiked.	*/
			EXPECT_EQ(0.0, neuron1.getMembranePotential());
		}
		neuron2.update();
	}
	/*	The neuron2 should not have spiked.	*/
	EXPECT_EQ(0, neuron2.getSpikes());
}
TEST(NetworkTest, Connections)
{	
int main(int argc, char **argv) 
{
		::testing::InitGoogleTest(&argc, argv);
		return RUN_ALL_TESTS();
}
