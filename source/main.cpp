#include "fakeDB.h"

int main()
{
    std::string str;
    std::string instruction;
    while(true) {
       std::getline(std::cin, str);
        if (str == "exit") {
            return 0;
        }
        size_t pos = str.find(" ");
        instruction = str.substr(0, pos);
        try {
            if (instruction == "create") {
                Create c(str);
            } else if (instruction == "insert") {
                Insert i(str);
            } else if (instruction == "update") {
                Update u(str);
            } else if (instruction == "delete") {
                Delete d(str);
            } else if (instruction == "select") {
                Select s(str);
            } else {
                std::cout << "Wrong enter ․․․․try again " << std::endl;
            }
        } catch (...) {
            std::cout << "try again" << std::endl;
        }
    }
    return 0;
}
