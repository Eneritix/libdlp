cmake_minimum_required(VERSION 2.8)

project(libdlp)
add_library(
    dlp
    source/writer.c
    source/reader.c
    source/comms.c
    source/crc.c
    include/libdlp/reader.h
    include/libdlp/writer.h
    include/libdlp/comms.h
    include/libdlp/crc.h
    include/libdlp/frame_header.h
    include/libdlp/libdlp.h)

target_include_directories(
    dlp
    PUBLIC
    include)
