#include "bowtie_parser.h"

using namespace std;


// Creator for object BowtieParser - stores genome in memory
BowtieParser::BowtieParser(string& referenceGenomePath, string& outputFilePath, string& noAlign){

    ifstream referenceGenomeFile;
    referenceGenomeFile.open(referenceGenomePath.c_str());
    this->getReferenceGenome(referenceGenomeFile); // Loads reference genome in memory (DB graph contigs here)

    // Opens output files
    this->outputFile.open(outputFilePath.c_str());

    this->noAlign = noAlign;

}




// Loads reference genome in memory as a vector of sequences. Identifiers are not stored because the reference file is processed before and sequence names are
// set to the order of the sequence (first sequence is >0, second is >1 ...)
void BowtieParser::getReferenceGenome(ifstream& referenceFile){

    string line;

    while(getline(referenceFile, line)){

        if (line[0] not_eq '>'){
            this->referenceGenome.push_back(line);
        }

    }

    referenceFile.close();

}




// Returns sequence from a reference based on parameters obtained in the SAM output file (reference sequence number and position on this sequence).
string BowtieParser::getReferenceSequence(const int& seqNumber, const int& position, const int& size, const bool& revComp){

    string referenceRead = this->referenceGenome[seqNumber].substr(position, size);

    if (revComp == true){ // SAM file has a flag set to 16 when reverse complement was aligned (not entirely true, maybe need to check that later)
        return reverseComplement(referenceRead);
    }

    return referenceRead;
}





// Extracts information from the alignment SAM output file, gets corrected reads sequence from the DB graph (the reference genome here) and stores these corrected
// reads in an output file.
void BowtieParser::getReadsFromReference(){

    char line[5000];
    vector<string> splittedLine;
    string correctedSequence, name;
    int readSize, refId, refPos;
    bool revComp;

    while(cin.getline(line, 5000)){

        splittedLine = split(line); // Split function is in utils, splits by '\t' by default

        name = splittedLine[0];

        /* Bowtie output organisation (only relevant fields):
         * 0. Identifier / name of the aligned read
         * 1. + if aligned on forward ref, - otherwise
         * 2. Identifier / name of the reference sequence on which the read aligns ( = '*' if no alignment)
         * 3. Starting position of the read on the reference sequence (1-based offset)
         * 4. Read sequence
         */

        if (splittedLine[2] != "*"){

            refId = stoi(splittedLine[2]);
            refPos = stoi(splittedLine[3]);

            readSize = static_cast<int>(splittedLine[4].size());

            if (splittedLine[1] == "-"){
                revComp = true;
            } else {
                revComp = false;
            }

            correctedSequence = this->getReferenceSequence(refId, refPos, readSize, revComp);

            this->outputFile << ">" + name + "\n" + correctedSequence + "\n";

        } else {

            if (this->noAlign == "T" or this->noAlign == "True" or this->noAlign == "true" or this->noAlign == "TRUE"){

                this->outputFile << ">" + name + "\n" + "not_aligned\n";

            }else {

                this->outputFile << ">" + name + "\n" + splittedLine[4] + "\n";

            }

        }

    }

    this->outputFile.close();
}
