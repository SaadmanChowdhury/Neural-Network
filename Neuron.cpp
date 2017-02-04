#ifndef __NEURON_H__
#define __NEURON_H__

#include "Neuron.h"

/** NOTES TO EDITORS **/
/*
    THROUGH OUT THE COURSE OF THIS CODE, THE FOLLOWING CONVENTIONS ARE FOLLOWED:
        Link* are named - connection - wherever possible
*/

/* ************************************************************************************************************/
/* **************************************** *//** CONSTRUCTORS **//* ******************************************/
/* ************************************************************************************************************/

Neuron::Neuron(){
    layerNumber = -1;

    numberOfInputs = 0;
    neuronID = total_neurons;
    total_neurons++;
    srand (time(NULL));
}

Neuron::Neuron(int layerNumer){
    //Neuron();
    srand (time(NULL));
    this->layerNumber = layerNumber;

    numberOfInputs = 0;
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

    try{

        Link* connection = child->connectBackward(this);

        linkNextLayer.push_back(connection);
        cout << "["<< connection->from->getID() << "] connects to [" << connection->to->getID() << "] with weight " << connection->weight<<endl;
        isOutputNeuron = false;

        return true;

    }catch (...){

        return false;

    }
}

/** CALLED BY THE CLASS **/
Link* Neuron::connectBackward(Neuron* parent){

    if(isInputNeuron == true)
        throw "INPUT_NEURONS cannot have any neurons behind them";

    Link* connection = new Link;
    connection-> from = parent;
    connection-> to = this;
    connection-> weight = generateRandomWeight();
    connection-> output = 0.0;
    connection-> error = 0.0;

    linkPreviousLayer.push_back(connection);
    numberOfInputs++;

    isInputNeuron = false;

    return connection;
}




/* ************************************************************************************************************/
/* ************************************ *//** VALUE SETTING FUNCTIONS **//* ***********************************/
/* ************************************************************************************************************/

double Neuron::generateRandomWeight(){

    return (rand()%200 / 100.0) - 1.0 ; /*        value is open for consideration    */ /** (!) **/
    //return 1.0;
    //return (rand() % (int)ceil((learning_rate*10.0))) / (learning_rate*10.0);
}

bool Neuron::classifyAsInputNeuron(){
    if(isInputNeuron == NULL){
        isInputNeuron = true;
        isOutputNeuron = false;
        isBiasNeuron = false;
    }

    return isInputNeuron;
}

bool Neuron::classifyAsOutputNeuron(){
    if(isOutputNeuron == NULL){
        isOutputNeuron = true;
        isInputNeuron = false;
        isBiasNeuron = false;
    }

    return isOutputNeuron;
}

bool Neuron::classifyAsBiasNeuron(){
    if(isBiasNeuron == NULL){
        isBiasNeuron = true;
        isInputNeuron = false;
        isOutputNeuron = false;
    }

    return isBiasNeuron;
}

void Neuron::setInputVal(double in){
    if(isInputNeuron){
        neuronValue = in;
    }
}

double Neuron::getNeuronValue(){

    if(isInputNeuron==true)
        return neuronValue;

    if(isBiasNeuron==true)
        return 1;

    else return DEFINE_THIS_YO( neuronValue );
}




/* ************************************************************************************************************/
/* *************************************** *//** CASCADING OUTPUT **//* ***************************************/
/* ************************************************************************************************************/

void Neuron::feedForward(){

    Neuron* neuronToBeFed;
    double valueToBeFed;
    Link* connection;

    /** Calculate the value to be fed **/
        valueToBeFed = getNeuronValue();

    /* Feed values to all forward laying neurons */
    for(int i=0; i<linkNextLayer.size(); i++){

        neuronToBeFed = linkNextLayer[i]->to;
        connection = linkNextLayer[i];

        neuronToBeFed->updateValue(connection, valueToBeFed);
    }

}

void Neuron::updateValue(Link* connection, double value){

    neuronValue -= connection->output;

    connection->output = value * connection->weight;

    neuronValue += connection->output;

}


