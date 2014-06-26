
#ifndef BRUKERSYSTEM_H
#define BRUKERSYSTEM_H


// Windoze related troubles (as usual)

//-----------------------------------------------------------------------------

#if defined(_WIN32)
  #ifdef creaBruker_ICUBE_EXPORT_SYMBOLS
    #define creaBruker_ICUBE_EXPORT __declspec( dllexport )
#else
    #define creaBruker_ICUBE_EXPORT __declspec( dllimport )
  #endif
  #define creaBruker_ICUBE_CDECL __cdecl
#else
  #define creaBruker_ICUBE_EXPORT
  #define creaBruker_ICUBE_CDECL
#endif // defined(_WIN32)

#ifdef __BORLANDC__
  #include <mem.h>
#endif

#endif
