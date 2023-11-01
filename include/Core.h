#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <string>

#include "../include/Global.h"
#include "../include/Memory.h"
#include "../include/Register.h"
#include "../include/PipelineRegister.h"

class Core{
public:
    Core();

    void reset_proc();
    void load_program_memory();
    void write_memory();
    void write_context();
    void run_simplesim();
        
    //Read from instruction memory
    void fetch_begin();
    //Update the instruction register
    void fetch_end();
    //Reads the instrution register, reads operand1, operand2 from register file, decides the operation to be performed in the execute stage
    void decode();
    //Executes the ALU operation based on ALUop
    void execute();
    //Performs the memory operation
    void mem_access();
    //Writes the results back to register file
    void write_back();

private:
    Memory MEM;
    std::ifstream input_file;
    std::ofstream output_file;

    PipelineRegister if_of;
    PipelineRegister of_ex;
    PipelineRegister ex_ma;
    PipelineRegister ma_rw;

    Register<unsigned int> PC;
    unsigned int R[16];
    bool eq,gt;
    bool isBranchTaken;
    unsigned int branchPC;


    bool checkValidPC(unsigned int testPC);
    unsigned int inst_bitset(unsigned int inst_word, unsigned int start, unsigned int end);
    bool check_data_conflict(PipelineRegister& A, PipelineRegister& B);

    bool detect_data_dependency();
    bool detect_control_dependency();

    //Disassemble encoded instructions to instruction string
    std::string disassemble (unsigned int inst_word);
    //Convert register Number from int to string
    std::string registerstring(unsigned int a);
    //Convert integer to signed string based on bit size
    static std::string sintstring (unsigned int a, int size);
    //Convert integet to hexstring
    static std::string hexstring (unsigned int a);
        
};