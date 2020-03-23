#include "APIAudio.hpp"

void lecture(){

    std::cout << "debut thread lecture" << std::endl;

    SNDFILE *inFile = nullptr;
    SNDFILE *outFile = nullptr;
    SF_INFO sfInfo;

    std::string pathIn =  "/home/vahlar/DATA/audio8kmono.wav";
    std::string pathOut = "/home/vahlar/DATA/audio8kmonoOut.wav";

    const char *in;
    in = pathIn.c_str();
    const char *out;
    out = pathOut.c_str();

    inFile = sf_open(in, SFM_READ, &sfInfo);
    if(inFile == nullptr){
        std::cout << "erreur infile lecture" << std::endl;
        exit(1);
    }
    outFile = sf_open(out, SFM_WRITE, &sfInfo);
    if(outFile == nullptr){
        std::cout << "erreur outfile lecture" << std::endl;
        exit(1);
    }

    int sampleRate = sfInfo.samplerate;
    int frameSize = sampleRate/2;
    int frameIn = 0;
    int frameOut = 0;

    float *buff = new float[frameSize];

    while ((frameIn = sf_read_float(inFile, buff, frameSize)) > 0){

        std::cout << "frameIn lecture: " << frameIn << std::endl;
        frameOut = sf_write_float(outFile, buff, frameSize);
        sf_write_sync(outFile);
        std::cout << "frameOut lecture: " << frameOut << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    delete [] buff;
}
