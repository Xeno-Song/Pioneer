#pragma once

#ifdef UTILITYIO_EXPORTS
#define MIO_API __declspec(dllexport)
#else
#define MIO_API __declspec(dllimport)
#endif
