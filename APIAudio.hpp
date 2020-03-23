#pragma once

#include <iostream>
#include <chrono>
#include <pthread.h>
#include <thread>
#include <mutex>
#include <sndfile.h>
#include <string.h>
#include <condition_variable>


//class APIAudio{

//public:
//    APIAudio();
//    ~APIAudio(void);

void lecture();
void ecriture();

//};
