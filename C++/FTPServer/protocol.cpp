#include "ftp.hpp"


int send_response(int socket, const char* code, const char* message){
     char response[BUFFER_SIZE];

     snprintf(response, sizeof(response), "%s %s\n",code , message);



    if(send(socket, response, strlen(response), 0) < 0){
        std::perror("send_response");
        return -1;
    }
    return 0;


}


//int receive_response(int socket, std::string_view &buffer, size_t bufferSize){
//    ssize_t bytes_received = recv(socket, buffer, bufferSize - 1, 0);

 //   if(bytes_received < 0){
  //      std::perror("receive_response");
   //     return -1;
    //}

 //   return bytes_received;
//}
