#include "APIAudio.hpp"


using namespace std;

int main(int argc, char* argv[]){

    //APIAudio *A = new APIAudio;

//    string pathIn =  "/home/vahlar/DATA/audio8kmono.wav";
//    string pathOut = "/home/vahlar/DATA/audio8kmonoOut.wav";
//    string pathIn2 =  "/home/vahlar/DATA/audio8kmonoOut.wav";
//    string pathOut2 = "/home/vahlar/DATA/audio8kmonoOut2.wav";

    thread t1(lecture);
    thread t2(ecriture);

    t1.join();
    t2.join();

    //delete A;
    return 0;
}
