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
        
            //read from instruction memory
            void fetch_begin();
            //update the instruction register
            void fetch_end();
            //reads the instrution register, reads operand1, operand2 from register file, decides the operation to be performed in the execute stage
            void decode();
            //executes the ALU operation based on ALUop
            void execute();
            //perform the memory operation
            void mem_access();
            //writes the resuts nacl to register file
            void write_back();

    protected:

    private:
        bool checkValidPC(unsigned int testPC);
        unsigned int inst_biset(unsigned int inst_word, unsigned int start, unsigned int end);
        bool check_data_conflict(PipelineRegister& A, PipelineRegister& B);

        bool detect_data_dependency();
        bool detect_control_dependecy();

        //Disassemble encoded instructio to instruction string
        std::string disassemble (unsigned int inst_word);
        //Convert register Number from int to string
        std::string registerstring(unsigned int a);
        //Convert integer to signed string based on bit size
        std::string sintstring (unsigned int a, int size);
        //Convert integet to hexstring
        std::string hexstring (unsigned int a);
        
};