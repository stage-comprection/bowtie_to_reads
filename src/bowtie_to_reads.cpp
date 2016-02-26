#include "bowtie_parser.h"

using namespace std;

int main (int argc, char *argv[]) {

    if (argc < 4){
        cout<< "    Error: not enough argument, exiting"<<endl;
        return -1;
    }

    string outputFilePath = argv[3];
    string noAlign = argv[2];
    //settings.pathToOutput + "temp_bowtie_corrected_" + settings.baseFileName
    string pathToReferenceGenome = argv[1];
    //settings.pathToOutput + "temp_formatted_bglue_" + settings.baseFileName;
    cout<<noAlign<<endl;
    BowtieParser parser(pathToReferenceGenome, outputFilePath, noAlign);
    parser.getReadsFromReference();


    return 0;
}



