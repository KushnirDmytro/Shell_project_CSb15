// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>
#include <vector>
#include <iostream>
#include <boost/filesystem.hpp>
#include <boost/filesystem/fstream.hpp>


//========================CLASSES IMPORT==================
#include "../Env/ConsoleView.h"
#include "../Shell_core/EmbeddedFunc.h"
#include "../Shell_core/Utils/LineSplitter.h"
#include "../Shell_core/LaneInterpreter.h"
//====================CLASSES IMPORT END=====================


//==============================DEFINITIONS====================


using  callable_function =  int (*)(size_t, char **);

//============================DEFINITIONS END======================





// HOW TO CURE SPACED FILENAMES???
void cure_spaced_filenemas(size_t nargs,char* vargs[]){
    for (size_t i = 0; i < nargs; ++i){
        //TODO
        //USE BOOST::FILESYSTEM::PATH to recognise start, mid, end of directory
    }
}



vector<boost::filesystem::path> regex_match_directories(string regex){
    //TODO
    //process via iterators all possible pathes that match such expression
    vector<boost::filesystem::path> proceed_buffer;
    vector<boost::filesystem::path> directories;
    return directories;
}


//=============FUNCTIONS AND STRUCTURES DECLARATIONS END =============


namespace sh_core {
//TODO ask how to place it inside other namespace
    env::Env *environment;
    sh_core::LaneInterpreter *interpreter;
}


//=============ASSIST FUNCTIONS============


string my_read_line(void)
{
    string buffer;
    getline(std::cin,buffer);
    //buffer+=" ";
    return buffer;
}


//execuion loop
void my_loop()
{
    string line;
    vector<string> args;
    int status;


    do {
        sh_core::environment->console_->displayPromptMsg();
        line = my_read_line();
        if (strlen(line.c_str()) == 0){
            continue;
        }
        status = sh_core::interpreter->processSting(&line);
        //args = mySplitLine(line);
        //status = my_execute(args); //if 0 - finished, exited

    } while (status);
}


//=============ASSIST FUNCTIONS END============




namespace ext{
    int my_ls(size_t nargs, char **args);
    // ext::ExternLS *extern_ls_obj;

    //TODO solve it when splitting onto several EXEs
//just activator-function
    int my_ls(size_t nargs, char **argv) {
        return sh_core::interpreter->extern_ls_obj->my_ls_inner(nargs, argv);
        //my_ls_inner(nargs_, argv);
    }

}


int main(int argc, char **argv)
{
    printf("HELLO LS!!!\n");

    string ls_help = "PRINT HELP HERE";


    ext::ExternLS *LsObject = new ext::ExternLS( "EXTERN_LS", ext::my_ls , ls_help);

    printf("HELLO LSOBJECT!!!\n");

    return LsObject->call(argc, argv);

    sh_core::environment =  new env::Env();
    sh_core::interpreter = new sh_core::LaneInterpreter();


    //===================DYNAMIC INITIALISATION END======================

    // Run command loop.
    my_loop();

    // Perform any shutdown/cleanup.

    //=====================MEMORY CLEAN / SHUTDOWN==========================

    delete sh_core::interpreter;
    delete sh_core::environment;
    //=====================MEMORY CLEAN SHUTDOWN END==========================

    return EXIT_SUCCESS;
}
