#include "framework.h"
#include "apex/operating_system.h"
#include "apex/platform/app_core.h"
#include "copydesk.h"


namespace windowing_win32
{


   copydesk::copydesk()
   {

      //m_hwnd = nullptr;

      defer_create_mutex();

   }


   copydesk::~copydesk()
   {

      //::DestroyWindow(m_hwnd);

   }

   void copydesk::OnClipboardUpdate()
   {

      synchronization_lock synchronizationlock(mutex());

      m_cFileCount = -1;
      m_iPriorityTextFormat = -2;
      m_iFilea = -1;
      m_iText = -1;
      m_iDib = -1;

   }


   void copydesk::_001OnClipboardUpdate(::message::message * pmessage)
   {

      //if(message == WM_CLIPBOARDUPDATE)
      //{

        // LONG_PTR l = ::GetWindowLongPtrA(hwnd, GWLP_USERDATA);

         //copydesk * pdesk = (copydesk *) l;

         //if(pdesk != nullptr)
         //{

            OnClipboardUpdate();

         //}

//      }

  //    return DefWindowProc(hwnd, message, wparam, lparam);


   }

   
   void copydesk::install_message_routing(::channel * pchannel)
   {

      ::user::message_window::install_message_routing(pchannel);

      MESSAGE_LINK(WM_CLIPBOARDUPDATE, pchannel, this, &copydesk::_001OnClipboardUpdate);

   }


   ::e_status copydesk::initialize(::layered * pobjectContext)
   {

      auto estatus = ::user::copydesk::initialize(pobjectContext);

      if (!estatus)
      {

         return estatus;

      }

      synchronization_lock synchronizationlock(mutex());

      //WNDCLASS wndcls = {};

      //wstring strClass = L"ca2_copydesk_windows_message_queue";

      //HINSTANCE hinstance = System->m_hinstance;

      //if (!GetClassInfoW(hinstance, strClass, &wndcls))
      //{

      //   wndcls.style = 0;
      //   wndcls.lpfnWndProc = &copydesk::WindowProc;

      //   wndcls.cbClsExtra = 0;
      //   wndcls.cbWndExtra = 0;
      //   wndcls.hInstance = System->m_hinstance;
      //   wndcls.hIcon = nullptr;
      //   wndcls.hCursor = nullptr;
      //   wndcls.hbrBackground = nullptr;
      //   wndcls.lpszMenuName = nullptr;

      //   wndcls.lpszClassName = strClass;


      //   if (!::RegisterClass(&wndcls))
      //   {

      //      return false;

      //   }

      //}

      if(!create_message_queue("::windows::copydesk"))
      {

      //m_hwnd = ::CreateWindowEx(0, strClass, 0, 0, 0, 0, 0, 0, HWND_MESSAGE, 0, 0, nullptr);

      //if (m_hwnd == nullptr)
      //{

         return false;

      }

      //::SetWindowLongPtr(m_hwnd, GWLP_USERDATA, (LONG_PTR) this);

      if(!::AddClipboardFormatListener((HWND)get_oswindow()))
      {

         finalize();

         return false;

      }

      OnClipboardUpdate();

      return true;

   }


   void copydesk::finalize()
   {

      ::user::copydesk::finalize();

      ::user::message_window::finalize();

   }


   void copydesk::_001OnDestroy(::message::message * pmessage)
   {

      bool bOk1 = ::RemoveClipboardFormatListener((HWND)get_oswindow());

      //bool bOk2 = ::DestroyWindow(m_hwnd);

      //::user::copydesk::finalize();

   }


   bool copydesk::_has_filea()
   {

      return _get_file_count();

   }


   HGLOBAL copydesk::hglobal_get_filea(const ::file::patha & patha)
   {

      strsize iLen = 0;

      for (i32 i = 0; i < patha.get_size(); i++)
      {

         iLen += ::str::international::utf8_to_unicode_count(patha[i]) + 1;

      }

      HGLOBAL hglb = ::GlobalAlloc(GMEM_MOVEABLE, (SIZE_T) (sizeof(DROPFILES) + (iLen + 1) * sizeof(WCHAR)));
      LPDROPFILES pDropFiles = (LPDROPFILES) ::GlobalLock(hglb);
      pDropFiles->pFiles = sizeof(DROPFILES);
      pDropFiles->pt.x = 0;
      pDropFiles->pt.y = 0;
      pDropFiles->fNC = true;
      pDropFiles->fWide = true;

      char * psz = (char *)pDropFiles;

      psz += pDropFiles->pFiles;

      unichar * pwsz = (unichar *)psz;


      for (i32 i = 0; i < patha.get_size(); i++)
      {

         ::count c = ::str::international::utf8_to_unicode_count(patha[i]) + 1;

         ::str::international::utf8_to_unicode(pwsz, c, patha[i]);


         pwsz += c;


      }

      *pwsz = L'\0';


      ::GlobalUnlock(hglb);

      return hglb;

   }


