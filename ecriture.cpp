#include "APIAudio.hpp"

void ecriture(){

    std::cout << "debut thread ecriture" << std::endl;
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

    //calcule du temps avant que infFile soit disponible
    auto start = std::chrono::system_clock::now();
    do{
        inFile = sf_open(in, SFM_READ, &sfInfoIn);
    }while(inFile == nullptr);
    auto end = std::chrono::system_clock::now();
    std::chrono::duration<double> latence = end - start;

    //creation du fichier de sortie
    outFile = sf_open(out, SFM_WRITE, &sfInfoIn);
    if(outFile == nullptr){
        std::cout << "erreur outfile ecriture" << std::endl;
        exit(1);
    }
    //initialisation des variables
    int sampleRate = sfInfoIn.samplerate;
    int frameSize = sampleRate/2;
    int frameIn = 0;
    int frameOut = 0;
    int totFrames = 0;

    //creation du buffer pour les datas
    float *buff = new float[frameSize];

    std::cout << "debut ecriture, latence: " << (latence.count())*1000 << "ms" << std::endl;

    //lecture en continue du fichier
    while ((frameIn = sf_read_float(inFile, buff, frameSize)) > -1){

        totFrames += frameIn;

        //tant qu'il n'y a pas de datas supplementaire
        while(frameIn < frameSize){

            k++;
            if(k == 1 || (k % 10) == 0){
                std::cout << "waiting..." << std::endl;
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(500));

            //la fermeture et reouverture de inFile permet d'eviter le crash
            sf_close(inFile);
            SNDFILE *inFile = nullptr;
            inFile = sf_open(in, SFM_READ, &sfInfoIn);

            //reprise de la lecture ou elle s'est arrete
            sf_seek(inFile, totFrames, 0);

            //on verifie si de nouvelles datas sont disponible
            frameIn = sf_read_float(inFile, buff, frameSize);
        }
        if(k > 0){
            std::cout << "reprise ecriture" << std::endl;
            k = 0;
        }
        //ecriture des datas
        frameOut = sf_write_float(outFile, buff, frameIn);
        sf_write_sync(outFile);
    }
    std::cout << "fin ecriture" << std::endl;
    delete [] buff;
}
