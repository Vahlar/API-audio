#include "lecture.hpp"
#include "ecriture.hpp"


using namespace std;

int main(int argc, char* argv[]){

    //initialisation des time points
    chrono::system_clock::time_point time0;
    chrono::system_clock::time_point time1;
    chrono::system_clock::time_point time2;

    chrono::system_clock::time_point* pTime0 = &time0;
    chrono::system_clock::time_point* pTime1 = &time1;
    chrono::system_clock::time_point* pTime2 = &time2;

    //lancement des fonctions dans 2 threads differents
    thread t1(lecture, pTime0);
    thread t2(ecriture, pTime1, pTime2);

    t1.join();
    t2.join();

    //calcul des delays
    double latence = chrono::duration_cast<chrono::microseconds>(*pTime2 - *pTime0).count();
    double delay = chrono::duration_cast<chrono::microseconds>(*pTime1 - *pTime0).count();
    cout << "temps avant disponibilité du fichier: " << (delay/1000) << "ms" << std::endl;
    cout << "latence: " << (latence/1000) << "ms" << std::endl;

    return 0;
}
