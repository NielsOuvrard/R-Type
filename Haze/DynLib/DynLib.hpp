#pragma once

#include <dlfcn.h>
#include <iostream>

#include <filesystem>

namespace fs = std::filesystem;

namespace Haze {

    class DynLib {
    public:
        class DynLibException : public std::runtime_error {
            using std::runtime_error::runtime_error;
        };

    private:
        class DLOpenException : public DynLibException {
            using DynLibException::DynLibException;
        };

        class DLSymException : public DynLibException {
            using DynLibException::DynLibException;
        };

        typedef struct handle {
            void *ptr;
            std::string libname;
        } handle_t;

        handle_t _handle{};

    public:
        DynLib(const fs::path &libpath, int mode = RTLD_LAZY);
        ~DynLib();

        void *sym(const std::string &symname) const;
        std::string getLibName() const;
    };

};// namespace Haze
