#pragma once

#ifdef DAEMON_EXPORTS
#define DAEMON_API __declspec(dllexport)
#else
#define DAEMON_API __declspec(dllimport)
#endif
