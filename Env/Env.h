//
// Created by d1md1m on 09.05.17.
//

#ifndef LAB_2_SHELL_ENV_H
#define LAB_2_SHELL_ENV_H

//#include "ConsoleView.h"
#include "Interpreter.h"

namespace shell{}

class Env {
public:
//    ConsoleView *cons;
    Directory* dir;
    User* usr;
    Interpreter* interp;


    Env();
    ~Env();

};

#endif //LAB_2_SHELL_ENV_H
