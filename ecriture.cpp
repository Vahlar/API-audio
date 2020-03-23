#include "APIAudio.hpp"

void ecriture(){

    std::cout << "debut thread ecriture" << std::endl;
    int k = 0;

    SNDFILE *inFile = nullptr;
    SNDFILE *outFile = nullptr;
    SF_INFO sfInfoIn;

    std::string pathIn =  "/home/vahlar/DATA/audio8kmonoOutOpus";
    std::string pathOut = "/home/vahlar/DATA/audio8kmonoOutOpus2";

    const char *in;
    in = pathIn.c_str();
    const char *out;
    out = pathOut.c_str();

    auto start = std::chrono::system_clock::now();
    do{
        inFile = sf_open(in, SFM_READ, &sfInfoIn);
    }while(inFile == nullptr);
    auto end = std::chrono::system_clock::now();
    std::chrono::duration<double> latence = end - start;

//    if(inFile == nullptr){
//        std::cout << "erreur infile eciture" << std::endl;
//        exit(1);
//    }

    outFile = sf_open(out, SFM_WRITE, &sfInfoIn);
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

    std::cout << "debut ecriture, latence: " << (latence.count())*1000 << "ms" << std::endl;

    while ((frameIn = sf_read_float(inFile, buff, frameSize)) > -1){

        totFrames += frameIn;
        while(frameIn < frameSize){

            k = 1;
            std::cout << "waiting..." << std::endl;
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
            sf_close(inFile);
            SNDFILE *inFile = nullptr;
            inFile = sf_open(in, SFM_READ, &sfInfoIn);
            sf_seek(inFile, totFrames, 0);
            frameIn = sf_read_float(inFile, buff, frameSize);
        }
        if(k == 1){
            std::cout << "reprise ecriture" << std::endl;
            k = 0;
        }
        frameOut = sf_write_float(outFile, buff, frameIn);
        sf_write_sync(outFile);
    }
    std::cout << "fin ecriture" << std::endl;
    delete [] buff;
}