/* ************************************************************************************************************/
/* *************************************** *//** CASCADING UPDATE **//* ***************************************/
/* ************************************************************************************************************/

void Neuron::trainOutputNeuron(double expectedOutput){

    if(isOutputNeuron==false)
        throw "TRAIN_OUTPUT_NEURON can only be used on OUTPUT_NEURONS";


    /* Calculate the ERROR generated by this neuron */
    double error;
    error = (getNeuronValue())*(1 - getNeuronValue())*(expectedOutput - getNeuronValue());

    /* Adjust neuron's backward weights depending on the error */
    double weight;
    double output;

    for(int i=0; i < linkPreviousLayer.size(); i++){

        weight = linkPreviousLayer[i]->weight;
        output = linkPreviousLayer[i]->output / weight;

        weight = weight + (output * error * learning_rate);

        linkPreviousLayer[i]->weight = weight;
    }

    /* Update the ERROR of this neuron for previous layer neurons */
    for(int i=0; i < linkPreviousLayer.size(); i++){
        linkPreviousLayer[i]->error = error;
    }

}

void Neuron::trainHiddenNeuron(){

    /* Calculate TOTAL ERROR GENERATED from previous neurons */
    double totalErrorGenerated = 0.0;
    double errorGenerated, weight;

    for(int i=0;i<linkNextLayer.size();i++){

        errorGenerated = linkNextLayer[i]->error;
        weight = linkNextLayer[i]->weight;

        totalErrorGenerated += errorGenerated * weight;
    }

    /* Calculate the ERROR for this SPECIFIC NEURON */
    double error;
    error = neuronValue * (1 - neuronValue) * totalErrorGenerated;

    /* Adjust neuron's backward weights depending on the error */
    double output;

    for(int i=0; i < linkPreviousLayer.size(); i++){

        weight = linkPreviousLayer[i]->weight;
        output = linkPreviousLayer[i]->output;

        weight = weight + (output * error * learning_rate);

        linkPreviousLayer[i]->weight = weight;
    }

    /* Update the ERROR of this neuron for previous layer neurons */
    for(int i=0; i < linkPreviousLayer.size(); i++){
        linkPreviousLayer[i]->error = error;
    }

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


/* ************************************************************************************************************/
/* *************************************** *//** **************** **//* ***************************************/
/* ************************************************************************************************************/



/*

bool isInputNeuron = NULL;
bool isOutputNeuron = NULL;
double previousValue = 0.0;


double Neuron::generateOutput(double* inputs){

    double sum=0;

    for(int i=0;i<numberOfInputs;i++)
//        sum += inputs[i]*weights[i];

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
 //   for(int i=0;i<numberOfInputs;i++)
//        weights[i] += (learning_rate * error * neuronValue);
}


bool Neuron::cascadingOutput_master_function(){
    if(isOutputNeuron != true)
        return false; // MUST BE CALLED THE OUTPUT NEURON TO INITIATE

    backTrack_cascadingOutput();

}

bool Neuron::readyForCascadingOutput(){
    if(isInputNeuron)
        return true;

    return (numberOfInputs == valuesFed);

}

bool Neuron::backTrack_cascadingOutput(){

    if(readyForCascadingOutput()){
        if(isOutputNeuron)
            return true;
        return feedForward();
    }

    bool isEverythingCool = true;

    // Recursively call all the neurons in the previous layer
    for(int i=0; i<numberOfInputs; i++){

        isEverythingCool = linkPreviousLayer[i]->from->backTrack_cascadingOutput();

        if(isEverythingCool==false)
            return false;
    }

    backTrack_cascadingOutput();

    return true;
}

bool Neuron::cascadingUpdate_master_function(){
    if(isInputNeuron != true)
        return false; // MUST BE CALLED THE OUTPUT NEURON TO INITIATE

    backTrack_cascadingUpdate();
}

bool Neuron::readyForCascadingUpdate(){

}

bool Neuron::backTrack_cascadingUpdate(){

}

bool Neuron::updateWeights(){

}



*/

#endif // __NEURON_H__
