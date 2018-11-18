#pragma once

#ifdef DMN_EXPORTS
#define DMN_API __declspec(dllexport)
#else
#define DMN_API __declspec(dllimport)
#endif
