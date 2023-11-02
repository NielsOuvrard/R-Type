#include "DynLib.hpp"
#include "logger.hpp"

namespace Haze {
    DynLib::DynLib(const fs::path &libpath, int mode)
    {
        dlerror();
        _handle = {
                .ptr = dlopen(libpath.string().c_str(), mode),
                .libname = libpath.filename(),
        };
        char *dlerr = dlerror();
        if (dlerr != NULL)
            throw DLOpenException(dlerr);
    }

    DynLib::~DynLib()
    {
        dlerror();
        dlclose(_handle.ptr);
        char *dlerr = dlerror();
    }

    void *DynLib::sym(const std::string &symname) const
    {
        dlerror();
        void *symptr = dlsym(_handle.ptr, symname.c_str());
        char *dlerr = dlerror();
        if (dlerr != NULL)
            throw DLSymException(dlerr);
        return symptr;
    }

    std::string DynLib::getLibName() const
    {
        return _handle.libname;
    }
}// namespace Haze
