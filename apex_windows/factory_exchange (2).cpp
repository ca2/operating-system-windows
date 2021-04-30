#include "framework.h"
#include "apex/operating_system.h"
#include "apex/node/windows/_windows.h"
#include "file_os_watcher.h"
//#include "apex/node/windows/buffer.h"
//#include "apex/os/console.h"
//#include "console.h"



//namespace apex
//{
//
//
//   namespace windows
//   {
//
//
//      factory_exchange::factory_exchange()
//      {
//
//
//
//         //::windows::shell::theWindowsShell.Initialize();
//
//      }
//
//
//      factory_exchange::~factory_exchange()
//      {
//
//      }
//
//
//   } // namespace windows
//
//
//} // namespace apex


void __node_apex_factory_exchange(::factory_map * pfactorymap)
{

   create_factory < ::windows::dir_system, ::dir_system >();
   create_factory < ::windows::file_system, ::file_system >();

   create_factory < ::windows::dir_context, ::dir_context >();
   create_factory < ::windows::file_context, ::file_context >();

   //create_factory < ::windows::stdio_file, ::file::text_file >();
   //create_factory < ::windows::file, ::file::file >();
   create_factory < ::windows::os_context, ::os_context >();
   create_factory < ::windows::pipe, ::process::pipe >();
   create_factory < ::windows::process, ::process::process >();

   //create_factory < ::windows::console, ::console::console >();
   create_factory < ::windows::crypto, ::crypto::crypto >();
   create_factory < ::windows::ip_enum, ::net::ip_enum >();


   create_factory < ::windows::interprocess_communication_base, ::interprocess_communication::base >();
   create_factory < ::windows::interprocess_communication_rx, ::interprocess_communication::rx >();
   create_factory < ::windows::interprocess_communication_tx, ::interprocess_communication::tx >();
   //create_factory < ::windows::interprocess_communication, ::interprocess_communication::interprocess_communication >();


   //create_factory < ::windows::buffer, ::graphics::graphics >();
   //create_factory < ::windows::interaction_impl, ::user::interaction_impl >();

   create_factory < ::file::os_watcher, ::file::watcher >();
   create_factory < ::file::os_watch, ::file::watch >();

   //create_factory < ::windows::copydesk, ::user::copydesk >();
   ////create_factory < ::windows::shell, ::user::shell >();


}




