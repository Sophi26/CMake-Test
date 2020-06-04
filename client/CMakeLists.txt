cmake_minimum_required (VERSION 3.0.0) 
 
set (PROJECT client) 
 
project (${PROJECT} VERSION 0.1.0) 
 
set (CLIENT_HEADERS 
    main.h
    Client.h)
 
set (CLIENT_SOURCES 
    main.cpp
    Client.cpp) 
 
add_executable (${PROJECT} ${CLIENT_HEADERS} ${CLIENT_SOURCES})