#pragma once


#include "_.h"
#include "acme_windows_common/_library.h"
#include "acme/operating_system.h"
#include "acme_windows_common/_library.h"
#include "acme/operating_system/_const_console.h"
#include "acme/operating_system/console.h"
#include "acme/filesystem/filesystem/acme_directory.h"
#include "acme/filesystem/filesystem/acme_path.h"
#include <Shlobj.h>
#include <shellapi.h>
#include "acme_windows_common/comptr.h"
#include "simple_hold_handle.h"
#include "process.h"
#include <fcntl.h>
#include <VersionHelpers.h>
#include <ddeml.h>
#include <share.h>
#include <io.h>
#include <Winsvc.h>



CLASS_DECL_ACME_WINDOWS HANDLE hfile_create(
   const char * pFileName,
   ::u32                   dwDesiredAccess,
   ::u32                   dwShareMode,
   void * pSecurityAttributes,
   ::u32                   dwCreationDisposition,
   ::u32                   dwFlagsAndAttributes,
   HANDLE                  hTemplateFile
);


CLASS_DECL_ACME bool ensure_file_size_handle(HANDLE h, u64 iSize);


// namespace str
// {

//    string CLASS_DECL_ACME get_window_text_timeout(oswindow oswindow, ::duration tickTimeout = 1000);

// } // namespace str


CLASS_DECL_ACME void TRACELASTERROR();



//#include "acme_windows_common/comptr.h"
bool windows_find_is_dots(WIN32_FIND_DATAW & data);


CLASS_DECL_ACME inline i32 muldiv32(i32 a, i32 b, i32 ca)
{

   return (i32) ::MulDiv((i32)a, (i32)b, (i32)ca);

}

CLASS_DECL_ACME int_bool HFILE_set_size(HANDLE h, u64 iSize);

#ifdef WINDOWS
CLASS_DECL_ACME int_bool read_resource_as_file(const char * pszFile, HINSTANCE hinst, ::u32 nID, LPCTSTR pcszType);

#endif


CLASS_DECL_ACME TCHAR *** process_get_pargv();
CLASS_DECL_ACME TCHAR ** process_get_argv();


inline ansistring & assign(ansistring & ansistrDst, const cotaskptr < PWSTR > & pwidesz);

inline widestring & assign(widestring & widestrDst, const cotaskptr < PSTR > & pansisz);

inline ansistring & assign(ansistring & ansistrDst, const cotaskptr < PWSTR > & pwidesz);

inline widestring & assign(widestring & widestrDst, const cotaskptr < PSTR > & pansisz);


CLASS_DECL_ACME string get_command_line(HANDLE handleProcess);



#ifdef WINDOWS


CLASS_DECL_ACME FILETIME __FILETIME(const ::earth::time & time);


#endif



void __copy(payload * ppayload, const FILETIME * ptime);
void __copy(payload * ppayload, const SYSTEMTIME * ptime);





inline void __copy(payload * ppayload, const LPDWORD * lppdw)
{

   ppayload->operator = ((::u32 *)*lppdw);

}

inline void __copy(payload * ppayload, const long * plong)
{

   ppayload->operator = ((::i32)*plong);

}


inline void __copy(payload * ppayload, const DWORD * pdw)
{

   ppayload->operator = ((::u32)*pdw);

}


//inline void __copy(LPDWORD * ppdw, const payload * ppayload)
//{
//
//   *ppdw = (LPDWORD) (u32*) *ppayload;
//
//}

inline void __copy(long * plong, const payload * ppayload)
{

   *plong = (long)ppayload->i64();

}


inline void __copy(DWORD * pdw, const payload * ppayload)
{

   *pdw = ppayload->u32();

}


CLASS_DECL_ACME_WINDOWS ::file::path get_module_path(HMODULE hmodule = nullptr);
CLASS_DECL_ACME_WINDOWS string read_resource_as_string(hinstance hinst, ::u32 nID, const char * pcszType, strsize iReadAtMostByteCount = -1);
CLASS_DECL_ACME_WINDOWS const void * get_resource_pointer(HINSTANCE hinst, DWORD nID, const char* pcszType, memsize & memsize);
CLASS_DECL_ACME_WINDOWS bool read_resource_as_memory(memory & m, HINSTANCE hinst, DWORD nID, const char * pcszType, strsize iReadAtMostByteCount = -1);




inline comptr < IStream > create_istream(const memory_base & memory)
{

   return ::SHCreateMemStream(memory.get_data(), (::u32)memory.get_size());

}


CLASS_DECL_ACME bool is_valid_FILETIME(const FILETIME & ft) noexcept;


CLASS_DECL_ACME int_bool read_resource_as_file(const char * pszFile, HINSTANCE hinst, ::u32 nID, LPCTSTR pcszType);


namespace acme_windows
{


   CLASS_DECL_ACME_WINDOWS string langid_to_iso(LANGID langid);


} // namespace acme_windows




#include "acme_directory.h"
#include "acme_file.h"
#include "acme_path.h"


#include "file_find.h"
#include "registry.h"


#include "itemidlist.h"


#include "console.h"
#include "pipe.h"


#include "shared_memory.h"


#include "file_exception.h"


#include "uac_tools.h"


#include "node.h"


