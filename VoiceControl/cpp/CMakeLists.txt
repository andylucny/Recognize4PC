cmake_minimum_required(VERSION 2.8)
project( VoiceControl )
add_executable( VoiceControl main.cpp BoeBotControl.h BoeBotControl.cpp serial.h serial.cpp)
target_link_libraries( VoiceControl )
