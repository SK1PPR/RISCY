#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include <ctime>
#include <cstring>
#include <cstdlib>

#include "../include/Global.h"
#include "../include/Core.h"
#include "../include/Memory.h"
#include "../include/PipelineRegister.h"
#include "../include/Register.h"

using namespace std;

bool pipeline = false;
int debugLevel = 1;
int MEM_CAPACITY = 100000;
char* inputFileName = NULL;
char* outputFileName = NULL;
bool specifymemout = false;
char* memoutFileName = NULL;
bool specifycontextout = false;
char* contextoutFileName = NULL;

void printhelp();

int main(int argc, char *argv[]){
    clock_t begin = clock();

    if (argc<2){
        printhelp();
        return 1;
    }

    vector<string> token;

    //Tokenize the input file
    char* p;
    for(int k = 1; k < argc; k++){
        p = strtok(argv[k], " ");
        while (p){
            token.push_back(string(p));
            p = strtok(NULL, " ");
        }
    }

    //Parse arguements
    for (int i=0; i<token.size(); i++){
        if (token[i] == "-h"){
            printhelp();
            return 1;
        }
        if(token[i]=="-pipe"){
            pipeline = true;
        }
        if (token[i]=="-input"){
            inputFileName = new char[token[i+1].size()];
            strcpy(inputFileName, token[i+1].c_str());
        }
        if (token[i]=="-output"){
            outputFileName = new char[token[i+1].size()];
            strcpy(outputFileName, token[i+1].c_str());
        }
        if (token[i]=="-mem"){
            memoutFileName = new char[token[i+1].size()];
            strcpy(memoutFileName, token[i+1].c_str());
            specifymemout=true;
        }
        if (token[i]=="-context"){
            contextoutFileName = new char[token[i+1].size()];
            strcpy(contextoutFileName, token[i+1].c_str());
            specifycontextout=true;
        }
    }

    ifstream test_input_file;
    test_input_file.open(inputFileName, ios::in);

    if (test_input_file.fail()){
        cout<<"Invalid input file"<<endl;
        printhelp();
        return 1;
    }
    else {
        test_input_file.close();
    }
    ofstream test_output_file;
    test_output_file.open(outputFileName, ios::out | ios::trunc);

    if (test_output_file.fail()) {
        cout<<"Error opening output file"<<endl;
        printhelp();
        return 1;
    } else {
        test_output_file.close();
    }

    if (specifymemout){
        ofstream test_memout_file;
        test_memout_file.open(memoutFileName, ios::out | ios::trunc);

        if (test_memout_file.fail()) {
            cout<<"Error opening output file"<<endl;
            printhelp();
            return 1;
        } else {
            test_memout_file.close();
        }
    }

    if (specifycontextout){
        ofstream test_contextout_file;
        test_contextout_file.open(contextoutFileName, ios::out | ios::trunc);

        if (test_contextout_file.fail()) {
            cout<<"Error opening output file"<<endl;
            printhelp();
            return 1;
        } else {
            test_contextout_file.close();
        }
    }

    Core simulator;
    
    simulator.load_program_memory();

    simulator.reset_proc();

    simulator.run_simplesim();

    simulator.write_memory();

    simulator.write_context();

    clock_t end = clock();
    double time = double(end - begin) / CLOCKS_PER_SEC;

    //dec makes cout in decimal
    cout<<"Running time: "<<dec<<time<<endl;

    return 0;
}

void printhelp(){
    cout<<"Help"<<endl;
    cout<<"-h : Display Help\n\n";
    cout<<"Mandatory arguements \n"<<endl;
    cout<<"-input [Input MEM File name] : Specify Input File"<<endl;
	cout<<"-output [Input MEM File name] : Specify Output File"<<endl;
	cout<<endl;
	cout<<"Optional Arguments"<<endl;
	cout<<"-pipe : Use pipeline based processor"<<endl;
	cout<<"-debug [0 | 1 | 2] : Specify debug level"<<endl;
	cout<<"-mem [Memory_OUT File name] : Specify Memory_OUT File Name"<<endl;
	cout<<"-context [Context_OUT File name] : Specify Context_OUT File Name"<<endl;

}