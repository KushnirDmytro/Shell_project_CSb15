
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <vector>
#include <iostream>
#include <boost/filesystem.hpp>
#include <boost/filesystem/fstream.hpp>
#include <pwd.h>
#include <map>
#include <fstream>
#include <cstring>


//========================CLASSES IMPORT==================

#include "ConsoleView.h"
//#include "User.h"
#include "Directory.h"
#include "Embedded_func.h"
#include "Line_splitter.h"
#include "Interpreter.h"
#include "FileLaneIterator.h"
#include "External_func.h"

//====================CLASSES IMPORT END=====================



//==============================DEFINITIONS====================

using namespace std;


#define  home_dir_call  "~"


using  callable_function =  int (*)(size_t, char **);

//============================DEFINITIONS END======================


//=============FUNCTIONS AND STRUCTURES DECLARATIONS=============

int my_ls(size_t nargs, char **args);
int my_cd(size_t nargs, char **args);
int my_pwd(size_t nargs, char **args);
int my_help(size_t nargs, char **args);
int my_exit(size_t nargs, char **args);
int my_sh(size_t nargs, char **args);

callable_function my_cd_addr = my_cd;
callable_function my_pwd_addr = my_pwd;
callable_function my_help_addr = my_help;
callable_function my_exit_addr = my_exit;
callable_function my_sh_addr = my_sh;
callable_function my_ls_addr = my_ls;


Embedded_func *my_shell_fileinterpreter;
Embedded_func *my_pwd_obj;
Embedded_func *my_cd_obj;
Embedded_func *my_help_obj;
Embedded_func *my_exit_obj;

Embedded_func *my_ls_obj;

//=============FUNCTIONS AND STRUCTURES DECLARATIONS END =============


//==================DEFAULT OBJECTS DECLARATIONS===================

User * default_user;

Directory *current_directory;

Line_splitter* def_line_split;

Interpreter* default_interpreter;


ConsoleView *console;

map <string, Embedded_func*> embedded_lib;



//=================DEFAULT OBJECTS DECLARATIONS END================




//====================BUILT-IN COMMANDS ============

#include <boost/range/iterator_range.hpp>

namespace fs = boost::filesystem;

//show current directory
int my_ls(size_t nargs, char **args)
{
    fs::path p = fs::current_path();
    if(fs::is_directory(p)) {
        std::cout << p << " is a directory containing:\n";


        //for (fs::path::iterator it = p.begin(); it != p.end(); ++it)
        //    cout << " " << *it << '\n';

        for(auto& entry : boost::make_iterator_range(fs::directory_iterator(p), {}))

        std::cout << entry << "\n";

    }
}


//show current directory
int my_pwd(size_t nargs, char **args)
{
    current_directory->refresh_path();
    printf("%s", current_directory->getActual_path().c_str());
    return 1;
}

//changes directory
int my_cd(size_t nargs, char **args)
{
    if (args[1] == NULL) { //has to have at least one arg
        fprintf(stderr, "my_Shell: expected argument to \"cd\"\n");
    } else {
        string str(args[1]);
        if (str == home_dir_call){
            if ( boost::filesystem::is_directory( default_user->getHome_dirrectory() ) ){
                boost::filesystem::current_path(default_user->getHome_dirrectory());
            }
        }
        else if (boost::filesystem::is_directory(args[1])){
            boost::filesystem::current_path(args[1]);
        }
        else{
            //TODO filesystem errors
            //boost::filesystem::filesystem_error()
            perror("\n my_Shell failed to change dir \t");
        }

    }
    current_directory->setActual_path(boost::filesystem::current_path());
    current_directory->setPath_was_changed(true);
    return 1;
}

//shows help info
int my_help(size_t nargs, char **args)
{

    printf("Write command and arguments, if needed, then press Enter\n");
    printf("To get detailed information, write <command name> -help or <command name> -h:\n");

    return 1;
}

//just exits, that is it
int my_exit(size_t nargs, char **args)
{
    printf("my_Shell says GoodBye to You and wishes a good day ;O) ");
    return 0;
}

//executes in this shell external ".msh" files
int my_sh(size_t nargs, char **args)
{
    if (nargs > 1){
        string file_path;
        file_path = current_directory->getActual_path().string();
        file_path.append("/");
        file_path.append(args[1]);
        if (boost::filesystem::is_regular_file(args[1]) ){
            FileLaneIterator *iter = new FileLaneIterator(args[1]);
            string st;
            cout << "------------FILE READING IN PROCESS------------------" << endl;
            int i =0;
            int status;
            while(iter->fileIsReady()){
                iter->getNextString(&st);
                printf("String #%d red \n", i++);
                cout << st << endl;
                // st.append(" ");
                status = default_interpreter->proceed_sting(&st);
                if (!status){
                    return 0;
                };

            }
        }
        else if (boost::filesystem::is_regular_file(file_path) ){
            FileLaneIterator *iter = new FileLaneIterator(file_path);
            string st;
            cout << "------------FILE READING IN PROCESS------------------" << endl;
            while(iter->fileIsReady()){
                iter->getNextString(&st);
                cout << st << endl;
                return default_interpreter->proceed_sting(&st);
            }
        }
        else{
            perror(args[1]);
            perror(file_path.c_str());
        }


    }
    return 1;
}


//====================BUILT-IN COMMANDS END============


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






//=============ASSIST FUNCTIONS============


string my_read_line(void)
{
    string buffer;
    getline(cin,buffer);
    //buffer+=" ";
    return buffer;
}


//execuion loop
void my_loop(void)
{
    string line;
    vector<string> args;
    int status;


    do {
        console->display_all();
        line = my_read_line();
        status = default_interpreter->proceed_sting(&line);
        //args = my_split_line(line);
        //status = my_execute(args); //if 0 - finished, exited

    } while (status);
}


//=============ASSIST FUNCTIONS END============



int main(int argc, char **argv)
{

    //===================DYNAMIC INITIALISATION ======================
    string cd_help_msg = "SOME CD HELP";
    my_cd_obj = new Embedded_func("MY_CD", my_cd, cd_help_msg );
    my_pwd_obj = new Embedded_func("MY_PWD", my_pwd, cd_help_msg );
    my_help_obj = new Embedded_func("MY_HELP", my_help, cd_help_msg );
    my_exit_obj = new Embedded_func("MY_EXIT", my_exit, cd_help_msg );
    my_ls_obj = new Embedded_func("MY_LS", my_ls, cd_help_msg );

    my_shell_fileinterpreter = new Embedded_func("MY_FILEINTERPRETER", my_sh, cd_help_msg);

    embedded_lib= {
            {"cd",   my_cd_obj},
            {"pwd",  my_pwd_obj},
            {"help", my_help_obj},
            {"exit", my_exit_obj},
            {"mysh", my_shell_fileinterpreter},
            {"ls", my_ls_obj}

    };


    default_user = new User();
    default_interpreter = new Interpreter();
    def_line_split = new Line_splitter();
    //init_user(&this_user);
    current_directory = new Directory();
    console = new ConsoleView(current_directory);

    //===================DYNAMIC INITIALISATION END======================



    // Run command loop.
    my_loop();


    // Perform any shutdown/cleanup.


    //=====================MEMORY CLEAN / SHUTDOWN==========================
    delete default_user;
    delete current_directory;
    delete console;
    //=====================MEMORY CLEAN SHUTDOWN END==========================

    return EXIT_SUCCESS;
}
