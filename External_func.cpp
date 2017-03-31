//
// Created by d1md1m on 29.03.17.
//


#include "External_func.h"
User * default_user;

Directory *current_directory;

Line_splitter* def_line_split;

Interpreter* default_interpreter;


ConsoleView *console;

map <string, Embedded_func*> embedded_lib;



namespace fs = boost::filesystem;



//====================BUILT-IN COMMANDS ============


//show current directory
int my_ls(size_t nargs, char **args)
{
    fs::path p = fs::current_path();
    if(fs::is_directory(p)) {
        std::cout << p << " is a directory containing:\n";

        //for (fs::path::iterator it = p.begin(); it != p.end(); ++it)
        //    cout << " " << *it << '\n';

        if (nargs>1 && args[1] == "-l" ){
            //detailed case


        }


        for (auto &entry : boost::make_iterator_range(fs::directory_iterator(p), {})) {
            if(fs::is_directory(entry.path())) {
                //printf("IS DIRECTORY\n");
                cout <<  "/" <<entry.path().filename().c_str() << "\n";
            }
            else if(fs::is_regular_file(entry.path()))
                //printf("IS FILENAME\n");
                std::cout<< entry.path().filename().c_str()  << "\n";
            //std::cout << entry << "\n";
        }

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
