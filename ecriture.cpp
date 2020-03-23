#include "APIAudio.hpp"

void ecriture(){

    SNDFILE *inFile = nullptr;
    SNDFILE *outFile = nullptr;
    SF_INFO sfInfo;

    std::string pathIn =  "/home/vahlar/DATA/audio8kmonoOut.wav";
    std::string pathOut = "/home/vahlar/DATA/audio8kmonoOut2.wav";

    const char *in;
    in = pathIn.c_str();
    const char *out;
    out = pathOut.c_str();

    std::this_thread::sleep_for(std::chrono::milliseconds(1000));

    inFile = sf_open(in, SFM_READ, &sfInfo);
    if(inFile == nullptr){
        std::cout << "erreur infile eciture" << std::endl;
        exit(1);
    }


    outFile = sf_open(out, SFM_WRITE, &sfInfo);
    if(outFile == nullptr){
        std::cout << "erreur outfile ecriture" << std::endl;
        exit(1);
    }

    int sampleRate = sfInfo.samplerate;
    int frameSize = sampleRate/2;
    int frameIn = 0;
    int frameOut = 0;
    int totFrames = 0;

    float *buff = new float[frameSize];

    while ((frameIn = sf_read_raw(inFile, buff, frameSize)) > 0){

        totFrames += frameIn;
        if(frameIn < frameSize){

            std::cout << "wait" << std::endl;
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
            sf_close(inFile);
            SNDFILE *inFile = nullptr;
            inFile = sf_open(in, SFM_READ, &sfInfo);
            sf_seek(inFile, totFrames, 0);
        }
        std::cout << "frameIn ecriture: " << frameIn << std::endl;
        frameOut = sf_write_raw(outFile, buff, frameSize);
        sf_write_sync(outFile);
        std::cout << "frameOut ecriture: " << frameOut << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    delete [] buff;
}