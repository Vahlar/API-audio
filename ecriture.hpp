#pragma once

#include <iostream>
#include <chrono>
#include <pthread.h>
#include <thread>
#include <sndfile.h>
#include <string.h>
#include <vector>

void ecriture(std::chrono::system_clock::time_point* pTime1, std::chrono::system_clock::time_point* pTime2);
