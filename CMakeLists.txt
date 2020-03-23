cmake_minimum_required(VERSION 3.5)

project(API-Audio LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

list(APPEND CMAKE_MODULE_PATH ~/DEV/sandbox_NIM/cmakeModules)

find_package(LibSndFile REQUIRED)
find_package(Opus REQUIRED)
find_package(Ogg REQUIRED)
find_package(FLAC REQUIRED)
find_package(Vorbis REQUIRED)
find_package(VorbisEnc REQUIRED)
find_package(Speex REQUIRED)

add_executable(API-Audio
    main.cpp
    APIAudio.hpp
    lecture.cpp
    ecriture.cpp
    )
target_include_directories(API-Audio
    PUBLIC
    ${LIBSNDFILE_INCLUDE_DIRS}
    ${LIBOPUS_INCLUDE_DIRS}
    ${LIBOGG_INCLUDE_DIRS}
    ${LIBFLAC_INCLUDE_DIRS}
    ${LIBVORBIS_INCLUDE_DIRS}
    )
target_link_libraries(API-Audio
    PUBLIC
    ${LIBSNDFILE_LIBRARIES}
    Ogg::Ogg
    Opus::Opus
    Vorbis::Vorbis
    Vorbis::VorbisEnc
    FLAC::FLAC
    Speex::Speex
    pthread
    )
