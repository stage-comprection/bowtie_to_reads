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

    // All possible flags containing "rev comp"
    int goodFlags[255] = {16, 17, 19, 23, 31, 63, 127, 255, 191, 95,
                         223, 159, 55, 119, 247, 183, 87, 215, 151, 27,
                         59, 123, 251, 187, 91, 219, 155, 51, 115, 243,
                         179, 83, 211, 147, 21, 29, 61, 125, 253, 189,
                         93, 221, 157, 53, 117, 245, 181, 85, 213, 149,
                         25, 57, 121, 249, 185, 89, 217, 153, 49, 113,
                         241, 177, 81, 209, 145, 18, 22, 30, 62, 126,
                         254, 190, 94, 222, 158, 54, 118, 246, 182, 86,
                         214, 150, 26, 58, 122, 250, 186, 90, 218, 154,
                         50, 114, 242, 178, 82, 210, 146, 20, 28, 60,
                         124, 252, 188, 92, 220, 156, 52, 116,  244, 180,
                         84, 212, 148, 24, 56, 120, 248, 184, 88, 216,
                         152, 48, 112, 240, 176, 80, 208, 144, 17, 19,
                         23, 31, 63, 127, 255, 191, 95, 223, 159, 55,
                         119, 247, 183, 87, 215, 151, 27, 59, 123, 251,
                         187, 91, 219, 155, 51, 115, 243, 179, 83, 211,
                         147, 21, 29, 61, 125, 253, 189, 93, 221, 157,
                         53, 117, 245, 181, 85, 213, 149, 25, 57, 121,
                         249, 185, 89, 217, 153, 49, 113, 241, 177, 81,
                         209, 145, 18, 22, 30, 62, 126, 254, 190, 94,
                         222, 158, 54, 118, 246, 182, 86, 214, 150, 26,
                         58, 122, 250, 186, 90, 218, 154, 50, 114, 242,
                         178, 82, 210, 146, 20, 28, 60, 124, 252, 188,
                         92, 220, 156, 52, 116, 244, 180, 84, 212, 148, 24,
                         56, 120, 248, 184, 88, 216, 152, 48, 112, 240,
                         176, 80, 208, 144};

    BowtieParser(std::string& referenceGenomePath, std::string& outputFilePath, std::string& noAlign);
    void getReferenceGenome(std::ifstream& referenceFile);
    std::string getReferenceSequence(const int& seqNumber, const int& position, const int& size, const bool& revComp);
    void processLine();
    void getReadsFromReference();
};
