#include "ecriture.hpp"

void ecriture(std::chrono::system_clock::time_point* pTime1, std::chrono::system_clock::time_point* pTime2){

    std::cout << "debut thread ecriture" << std::endl;
    int i = 0;
    int k = 0;

    //creation des pointeurs sndfile et de la structure info
    SNDFILE *inFile = nullptr;
    SNDFILE *outFile = nullptr;
    SF_INFO sfInfoIn;

    //path to files
    std::string pathIn =  "/home/vahlar/DATA/audio8kmonoOutOpus";
    std::string pathOut = "/home/vahlar/DATA/audio8kmonoOutOpus2";

    //conversion des string en chaine de caracteres
    const char *in;
    in = pathIn.c_str();
    const char *out;
    out = pathOut.c_str();

    //on essaie d'ouvrir le fichier jusqu'à ce qu'il soit disponible
    do{
        inFile = sf_open(in, SFM_READ, &sfInfoIn);
        std::this_thread::sleep_for(std::chrono::milliseconds(0));
    }while(inFile == nullptr);

    //prise tu temps t1
    *pTime1 = std::chrono::system_clock::now();

    //creation du fichier de sortie
    outFile = sf_open(out, SFM_WRITE, &sfInfoIn);
    if(outFile == nullptr){
        std::cout << "erreur outfile ecriture" << std::endl;
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
    std::vector<float> buff(frameSize);

    //lecture en continue du fichier
    while ((frameIn = sf_read_float(inFile, &buff[0], frameSize)) > -1){

        //prise du temps t2
        if((i == 0) && (frameIn == frameSize)){
            *pTime2 = std::chrono::system_clock::now();
            i++;
        }
        totFrames += frameIn;

        //tant qu'il n'y a pas de datas supplementaire
        while(frameIn < frameSize){

            k++;
            if(k == 1 || (k % 10) == 0){
                std::cout << "waiting..." << std::endl;
            }
            //on arrete d'attendre au bout d'un certain temps
            if(k == 10){
                std::cout << "time out, fin ecriture" << std::endl;
                return;
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(500));

            //la fermeture et reouverture de inFile permet d'eviter le crash
            sf_close(inFile);
            SNDFILE *inFile = nullptr;
            inFile = sf_open(in, SFM_READ, &sfInfoIn);

            //reprise de la lecture ou elle s'est arrete
            sf_seek(inFile, totFrames, 0);

            //on verifie si de nouvelles datas sont disponible
            frameIn = sf_read_float(inFile, &buff[0], frameSize);
        }
        if(k > 0){
            std::cout << "reprise ecriture" << std::endl;
            totFrames += frameIn;
            k = 0;
        }
        //ecriture des datas
        frameOut = sf_write_float(outFile, &buff[0], frameIn);
        sf_write_sync(outFile);
    }
}
