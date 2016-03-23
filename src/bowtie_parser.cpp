#include "bowtie_parser.h"


// Creator for object BowtieParser - stores genome in memory
BowtieParser::BowtieParser(std::string& referenceGenomePath, std::string& outputFilePath, std::string& noAlign){

    std::ifstream referenceGenomeFile;
    referenceGenomeFile.open(referenceGenomePath.c_str());
    this->getReferenceGenome(referenceGenomeFile); // Loads reference genome in memory (DB graph contigs here)

    // Opens output files
    this->outputFile.open(outputFilePath.c_str());

    this->noAlign = noAlign;

}





// Parser for cigar string
std::vector<uint> BowtieParser::cigarParser(std::string& cigar){

    std::vector<uint> positions;
    std::regex to_match ("(\\d+)I");
    std::smatch matches;

    while (std::regex_search(cigar, matches, to_match)) {

        positions.push_back(std::stoi(matches[1]));
        cigar = matches.suffix().str();
    }

    return positions;
}





// Loads reference genome in memory as a vector of sequences. Identifiers are not stored because the reference file is processed before and sequence names are
// set to the order of the sequence (first sequence is >0, second is >1 ...)
void BowtieParser::getReferenceGenome(std::ifstream& referenceFile){

    std::string line;

    while(std::getline(referenceFile, line)){

        if (line[0] not_eq '>'){
            this->referenceGenome.push_back(line);
        }

    }

    referenceFile.close();
}




// Returns sequence from a reference based on parameters obtained in the SAM output file (reference sequence number and position on this sequence).
std::string BowtieParser::getReferenceSequence(uint& refNumber, uint& refPosition, uint& size, bool revComp){

//    std::string cigar = samLine[5];
//    std::vector<uint> insertions = this->cigarParser(cigar);
//    std::string referenceRead = "";

    std::string referenceRead = this->referenceGenome[refNumber].substr(refPosition -1, size);

    if (revComp){
        return reverseComplement(referenceRead);
    }

//    } else {

//        uint start = refPosition;

//        for (uint i=0; i<insertions.size(); ++i){

//            referenceRead += this->referenceGenome[refNumber].substr(start -1, insertions[i]);
//            start += insertions[i] + 1;

//        }

//        referenceRead += this->referenceGenome[refNumber].substr(start -1, size - referenceRead.size());

//    }

    return referenceRead;
}




// Extracts information from the alignment SAM output file, gets corrected reads sequence from the DB graph (the reference genome here) and stores these corrected
// reads in an output file.
void BowtieParser::getReadsFromReference(){

    char line[5000];
    std::vector<std::string> samLine;
    std::string correctedSequence, name;
    uint size, refNumber, refPosition;
    bool revComp;
    std::bitset<12> flag;

    while(std::cin.getline(line, 5000)){

        if (line[0] != '@'){

            samLine = split(line); // Split function is in utils, splits by '\t' by default

            name = samLine[0];

            /* Bowtie output organisation (only relevant fields) in SAM format:
             * 0. Identifier / name of the aligned read
             * 1. Flags
             * 2. Identifier / name of the reference sequence on which the read aligns ( = '*' if no alignment)
             * 3. Starting position of the read on the reference sequence (1-based offset)
             * 9. Read sequence
             */

            flag = std::bitset<12>(std::stoi(samLine[1]));

            if (is_mapped(flag)){

                refNumber = std::stoi(samLine[2]);
                refPosition = std::stoi(samLine[3]);
                size = static_cast<int>(samLine[9].size());
                revComp = is_RC(flag);

                correctedSequence = this->getReferenceSequence(refNumber, refPosition, size, revComp);

                this->outputFile << ">" + name + "\n" + correctedSequence + "\n";

            } else {

                if (this->noAlign == "T" or this->noAlign == "True" or this->noAlign == "true" or this->noAlign == "TRUE"){

                    this->outputFile << ">" + name + "\n" + "not_aligned\n";

                } else {

                    this->outputFile << ">" + name + "\n" + samLine[9] + "\n";

                }
            }
        }
    }
}
