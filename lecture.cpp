#include "APIAudio.hpp"

void lecture(){

    std::cout << "debut thread lecture" << std::endl;
    int i = 0;

    //creation des pointeurs sndfile et des structures infos
    SNDFILE *inFile = nullptr;
    SNDFILE *outFile = nullptr;
    SF_INFO sfInfoIn;
    SF_INFO sfInfoOut;

    //path to files
    std::string pathIn =  "/home/vahlar/DATA/audio8kmono.wav";
    std::string pathOut = "/home/vahlar/DATA/audio8kmonoOutOpus";

    //conversion des string en chaine de caracteres
    const char *in;
    in = pathIn.c_str();
    const char *out;
    out = pathOut.c_str();

    //creation du fichier d'entre
    inFile = sf_open(in, SFM_READ, &sfInfoIn);
    if(inFile == nullptr){
        std::cout << "erreur infile lecture" << std::endl;
        exit(1);
    }

    //le fichier de sortie garde les même proprietes
    sfInfoOut = sfInfoIn;

    //le format d'ecriture quand à lui est ogg opus
    sfInfoOut.format = 2097252;

    //creation du fichier de sortie
    outFile = sf_open(out, SFM_WRITE, &sfInfoOut);
    if(outFile == nullptr){
        std::cout << "erreur outfile lecture" << std::endl;
        exit(1);
    }
    //initialisation des variables
    int sampleRate = sfInfoIn.samplerate;
    int frameSize = sampleRate/2;
    int frameIn = 0;
    int frameOut = 0;

    //creation du buffer pour les datas
    float *buff = new float[frameSize];

    //lecture du fichier jusqu'à la fin
    while ((frameIn = sf_read_float(inFile, buff, frameSize)) > 0){
        if(i == 0){
            std::cout << "lecture en cours" << std::endl;
            i++;
        }
        //ecriture des datas
        frameOut = sf_write_float(outFile, buff, frameSize);
        sf_write_sync(outFile);
    }
    std::cout << "fin lecture" << std::endl;
    delete [] buff;
}
