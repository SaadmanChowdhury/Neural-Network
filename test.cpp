#include <bits/stdc++.h>
using namespace std;

#include "Neuron.cpp"

int Neuron::total_neurons=0;
double Neuron::learning_rate=0.2;


Neuron* a = new Neuron(1);
Neuron* b = new Neuron(1);
Neuron* c = new Neuron(2);
void performNeuralOperation(double input1, double input2, double output);

int main(){

    a->classifyAsInputNeuron();
    b->classifyAsInputNeuron();
    c->classifyAsOutputNeuron();

    a->connectForward(c);
    b->connectForward(c);

    for(int i=0; i<50; i++){

        cout << "EPOCH " << i << " :: " << endl;

        performNeuralOperation(0.0, 0.0, 0.0);
        performNeuralOperation(0.0, 1.0, 0.0);
        performNeuralOperation(1.0, 0.0, 0.0);
        performNeuralOperation(1.0, 1.0, 1.0);

        cout << endl;

    }


}

void performNeuralOperation(double input1, double input2, double output){

    a->setInputVal(input1);
    b->setInputVal(input2);

    a->feedForward();
    b->feedForward();

    cout << "Expected: "<<output <<", Generated: " << c->getNeuronValue() << endl;

    c->trainOutputNeuron(output);
}
