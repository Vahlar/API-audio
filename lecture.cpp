#include "APIAudio.hpp"

void lecture(){

    std::cout << "debut thread lecture" << std::endl;
    int i = 0;

    SNDFILE *inFile = nullptr;
    SNDFILE *outFile = nullptr;
    SF_INFO sfInfoIn;
    SF_INFO sfInfoOut;

    std::string pathIn =  "/home/vahlar/DATA/audio8kmono.wav";
    std::string pathOut = "/home/vahlar/DATA/audio8kmonoOutOpus";

    const char *in;
    in = pathIn.c_str();
    const char *out;
    out = pathOut.c_str();

    inFile = sf_open(in, SFM_READ, &sfInfoIn);
    if(inFile == nullptr){
        std::cout << "erreur infile lecture" << std::endl;
        exit(1);
    }
    sfInfoOut = sfInfoIn;
    sfInfoOut.format = 2097252;

    outFile = sf_open(out, SFM_WRITE, &sfInfoOut);
    if(outFile == nullptr){
        std::cout << "erreur outfile lecture" << std::endl;
        exit(1);
    }

    int sampleRate = sfInfoIn.samplerate;
    int frameSize = sampleRate/2;
    int frameIn = 0;
    int frameOut = 0;

    float *buff = new float[frameSize];

    while ((frameIn = sf_read_float(inFile, buff, frameSize)) > 0){
        if(i == 0){
            std::cout << "lecture en cours" << std::endl;
            i++;
        }
        frameOut = sf_write_float(outFile, buff, frameSize);
        sf_write_sync(outFile);
    }
    std::cout << "fin lecture" << std::endl;
    delete [] buff;
}
