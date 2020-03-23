#include "APIAudio.hpp"

void ecriture(){

    std::cout << "debut thread ecriture" << std::endl;

    SNDFILE *inFile = nullptr;
    SNDFILE *outFile = nullptr;
    SF_INFO sfInfoIn;
    SF_INFO sfInfoOut;

    std::string pathIn =  "/home/vahlar/DATA/audio8kmonoOut.wav";
    std::string pathOut = "/home/vahlar/DATA/audio8kmonoOutOpus";

    const char *in;
    in = pathIn.c_str();
    const char *out;
    out = pathOut.c_str();

    std::this_thread::sleep_for(std::chrono::milliseconds(500));

    inFile = sf_open(in, SFM_READ, &sfInfoIn);
    if(inFile == nullptr){
        std::cout << "erreur infile eciture" << std::endl;
        exit(1);
    }
    sfInfoOut = sfInfoIn;
    sfInfoOut.format = 2097252;

    outFile = sf_open(out, SFM_WRITE, &sfInfoOut);
    if(outFile == nullptr){
        std::cout << "erreur outfile ecriture" << std::endl;
        exit(1);
    }
    int sampleRate = sfInfoIn.samplerate;
    int frameSize = sampleRate/2;
    int frameIn = 0;
    int frameOut = 0;
    int totFrames = 0;

    float *buff = new float[frameSize];

    while ((frameIn = sf_read_float(inFile, buff, frameSize)) > -1){

        totFrames += frameIn;
        if(frameIn < frameSize){

            std::cout << "wait" << std::endl;
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
            sf_close(inFile);
            SNDFILE *inFile = nullptr;
            inFile = sf_open(in, SFM_READ, &sfInfoIn);
            sf_seek(inFile, totFrames, 0);
        }
        std::cout << "frameIn ecriture: " << frameIn << std::endl;
        frameOut = sf_write_float(outFile, buff, frameIn);
        sf_write_sync(outFile);
        std::cout << "frameOut ecriture: " << frameOut << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    delete [] buff;
}
