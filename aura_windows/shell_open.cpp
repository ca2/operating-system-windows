#include "framework.h"
#include "shell_open.h"


namespace windows
{


   shell_open::shell_open()
   {


   }


   shell_open::~shell_open()
   {


   }



   ::e_status shell_open::initialize(::object * pobject)
   {

      auto estatus = ::shell_open::initialize(pobject);

      if (!estatus)
      {

         return estatus;

      }

      return estatus;

   }


   HDDEDATA CALLBACK shell_open::DdeCallback(
      u32 uType,
      u32 uFmt,
      HCONV hconv,
      HDDEDATA hsz1,
      HDDEDATA hsz2,
      HDDEDATA hdata,
      HDDEDATA dwData1,
      HDDEDATA dwData2
   )
   {
      UNREFERENCED_PARAMETER(uFmt);
      UNREFERENCED_PARAMETER(hconv);
      UNREFERENCED_PARAMETER(dwData1);
      UNREFERENCED_PARAMETER(dwData2);
      switch (uType)
      {
      case XTYP_REGISTER:
      case XTYP_UNREGISTER:
         return (HDDEDATA) nullptr;

      case XTYP_ADVDATA:
         return (HDDEDATA)DDE_FACK;

      case XTYP_XACT_COMPLETE:
         return (HDDEDATA) nullptr;

      case XTYP_CONNECT:
      {
         
         __pointer(::windows::shell_open) pshellopen = ::get_task()->get_application();

         if (!DdeCmpStringHandles((HSZ)hsz1, pshellopen->m_hszSystemTopic))
         {
            if (!DdeCmpStringHandles((HSZ)hsz2, pshellopen->m_hszAppName))
            {
               return (HDDEDATA)true;
            }
         }
         return (HDDEDATA)false;
      }

      case XTYP_DISCONNECT:
         return (HDDEDATA) nullptr;

      case XTYP_EXECUTE:
      {
         // get the command string
         u32 dwSize = DdeGetData(
            hdata,
            nullptr,
            0,
            0);

         string str;

         dwSize = DdeGetData(
            hdata,
            (LPBYTE)str.get_string_buffer(dwSize),
            dwSize,
            0);

         str.release_string_buffer();

         //__throw(error_not_implemented);
         /*
         // execute the command
         if (!psystem->OnDDECommand( (char *)(const wchar_t *)str))
            TRACE1("Error: failed to execute DDE command '%S'.\n", str);
         */
         //
         VERIFY(DdeFreeDataHandle(hdata));
         return (HDDEDATA) nullptr;
      }

      default:
         return (HDDEDATA) nullptr;
      }
   }

   ::e_status shell_open::initialize_shell_open()
   {


      m_dwDde = 0;

      if (!DdeInitializeW(&m_dwDde,         // receives instance identifier
         (PFNCALLBACK)DdeCallback, // pointer to callback function
         //CBF_FAIL_EXECUTES |        // filter XTYPE_EXECUTE
         APPCMD_FILTERINITS, // filter notifications
         0))
      {

         m_hszAppName = DdeCreateStringHandleW(m_dwDde, L"vmpLight", 0);

         m_hszSystemTopic = DdeCreateStringHandleW(m_dwDde, L"::aura::get_system()", 0);

         DdeNameService(m_dwDde, m_hszAppName, 0, DNS_REGISTER);

      }


      return ::success;


   }


} // namespace windows