#pragma once
#include <string>
#include <string.h>
#include <iostream>
#include <sys/socket.h>
#include <cerrno>


// defines
#define BUFFER_SIZE 4096


// response
#define RESP_OK "200"




int send_file(int socket, const std::string_view &filename);
int recieve_file(int socket, const std::string_view &filename);
int send_response(int socket, const char* code, const char *message);
int receive_response(int socket, std::string_view &buffer, size_t bufferSize);


