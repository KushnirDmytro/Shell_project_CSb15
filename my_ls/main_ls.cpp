// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include <sys/wait.h>
#include <vector>
#include <iostream>


//========================CLASSES IMPORT==================
#include "../Env/ConsoleView.h"
#include "../Shell_core/EmbeddedFunc.h"
#include "../Shell_core/Utils/LineSplitter.h"
#include "ExternLS.h"
//====================CLASSES IMPORT END=====================


//==============================DEFINITIONS====================


using  callable_function =  int (*)(size_t, char **);

namespace sh_core {
    env::Env *environment;
}


namespace ext{
    int myLsStaticLauncher(size_t nargs = 0, char **args = nullptr);

    ext::ExternLS *LsObject; //forvard static declaration

//just activator-function
    int myLsStaticLauncher(size_t nargs, char **argv) {
        // this class is needed only to be static initializer but can instead incapsulate behaviour
        // I just decide not to get behaviour out of class in generic case

        //printf("Initialization and checks performed successfully\n");
        return 1;
    }

}


int main(int argc, char **argv)
{

    string ls_help = "PRINT HELP HERE";


    ext::LsObject = new ext::ExternLS("EXTERN_LS", ext::myLsStaticLauncher, ls_help);

    sh_core::environment =  new env::Env();

    int result = ext::LsObject->call(static_cast<size_t >(argc), argv);

    //=====================MEMORY CLEAN / SHUTDOWN==========================
    delete ext::LsObject;
    delete sh_core::environment;
    //=====================MEMORY CLEAN SHUTDOWN END==========================

    return result;

    //===================DYNAMIC INITIALISATION END======================


}
