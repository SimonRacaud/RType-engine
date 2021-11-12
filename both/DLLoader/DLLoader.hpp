/*
** EPITECH PROJECT, 2021
** R_TYPE
** File description:
** DLLoader
*/

#ifndef DLLOADER_HPP_
#define DLLOADER_HPP_

#include <cstring>
#include <iostream>
#include <memory>
#if defined(WIN32) || defined(_WIN32) \
    || defined(__WIN32) && !defined(__CYGWIN__)
    #include <windows.h>
    #define LIBTYPE          HINSTANCE
    #define OPENLIB(libname) LoadLibrary(libname)
    #define LIBFUNC(lib, fn) GetProcAddress((lib), (fn))
    #define CLOSELIB(handle) FreeLibrary(handle)
#else
    #include <dlfcn.h>
    #define LIBTYPE void *
    #define OPENLIB(libname) \
        dlopen((libname), RTLD_LAZY | RTLD_NODELETE | RTLD_GLOBAL)
    #define LIBFUNC(lib, fn) dlsym((lib), (fn))
    #define CLOSELIB(handle) dlclose(handle)
#endif

template <typename T> class DLLoader {
  public:
    static T *getEntryPoint(std::string filePath)
    {
        LIBTYPE handle = NULL;
        T *(*instance)(void);
        T *ptr = NULL;
        // const char *error = NULL;

        handle = OPENLIB(filePath.c_str());
        // error = dlerror();
        // if (!handle) {
        //    std::cerr << "Could not retrieve handle from filepath : " <<
        //    filePath << std::endl << "Error is : " << error << std::endl;
        //    return nullptr;
        //}
        *(void **) &instance = LIBFUNC(handle, "initApi");
        // error = dlerror();
        if (!instance) {
            std::cerr << "Could not retrieve instance from handler"
                      << std::endl;
            return nullptr;
        }
        ptr = (instance) ();
        CLOSELIB(handle);
        return ptr;
    }
};

#endif /* !DLLOADER_HPP_ */