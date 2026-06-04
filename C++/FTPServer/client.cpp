#include "ftp.hpp"



void print_help(){
    std::cout << "\nAvailable commands: \n" ;
    std::cout << "  ls         - List server files\n";
    std::cout << "  lss        - List Local files\n";
    std::cout << "  get <file> - Download file from server\n";
    std::cout << "  put <file> - upload file to server\n";
    std::cout << "  help       - Show this help\n";
    std::cout << "  quit       - Exit client\n";
}


int main(int argc, char* argv[]){

    print_help();

    std::string input{};
    while(true){
        std::cout << "play> ";
        std::getline(std::cin , input);


        if(input == "exit"){
            break;
        }


    }
    return 0;
}
