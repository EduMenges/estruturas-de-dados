CMAKE_MINIMUM_REQUIRED(VERSION 3.25)
PROJECT(ContaBancaria VERSION 1.0)
ADD_LIBRARY(Conta STATIC conta.c)
ADD_EXECUTABLE(${CMAKE_PROJECT_NAME} main.c)
TARGET_LINK_LIBRARIES(${CMAKE_PROJECT_NAME} PRIVATE Conta)