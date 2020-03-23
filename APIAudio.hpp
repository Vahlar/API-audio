#pragma once

#include <iostream>
#include <chrono>
#include <pthread.h>
#include <thread>
#include <mutex>
#include <sndfile.h>
#include <string.h>
#include <condition_variable>

void lecture();
void ecriture();

