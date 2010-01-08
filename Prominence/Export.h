#ifndef _EXPORT_H
#define _EXPORT_H

#if defined(IMPORT_PROMINENCE)
#   define DECLSPEC   __declspec(dllimport)
#else
#   define DECLSPEC   __declspec(dllexport)
#endif 

#endif