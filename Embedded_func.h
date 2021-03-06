//
// Created by d1md1m on 27.03.17.
//

#ifndef LAB_2_SHELL_EMBEDDEDFUNC_H
#define LAB_2_SHELL_EMBEDDEDFUNC_H


#include  <string>
#include <map>
#include <cstring>


#include <boost/filesystem/operations.hpp>

#include "Directory.h"
#include "ConsoleView.h"
#include "Line_splitter.h"
#include "FileLaneIterator.h"
#include "Interpreter.h"

using namespace std;
using  callable_function =  int (*)(size_t, char **);


#define  home_dir_call  "~"


class Embedded_func{
protected:
    string name;
    char** vargs;
    size_t nargs;
    string help_info;
    callable_function func;
public:
    Embedded_func(const string &name,
                  const callable_function funct_to_assign,
                  const string &help_msg);

    int search_for_help(size_t nargs, char** &argvector);

    void output_help(const string &helpMsg);

    virtual int call(size_t nargs, char **args);

};


extern map <string, Embedded_func*> embedded_lib;

#endif //LAB_2_SHELL_EMBEDDEDFUNC_H