   HGLOBAL copydesk::hglobal_get_wide_text(const string & str)
   {

      ::count c = ::str::international::utf8_to_unicode_count(str) + 1;
      HGLOBAL hglb = ::GlobalAlloc(GMEM_MOVEABLE, (SIZE_T) (c * sizeof(WCHAR)));
      unichar * pwsz = (unichar *) ::GlobalLock(hglb);

      ::str::international::utf8_to_unicode(pwsz, c, str);

      ::GlobalUnlock(hglb);

      return hglb;

   }


   HGLOBAL copydesk::hglobal_get_utf8_text(const string & str)
   {

      HGLOBAL hglb = ::GlobalAlloc(GMEM_MOVEABLE, (SIZE_T) (sizeof(char) * (str.length() + 1)));
      char * psz = (char *) ::GlobalLock(hglb);

      strcpy(psz, str);

      ::GlobalUnlock(hglb);

      return hglb;

   }


   HGLOBAL copydesk::hglobal_get_image(const ::image * pimage)
   {

      ::u32 dwWidth, dwHeight;
      BITMAPINFOHEADER bi;
      hcursor hAlphaCursor = nullptr;

      dwWidth = pimage->width();
      dwHeight = pimage->height();

      ZeroMemory(&bi, sizeof(BITMAPINFOHEADER));
      bi.biSize = sizeof(BITMAPINFOHEADER);
      bi.biWidth = dwWidth;
      bi.biHeight = -(::i32)dwHeight;
      bi.biPlanes = 1;
      bi.biBitCount = 32;
      bi.biCompression = BI_RGB;
      bi.biSizeImage = pimage->scan_size() * pimage->height();

      HGLOBAL hglb = GlobalAlloc(GMEM_MOVEABLE, sizeof(bi) + pimage->scan_size() * pimage->height());

      if (hglb == nullptr)
      {

         return nullptr;

      }

      byte * p = (byte *) ::GlobalLock(hglb);


      pimage->map();

      ::memcpy_dup(p, &bi, sizeof(bi));

      ::memcpy_dup(p + sizeof(bi), pimage->get_data(), pimage->scan_size() * pimage->height());

      GlobalUnlock(hglb);

      return hglb;

   }


   int copydesk::_get_priority_text_format()
   {

      if(m_iPriorityTextFormat == -2)
      {

         ::u32 iCfShellInternetUrlW = ::RegisterClipboardFormat(CFSTR_INETURLW);

         ::u32 uaFormatPriorityList[] =
         {
            iCfShellInternetUrlW,
            CF_UNICODETEXT,
            CF_TEXT,
         };

         m_iPriorityTextFormat = ::GetPriorityClipboardFormat(uaFormatPriorityList, ARRAYSIZE(uaFormatPriorityList));

      }

      return m_iPriorityTextFormat;

   }


   ::count copydesk::_get_file_count()
   {

      if(m_cFileCount < 0)
      {

         if (!IsClipboardFormatAvailable(CF_HDROP))
         {

            m_cFileCount = 0;

         }
         else
         {

            synchronization_lock synchronizationlock(mutex());

            if (!::OpenClipboard(__hwnd(get_oswindow())))
            //if(!OpenClipboard())
            {

               m_cFileCount =  0;

            }
            else
            {

               HDROP hdrop = (HDROP) ::GetClipboardData(CF_HDROP);

               ::count c = 0;

               if (hdrop != nullptr)
               {

                  c = ::DragQueryFile(hdrop, 0xFFFFFFFF, nullptr, 0);

               }

               ::CloseClipboard();

               m_cFileCount = c;

            }

         }

      }

      return m_cFileCount;

   }


   bool copydesk::_get_filea(::file::patha & patha, e_op & eop)
   {

      ::count c = _get_file_count();

      if (c <= 0)
      {

         return false;

      }

      synchronization_lock synchronizationlock(mutex());

      if (!::OpenClipboard(__hwnd(get_oswindow())))
      {

         return false;

      }

      HDROP hdrop = (HDROP) ::GetClipboardData(CF_HDROP);

      for (::index i = 0; i < c; i++)
      {

         ::u32 uLen = ::DragQueryFileW(hdrop, (::u32) i, nullptr, 0);

         wstring wstr(get_buffer, uLen);

         ::DragQueryFileW(hdrop, (::u32) i, wstr, (::u32) wstr.length());

         wstr.release_string_buffer();

         patha.add(::file::path(wstr));

      }

      ::CloseClipboard();

      return true;

   }


   bool copydesk::_set_filea(const ::file::patha & patha, e_op eop)
   {

      //ASSERT(::IsWindow(m_hwnd));

      synchronization_lock synchronizationlock(mutex());

      if (!::OpenClipboard(__hwnd(get_oswindow())))
      {

         return false;

      }

      EmptyClipboard();

      SetClipboardData(CF_HDROP, hglobal_get_filea(patha));

      SetClipboardData(CF_UNICODETEXT, hglobal_get_wide_text(patha.implode("\r\n")));

      SetClipboardData(CF_TEXT, hglobal_get_utf8_text(patha.implode("\r\n")));

      VERIFY(::CloseClipboard());

      return true;

   }


