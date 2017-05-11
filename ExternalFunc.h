//
// Created by d1md1m on 29.03.17.
//

#ifndef LAB_2_SHELL_EXTERNAL_FUNC_H
#define LAB_2_SHELL_EXTERNAL_FUNC_H

#include <cstddef>
#include <string>
#include <vector>
#include <boost/filesystem/path.hpp>
#include <boost/filesystem/operations.hpp>
#include <boost/filesystem/path.hpp>
#include <boost/range/iterator_range.hpp>

#include <queue>

#include "Env/Env.h"


#include "Shell_core/EmbeddedFunc.h"



// =====================>class OPTIONS  DECLARATION

namespace ext {

    class DefaultOptionsManager;

//takes some arguments and checks are they in valid list (or of valid kind)

    using options_validator = bool (*)(size_t, char **, DefaultOptionsManager *ref_to_owner_object);

    class DefaultOptionsManager {

    protected:

        //TODO MAKE PROTECTED WHEN SOLVE INIT PROBLEM
    public:

        string option_name_;

        std::map<string, DefaultOptionsManager *> *opts_map_;

        //default value definition
        bool noargs_allowed_ = true;

        //field for classes to initialize
        //options_validator opt_cross_valid = nullptr;

        DefaultOptionsManager(string name,
                              std::map<string, DefaultOptionsManager *> *opts_map_ =
                              new std::map<string, DefaultOptionsManager *> {});

        virtual ~DefaultOptionsManager();

        DefaultOptionsManager *getSuboptionFromMap(const string potential_arg) const;

        virtual bool suboptionsAreValid(size_t nargs, char **argv);

        virtual bool areOptionsCrossValid();

        void convertStrQueueToCharArr( std::queue<string> queue, char **arr) const;

        bool argumentlessSuboptionCheck(size_t nargs, char **argv);

        virtual bool doesSuboptionSArgumentsAreValid(DefaultOptionsManager *opt_to_check, std::queue<string> *arg_buf);

        bool doesMapContain(const string seek_this) const;
    };


// =====================>class OPTIONS DECLARATION END



//=======================> class External Funcion

    class ExternalFunc : public sh_core::EmbeddedFunc {

    private:
    protected:

        //DefaultOptionsManager *func_opts;

        ExternalFunc(const string &name,
                      sh_core::callable_function funct_to_assign,
                //DefaultOptionsManager *options_ptr,
                      string &help_msg) :
                sh_core::EmbeddedFunc(name, funct_to_assign, help_msg) {
            //this->func_opts = options_ptr;
        }


        bool isValidDirectory(size_t nargs, char **vargs);

    public:
//Overriding
        int call(size_t nargs, char **args) override;


    };

//=======================> class External Funcion END

}



#endif //LAB_2_SHELL_EXTERNAL_FUNC_H
