cmake_minimum_required (VERSION 3.0.0) 
 
set (PROJECT server) 
 
project (${PROJECT} VERSION 0.1.0) 
 
set (SERVER_HEADERS 
    main.h
    Server.h)
 
set (SERVER_SOURCES 
    main.cpp
    Server.cpp) 
 
add_executable (${PROJECT} ${SERVER_HEADERS} ${SERVER_SOURCES})