   bool copydesk::_has_plain_text()
   {

      if(m_iText < 0)
      {

         int iFormat = _get_priority_text_format();

         m_iText = iFormat != 0 && iFormat != -1 ? 1 : 0;

      }

      return m_iText != 0;

   }


   bool copydesk::_set_plain_text(const string & str)
   {

      //ASSERT(::IsWindow(m_hwnd));

      synchronization_lock synchronizationlock(mutex());

      if (!::OpenClipboard(__hwnd(get_oswindow())))
      {

         return false;

      }

      EmptyClipboard();

      SetClipboardData(CF_UNICODETEXT, hglobal_get_wide_text(str));

      SetClipboardData(CF_TEXT, hglobal_get_utf8_text(str));

      ::file::patha patha;

      if (string_to_filea(&patha, str))
      {

         SetClipboardData(CF_TEXT, hglobal_get_filea(patha));

      }

      VERIFY(::CloseClipboard());

      return true;

   }


   bool copydesk::_get_plain_text(string & str)
   {

      int iFormat = _get_priority_text_format();

      if (iFormat == 0 || iFormat == -1)
      {

         return false;

      }

      synchronization_lock synchronizationlock(mutex());

      if (!::OpenClipboard(__hwnd(get_oswindow())))
      {

         return false;

      }

      HGLOBAL hglb = GetClipboardData(iFormat);

      if (iFormat == CF_UNICODETEXT)
      {

         str = (const unichar *)GlobalLock(hglb);

      }
      else if (iFormat == CF_TEXT)
      {

         str = (char *)GlobalLock(hglb);

      }
      else if (iFormat == ::RegisterClipboardFormat(CFSTR_INETURLW))
      {

         str = (const unichar *)GlobalLock(hglb);

      }

      GlobalUnlock(hglb);

      VERIFY(::CloseClipboard());

      return true;

   }


#undef new

   bool copydesk::_has_image()
   {

      if(m_iDib < 0)
      {

         m_iDib = IsClipboardFormatAvailable(CF_BITMAP) ? 1 : 0;

      }

      return m_iDib != 0;

   }


   bool copydesk::_desk_to_image(::image * pimage)
   {

      if (!_has_image())
      {

         return false;

      }

      synchronization_lock synchronizationlock(mutex());

      if (!::OpenClipboard(__hwnd(get_oswindow())))
      {

         DWORD dwLastError = ::GetLastError();

         TRACELASTERROR();

         return false;

      }

      bool bOk = false;

      HBITMAP hbitmap = (HBITMAP) ::GetClipboardData(CF_BITMAP);

      if(hbitmap != nullptr)
      {


         HDC hdcMem = nullptr;

         HGDIOBJ hbitmapOld = nullptr;

         try
         {

            BITMAP bm;

            __zero(bm);

            ::GetObject(hbitmap, sizeof(bm), &bm);

            pimage->create(::size_i32(bm.bmWidth, bm.bmHeight), NOK_IMAGE_OBJECT);

            if (pimage->area() > 0)
            {

               pimage->fill(0);

               hdcMem = ::CreateCompatibleDC(nullptr);

               hbitmapOld = ::SelectObject(hdcMem, hbitmap);

               BITMAPINFO bi;

               bi.bmiHeader.biSize = sizeof(BITMAPINFO);
               bi.bmiHeader.biWidth = bm.bmWidth;
               bi.bmiHeader.biHeight = -bm.bmHeight;
               bi.bmiHeader.biPlanes = 1;
               bi.bmiHeader.biBitCount = 32;
               bi.bmiHeader.biCompression = BI_RGB;
               bi.bmiHeader.biSizeImage = pimage->scan_size() * bm.bmHeight;
               bi.bmiHeader.biXPelsPerMeter = 0;
               bi.bmiHeader.biYPelsPerMeter = 0;
               bi.bmiHeader.biClrUsed = 0;
               bi.bmiHeader.biClrImportant = 0;

               pimage->map();

               bOk = GetDIBits(hdcMem, hbitmap, 0, bm.bmHeight, pimage->get_data(), &bi, DIB_RGB_COLORS) != false;

            }

         }
         catch (...)
         {

         }

         if (hdcMem != nullptr)
         {

            ::SelectObject(hdcMem, hbitmapOld);

            ::DeleteDC(hdcMem);

         }

         ::DeleteObject((HGDIOBJ)hbitmap);

         ::CloseClipboard();

      }

      return bOk;

   }


   bool copydesk::_image_to_desk(const ::image * pimage)
   {

      //ASSERT(::IsWindow(m_hwnd));

      synchronization_lock synchronizationlock(mutex());

      if (!::OpenClipboard(__hwnd(get_oswindow())))
      {

         return false;

      }

      EmptyClipboard();


      SetClipboardData(CF_DIB, hglobal_get_image(pimage));


      VERIFY(::CloseClipboard());

      return true;

   }

#define new ACME_NEW


} // namespace windowing_win32



