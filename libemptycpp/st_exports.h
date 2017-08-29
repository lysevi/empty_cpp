
#ifndef EXPORT_H
#define EXPORT_H

#ifdef SHARED_EXPORTS_BUILT_AS_STATIC
#  define EXPORT
#  define EMPTYCPP_NO_EXPORT
#else
#  ifndef EXPORT
#    ifdef emptycpp_EXPORTS
        /* We are building this library */
#      define EXPORT __declspec(dllexport)
#    else
        /* We are using this library */
#      define EXPORT __declspec(dllimport)
#    endif
#  endif

#  ifndef EMPTYCPP_NO_EXPORT
#    define EMPTYCPP_NO_EXPORT 
#  endif
#endif

#ifndef EMPTYCPP_DEPRECATED
#  define EMPTYCPP_DEPRECATED __declspec(deprecated)
#endif

#ifndef EMPTYCPP_DEPRECATED_EXPORT
#  define EMPTYCPP_DEPRECATED_EXPORT EXPORT EMPTYCPP_DEPRECATED
#endif

#ifndef EMPTYCPP_DEPRECATED_NO_EXPORT
#  define EMPTYCPP_DEPRECATED_NO_EXPORT EMPTYCPP_NO_EXPORT EMPTYCPP_DEPRECATED
#endif

#if 0 /* DEFINE_NO_DEPRECATED */
#  ifndef EMPTYCPP_NO_DEPRECATED
#    define EMPTYCPP_NO_DEPRECATED
#  endif
#endif

#endif
