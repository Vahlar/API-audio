#include "lecture.hpp"

void lecture(std::chrono::system_clock::time_point *pTime0){

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
    sfInfoOut.format = (SF_FORMAT_OPUS | SF_FORMAT_OGG);

    //creation du fichier de sortie
    outFile = sf_open(out, SFM_WRITE, &sfInfoOut);
    if(outFile == nullptr){
        std::cout << "erreur outfile lecture" << std::endl;
        exit(1);
    }
    //set ogg page latency
    double latency = 1000;
    double* pLatency = &latency;
    sf_command(outFile, SFC_SET_OGG_PAGE_LATENCY_MS, pLatency, sizeof (pLatency));

    //initialisation des variables
    int sampleRate = sfInfoIn.samplerate;
    int frameSize = sampleRate/2;
    int frameIn = 0;
    int frameOut = 0;
    int totFrames = 0;

    //creation du buffer pour les datas
    float *buff = new float[frameSize];

    //lecture du fichier jusqu'à la fin
    while ((frameIn = sf_read_float(inFile, buff, frameSize)) > 0){

        if(i == 0){
            //prise tu temps t0
            *pTime0 = std::chrono::system_clock::now();
            std::cout << "lecture en cours" << std::endl;
            i++;
        }
        totFrames += frameIn;

        //on arrete la pour ce test
        if(totFrames > 16000){
            std::cout << "fin test, fin lecture" << std::endl;
            delete [] buff;
            return;
        }
        //ecriture des datas
        frameOut = sf_write_float(outFile, buff, frameSize);
        sf_write_sync(outFile);

        //toutes les 500ms on écrit 500ms d'audio
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
    std::cout << "fin lecture" << std::endl;
    delete [] buff;
}
