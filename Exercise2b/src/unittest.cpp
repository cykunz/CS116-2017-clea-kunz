#include <iostream>
#include "Neuron.hpp"
#include "Network.hpp"
#include "gtest/gtest.h"

TEST (NeuronTest, MembranePotential) {
	Neuron neuron;
	neuron.setInput(1.0);
	
	
	neuron.update(1.0);
	EXPECT_EQ(0.02*(1.0-std::exp(-0.0001/0.02)), neuron.getMembranePotential());
}
TEST(NetworkTest, NumberSpikes) {
	Neuron neuron1;
	neuron1.setInput(1.01);
	Network network;
	network.setNeurons(vector<Neuron*> {new Neuron(neuron1)});
	network.update(0, 0.3);

	EXPECT_EQ(3, network.getNeurons()[0]->getTime().size());
}

TEST(NetworkTest, Spikes) {
	Neuron neuron;
	neuron.setInput(1.01);
	Network network;
	network.setNeurons(vector<Neuron*> {new Neuron(neuron)});
	network.update(0, 0.3);
	
	EXPECT_EQ(0.1924, network.getNeurons()[0]->getTime()[0]);
	EXPECT_EQ(0.2868, network.getNeurons()[0]->getTime()[1]);
	EXPECT_EQ(0.3812, network.getNeurons()[0]->getTime()[2]);
}
	
	
int main(int argc, char **argv) 
{
		::testing::InitGoogleTest(&argc, argv);
		return RUN_ALL_TESTS();
}
