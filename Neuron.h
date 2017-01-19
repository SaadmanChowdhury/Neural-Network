/*********************************************
 **         SAADMAN SHAHID CHOWDHURY        **
 **         saadmanshahid@gmail.com         **
 **               JAN 08 2017               **
 *********************************************/

 /******** 100 DAYS OF CODE: Day 001 *********/
 /******** 100 DAYS OF CODE: Day 002 *********/
 /******** 100 DAYS OF CODE: Day 003 *********/

#include <bits/stdc++.h>

#ifndef NEURON_H
#define NEURON_H

#define DEFINE_THIS_YO(X) 1/(1+exp(-1*X)) /** THRESHOLD FUNCTION **/

/** WHAT THIS CLASS DOES **/
/*
    STATIC VARIABLES:
        int total_neurons <------- MUST be initialized to ZERO by parent class
        double learning_rate <---- the neural network's learning rate

    CONSTRUCTOR:
        Neuron(int) :
                - the constructor takes in the number of inputs that this specific neuron will have

    FUNCTIONS:
        double generateOutput(double*) :
                - takes in an array of "outputs"[double] from neurons sending data to this neuron, then provides its own output[double]
                - note the weights of each input synapse are INSIDE this neuron
        double* trainNeuron(double* expectedOutput, int N)
                - user inputs the "expected output"[double] for the output neuron
                - the user inputs: N==1.

*/

class Neuron;

struct Link{
        Neuron* from;
        Neuron* to;
        double weight;
        double output;
};

class Neuron{

private:

    int neuronID;
    int numberOfInputs;
    int layerNumber;

    double neuronValue = 0.00;
    vector<Link*> linkNextLayer;
    vector<Link*> linkPreviousLayer;

    double generateRandomWeight();

    double offsetOutput(double x); /** THRESHOLD FUNCTION **/

    bool updateWeights();

public:

    static int total_neurons;
    static double learning_rate;

    Neuron();
    Neuron(int layerNubmer);

    bool classifyAsInputNeuron();
    bool classifyAsOutputNeuron();

    bool connectForward(Neuron* to);
    Link* connectBackward(Neuron* from);

    bool setInputVal(double input);
    double getOutputVal();
    bool feedForward();
/*
    double generateOutput(double* inputs);
    double* trainNeuron(double* expectedOutput, int N);
    void adjustAllWeights(double error);
*/
    /** BUGTEST UTILITY **/
    Neuron(Neuron* parentNeuron); // for copying a neuron exactly (!)[DOES NOT INCREASE COUNT](!)
    int getNumberOfInputs();
    int getID();
};


/*
Neuron object consist of the following:
    - N inputs[double]
        - Each input has a weight[double,private]
        - define number of inputs at object creation
        - initialize weight to zero
    - The neuron itself
        - summation of all weight*input
    - Threshold of output
        - there are two kinds: SIGMOID and STEP
        - the step function threshold need to be defined

After each iteration of learning, the weights of each input need to be updated based on the error.
*/


#endif // NEURON_H
