cmake_minimum_required(VERSION 3.20)
project(XylarBedrock LANGUAGES C)

add_library(XylarBedrock SHARED
    src/dllmain.c
    XylarBedrock.def
    version.rc
)

set_target_properties(XylarBedrock PROPERTIES
    OUTPUT_NAME "XylarBedrock"
)