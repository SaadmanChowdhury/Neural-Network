#ifndef __NEURON_H__
#define __NEURON_H__

#include "Neuron.h"

/* ************************************************************************************************************/
/* **************************************** *//** CONSTRUCTORS **//* ******************************************/
/* ************************************************************************************************************/

Neuron::Neuron(){
    neuronID = total_neurons;
    total_neurons++;
}

Neuron::Neuron(int layerNumer){
    //Neuron();
    this->layerNumber = layerNumber;

    neuronID = total_neurons;
    total_neurons++;

    cout << neuronID << endl;

}

/* ************************************************************************************************************/
/* ********************************** *//** CONNECTION MAKING FUNCTIONS **//* *********************************/
/* ************************************************************************************************************/

/** TO BE CALLED BY USER **/
bool Neuron::connectForward(Neuron* child){
    if(isOutputNeuron == true) // OUTPUT_NEURONS cannot link to forward neurons
        return false;

    if(child->connectBackward(this)){
        nextLayerNeurons.push_back(child);
        isOutputNeuron = false;

        double weight = generateWeight();
        weights.push_back(weight);

        cout << "["<< getID() << "] connects to [" << child->getID() << "] with weight " << weights.back() <<endl;

        return true;
    }
    else
        return false;
}

/** CALLED BY THE CLASS **/
bool Neuron::connectBackward(Neuron* parent){
    if(isInputNeuron == true) // INPUT_NEURONS cannot have any neurons behind them
        return false;

    previousLayerNeurons.push_back(parent);

    isInputNeuron = false;

    return true;
}

/* ************************************************************************************************************/
/* ************************************ *//** VALUE SETTING FUNCTIONS **//* ***********************************/
/* ************************************************************************************************************/

double Neuron::generateWeight(){
    srand (time(NULL));
    return (rand()%150 / 100.0); /*        value is open for consideration    */ /** (!) **/
    //return (rand() % (int)ceil((learning_rate*10.0))) / (learning_rate*10.0);
}

bool Neuron::classifyAsInputNeuron(){
    if(isInputNeuron == NULL){
        isInputNeuron = true;
    }

    return isInputNeuron;
}

bool Neuron::classifyAsOutputNeuron(){
    if(isOutputNeuron == NULL){
        isOutputNeuron = true;
    }

    return isOutputNeuron;
}

bool Neuron::setInputVal(double in){
    if(isInputNeuron){
        neuronValue = in;

        isReadyForCascadingOutput = true;
    }

    return isInputNeuron;
}

double Neuron::getOutputVal(){
    return neuronValue;
}


/* ************************************************************************************************************/
/* ************************************ *//** OPERATIONAL FUNCTIONS **//* *************************************/
/* ************************************************************************************************************/

bool Neuron::cascadingOutput_master_function(){
    if(isOutputNeuron != true)
        return false /* MUST BE CALLED THE OUTPUT NEURON TO INITIATE */

}

bool Neuron::backTrack_cascadingOutput(Neuron* currentNeuron){

    try{
        if(currentNeuron->isInputNeuron){
            if(isReadyForCascadingOutput == false)
                return false; /* INPUT NEURON's VALUE IS NOT SPECIFIED! */

            feedForward();

            return true;
        }
    } catch(exception &e){
        cout << endl;cout << endl;
        cout << "An *ERROR* occurred in <BACK_TRACKING> for Neuron[" << currentNeuron->getID() <<"]";
        cout << endl;cout << endl;
    }

}

bool Neuron::feedForward(){

    for(int i=0; i<nextLayerNeurons.size(); i++){
        neuronValue*nextLayerNeurons[i].weight
    }

}

double Neuron::generateOutput(double* inputs){

    double sum=0;

    for(int i=0;i<numberOfInputs;i++)
        sum += inputs[i]*weights[i];

    neuronValue = 1 / (1 + exp(sum)); // OUTPUT VALUE FOR SIGMOID FUNCTION
    return neuronValue;
}

double* Neuron::trainNeuron(double* expectedOutput, int N){
    double error;

    if(N==1){
        error = (neuronValue)*(1 - neuronValue)*(expectedOutput[0] - neuronValue);
    }

    else{
        double sum=0;
        for(int n=0;n<N;n++){
                sum += expectedOutput[n];
        }
        error = (neuronValue)*(1-neuronValue)*(sum);
    }

    adjustAllWeights(error);


}

void Neuron::adjustAllWeights(double error){
    for(int i=0;i<numberOfInputs;i++)
        weights[i] += (learning_rate * error * neuronValue);
}

/*****************************************************//*****************************************************/



/*****************************************************//*****************************************************/
/*****************************************************//*****************************************************/
/********************************************* BUGTEST UTILITY **********************************************/
/*****************************************************//*****************************************************/
/*****************************************************//*****************************************************/

// makes a replica of a neuron but does NOT increment total neuron count
Neuron::Neuron(Neuron* parentNeuron){
    neuronID = parentNeuron->getID();
    cout << "Neuron Created " <<getID() << endl;
}

int Neuron::getID(){
    return neuronID;
}

int Neuron::getNumberOfInputs(){
    return numberOfInputs;
}

#endif // __NEURON_H__
