cmake_minimum_required(VERSION 3.2)
project(stream_ciphers VERSION 1.0.1)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED true)
add_executable( stream_ciphers
  main.cc
  src/salsa20.cc
  src/chacha20.cc
  src/stream_ciphers.cc
)
