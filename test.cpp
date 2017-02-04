#include <bits/stdc++.h>
using namespace std;

#include "Neuron.cpp"

int Neuron::total_neurons=0;
double Neuron::learning_rate=0.4;


Neuron* a = new Neuron(1);
Neuron* b = new Neuron(1);
Neuron* bias = new Neuron(1);
Neuron* c = new Neuron(2);

bool print;

void performNeuralOperation(double input1, double input2, double output);

int main(){

    a->classifyAsInputNeuron();
    b->classifyAsInputNeuron();
    bias->classifyAsBiasNeuron();
    c->classifyAsOutputNeuron();

    a->connectForward(c);
    b->connectForward(c);
    bias->connectForward(c);

    for(int i=1; i<=1000000; i++){

        if(i%10000==0)
            print = true;
        else print = false;

        if(print)
            cout << "EPOCH " << i << " :: " << endl;

        performNeuralOperation(0.0, 0.0, 0.0);
        performNeuralOperation(0.0, 1.0, 0.0);
        performNeuralOperation(1.0, 0.0, 0.0);
        performNeuralOperation(1.0, 1.0, 1.0);

        if(print)
            cout << endl;

    }


}

void performNeuralOperation(double input1, double input2, double output){

    a->setInputVal(input1);
    b->setInputVal(input2);

    a->feedForward();
    b->feedForward();
    bias->feedForward();

    if(print)
        cout << "Expected: "<<output <<", Generated: " << c->getNeuronValue() << endl;

    c->trainOutputNeuron(output);
}
