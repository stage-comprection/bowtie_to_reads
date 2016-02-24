#pragma once

#include "utils.h"

#include <vector>
#include <fstream>
#include <string>
#include <iostream>
#include <thread>
#include <mutex>

class BowtieParser{

public:

    std::vector<std::string> referenceGenome;
    uint readLength;
    std::string noAlign;
    std::ofstream outputFile;

    BowtieParser(std::string& referenceGenomePath, std::string& outputFilePath, std::string& noAlign);
    void getReferenceGenome(std::ifstream& referenceFile);
    std::string getReferenceSequence(const int& seqNumber, const int& position, const int& size, const bool& revComp);
    void processLine();
    void getReadsFromReference();
};
