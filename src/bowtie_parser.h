#pragma once

#include "utils.h"

#include <vector>
#include <fstream>
#include <string>
#include <iostream>

class BowtieParser{

public:

    std::vector<std::string> referenceGenome;
    uint readLength;

    BowtieParser(std::string& referenceGenomePath);
    void getReferenceGenome(std::ifstream& referenceFile);
    std::string getReferenceSequence(const int& seqNumber, const int& position, const int& size, const bool revComp);
    void getReadsFromReference(std::string& correctedReadsFilePath, std::string& noAlign);
};
