// Define EXPORTED for any platform
#ifdef _WIN32
#   define EXPORTED  __declspec( dllexport )
#else
# define EXPORTED
#endif