#include <iostream>
#include "ftp.hpp"



int main(){
    int res = send_response(8080, RESP_OK, "FTP server Ready");
    std::cout << res << '\n';
    return 0;

}


int send_file(){
    return 3 * 9;
}
