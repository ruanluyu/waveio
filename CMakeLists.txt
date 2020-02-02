cmake_minimum_required (VERSION 2.8)
project (WaveIOProject)
aux_source_directory(. DIR_SRCS)
add_executable(waveio ${DIR_SRCS})