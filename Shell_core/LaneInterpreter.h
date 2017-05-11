//
// Created by d1md1m on 28.03.17.
//

#ifndef LAB_2_SHELL_INTERPRETER_H
#define LAB_2_SHELL_INTERPRETER_H

#include <zconf.h>
#include <wait.h>
#include "Utils/LineSplitter.h"
//#include "../EmbeddedFunc.h"
#include "iostream"
#include "../ExternLS.h"


#define  home_dir_call  "~"

namespace sh_core {

    class LaneInterpreter {
    private:

        std::map<string, EmbeddedFunc *> embedded_lib;

        //TODO make the same map for externals register

        utils::LineSplitter *splitter;

    public:
        ext::ExternLS *extern_ls_obj;

        LaneInterpreter();


        // launcher for custom modules
        int myExternLauncher(char **args) const;

        int getNumOfMyBuiltins() const;

        int myExecute(const vector<string> *const args) const;

        int processSting(string * values) const;

        ~LaneInterpreter();
        //TODO filemasks
    };

    extern LaneInterpreter *interpreter;

}


#endif //LAB_2_SHELL_INTERPRETER_H
