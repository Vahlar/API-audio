#include "APIAudio.hpp"


using namespace std;

int main(int argc, char* argv[]){

    //lancement des fonctions dans 2 threads differents
    thread t1(lecture);
    thread t2(ecriture);

    t1.join();
    t2.join();

    return 0;
}
