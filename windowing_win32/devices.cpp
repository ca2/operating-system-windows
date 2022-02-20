// Created by camilo on 2022-02-20 12:22 <3ThomasBorregaardS�rensen!!
#include "framework.h"
#include "_windows.h"


namespace windows
{


   devices::devices(HWND hwnd) :
      m_hwnd(hwnd)
   {

   }


   devices::~devices()
   {

   }


   void devices::register_device_listener(device_listener * plistener, GUID guid)
      // Parameters:
      //     guid - The interface class GUID for the device interfaces. 
      // Note:
      //     RegisterDeviceNotification also allows a service handle be used,
      //     so a similar wrapper function to this one supporting that scenario
      //     could be made from this template.
   {

      if (plistener->m_hdevnotify != nullptr)
      {

         throw exception(error_wrong_state);

      }

      DEV_BROADCAST_DEVICEINTERFACE NotificationFilter{};

      NotificationFilter.dbcc_size = sizeof(DEV_BROADCAST_DEVICEINTERFACE);

      NotificationFilter.dbcc_devicetype = DBT_DEVTYP_DEVICEINTERFACE;

      NotificationFilter.dbcc_classguid = guid;

      auto hdevnotify = RegisterDeviceNotification(
         m_hwnd,                     // events recipient
         &NotificationFilter,        // type of device
         DEVICE_NOTIFY_WINDOW_HANDLE // type of recipient handle
      );

      if (NULL == hdevnotify)
      {
         
         auto lastError = ::GetLastError();
         
         ERROR("RegisterDeviceNotification");
         
         throw exception(last_error_to_status(lastError));

      }
      
      plistener->m_hdevnotify = hdevnotify;
      
      m_devicelistenera.add(plistener);
      
   }


   void devices::on_message_device_change(::message::message * pmessage)
   {

      for (auto & pdevice : m_devicelistenera)
      {

         pdevice->on_device_change(pmessage->m_wparam, pmessage->m_lparam);

      }

   }


   //void devices::on_message_device_change(::message::message * pmessage)
   //{

   //   ASSERT(pmessage->m_atom == e_message_device_change);

   //   wparam wparam = pmessage->m_wparam;

   //   lparam lparam = pmessage->m_lparam;

   //   for (auto & pdevicelistener : m_devicelistenera)
   //   {

   //      pdevicelistener->on_device_change(wparam, lparam);

   //   }

   //}

   
   devices * g_pdevices = nullptr;


} // namespace windows


void initialize_windows_devices(::windowing_win32::system_interaction * psysteminteraction)
{

   if (::is_set(::windows::g_pdevices))
   {

      return;

   }

   ::windows::g_pdevices = new ::windows::devices((HWND) psysteminteraction->m_oswindow);

   ::windows::g_pdevices->initialize(psysteminteraction);

   psysteminteraction->add_message_handler(e_message_device_change, { ::windows::g_pdevices, &::windows::devices::on_message_device_change } );
   
}


void finalize_windows_devices()
{

   if (::is_null(::windows::g_pdevices))
   {

      return;

   }

   ::acme::del(::windows::g_pdevices);

}



