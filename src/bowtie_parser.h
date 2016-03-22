#pragma once

#include "utils.h"

#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <bitset>
#include <regex>

class BowtieParser{

public:

    std::vector<std::string> referenceGenome;
    uint readLength;
    std::string noAlign;
    std::ofstream outputFile;

    BowtieParser(std::string& referenceGenomePath, std::string& outputFilePath, std::string& noAlign);

    // Parser for cigar string
    std::vector<uint> cigarParser(std::string& cigar);

    void getReferenceGenome(std::ifstream& referenceFile);

    std::string getReferenceSequence(uint& refNumber, uint& refPosition, uint& size, bool revComp);

    void processLine();

    void getReadsFromReference();
};
