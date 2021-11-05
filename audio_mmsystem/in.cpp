﻿#include "framework.h"


namespace audio_mmsystem
{


   in::in()
   {

      m_pencoder = nullptr;
      m_hwavein = nullptr;
      m_estate = e_state_initial;
      m_bResetting = false;

   }

   in::~in()
   {
   }


   ::e_status in::init_thread()
   {

      TRACE("in::initialize_instance %X\n", get_ithread());

      //SetMainWnd(nullptr);
      //ASSERT(GetMainWnd() == nullptr);

      set_thread_priority(::e_priority_highest);

//         m_evInitialized.SetEvent();

      return true;

   }


   void in::term_thread()
   {

      m_eventExitInstance.SetEvent();

      thread::term_thread();

   }


   void in::pre_translate_message(::message::message * pmessage)
   {

      //ASSERT(GetMainWnd() == nullptr);
      if(pmessage->m_id == MM_WIM_OPEN ||
         pmessage->m_id == MM_WIM_CLOSE ||
         pmessage->m_id == MM_WIM_DATA)
      {
         
         translate_in_message(pmessage);

         if (pmessage->m_bRet)
         {

            return;

         }

      }

      return thread::pre_translate_message(pmessage);

   }


   ::e_status in::in_open(i32 iBufferCount, i32 iBufferSampleCount)
   {

      if(m_hwavein != nullptr && m_estate != e_state_initial)
      {

         in_initialize_encoder();

         return ::success;

      }

      single_lock sLock(mutex(), true);
      ::e_status     estatus;
      int iStatus = MMSYSERR_NOERROR;

      ASSERT(m_hwavein == nullptr);
      ASSERT(m_estate == e_state_initial);

      m_pwaveformat->m_waveformat.wFormatTag = WAVE_FORMAT_PCM;
      m_pwaveformat->m_waveformat.nChannels = 2;
      m_pwaveformat->m_waveformat.nSamplesPerSec = 44100;
      m_pwaveformat->m_waveformat.wBitsPerSample = sizeof(::wave::WAVEBUFFERDATA) * 8;
      m_pwaveformat->m_waveformat.nBlockAlign = m_pwaveformat->m_waveformat.wBitsPerSample * m_pwaveformat->m_waveformat.nChannels / 8;
      m_pwaveformat->m_waveformat.nAvgBytesPerSec = m_pwaveformat->m_waveformat.nSamplesPerSec * m_pwaveformat->m_waveformat.nBlockAlign;

      auto paudio = m_psystem->m_paquasystem->audio()->m_paudio;
      
      auto audiowave = paudio->audiowave();

      m_iBuffer = 0;

      if(estatus = ::multimedia::mmsystem::translate(waveInOpen(
                                          &m_hwavein,
                                          audiowave->m_uiWaveInDevice,
                                          wave_format(),
                                          get_ithread(),
                                          (u32) 0,
                                          CALLBACK_THREAD)))
         goto Opened;

      m_pwaveformat->m_waveformat.nSamplesPerSec = 22050;
      m_pwaveformat->m_waveformat.nAvgBytesPerSec = m_pwaveformat->m_waveformat.nSamplesPerSec * m_pwaveformat->m_waveformat.nBlockAlign;
      if(estatus = ::multimedia::mmsystem::translate(waveInOpen(
                                          &m_hwavein,
                                          WAVE_MAPPER,
                                          wave_format(),
                                          (u32) get_ithread(),
                                          (u32) 0,
                                          CALLBACK_THREAD)))
         goto Opened;
      m_pwaveformat->m_waveformat.nSamplesPerSec = 11025;
      m_pwaveformat->m_waveformat.nAvgBytesPerSec = m_pwaveformat->m_waveformat.nSamplesPerSec * m_pwaveformat->m_waveformat.nBlockAlign;
      if(MMSYSERR_NOERROR == (iStatus = waveInOpen(
                                          &m_hwavein,
                                          WAVE_MAPPER,
                                          wave_format(),
                                          (u32) get_ithread(),
                                          (u32) 0,
                                          CALLBACK_THREAD)))
         goto Opened;

      if(iStatus != MMSYSERR_NOERROR)
      {

         if(iStatus == MMSYSERR_ALLOCATED)
         {

            TRACE("Specified resource is already allocated.");

         }
         else if(iStatus == MMSYSERR_BADDEVICEID)
         {

            TRACE("Specified device identifier is out of range.");

         }
         else if(iStatus == WAVERR_BADFORMAT)
         {

            TRACE("Attempted to open with an unsupported waveform-audio_mmsystem format.");

         }
            
         TRACE("ERROR OPENING WAVE INPUT DEVICE");
            
         return iStatus;

      }

Opened:
      u32 uiBufferSizeLog2;
      u32 uiBufferSize;
      u32 uiAnalysisSize;
      u32 uiAllocationSize;
      u32 uiInterestSize;
      u32 uiSkippedSamplesCount;

      if(m_pwaveformat->m_waveformat.nSamplesPerSec == 44100)
      {
         uiBufferSizeLog2 = 16;
         uiBufferSize = m_pwaveformat->m_waveformat.nChannels * 2 * iBufferSampleCount; // 512 kbytes
         uiAnalysisSize = 4 * 1 << uiBufferSizeLog2;
         if(iBufferCount > 0)
         {
            uiAllocationSize = iBufferCount * uiBufferSize;
         }
         else
         {
            uiAllocationSize = 8 * uiAnalysisSize;
         }
         uiInterestSize = 200;
         uiSkippedSamplesCount = 2;
      }
      else if(m_pwaveformat->m_waveformat.nSamplesPerSec == 22050)
      {
         uiBufferSizeLog2 = 9;
         uiBufferSize = 4 * 1 << uiBufferSizeLog2;
         uiAnalysisSize = 16 * 1 << uiBufferSizeLog2;
         uiAllocationSize = 4 * uiAnalysisSize;
         uiInterestSize = 600;
         uiSkippedSamplesCount = 1;
      }
      else if(m_pwaveformat->m_waveformat.nSamplesPerSec == 11025)
      {
         uiBufferSizeLog2 = 9;
         uiBufferSize = 2 * 1 << uiBufferSizeLog2;
         uiAnalysisSize = 8 * 1 << uiBufferSizeLog2;
         uiAllocationSize = 4 * uiAnalysisSize;
         uiInterestSize = 600;
         uiSkippedSamplesCount = 1;
      }
      in_get_buffer()->FFTOpen(
      uiAllocationSize,
      uiBufferSize,
      uiAnalysisSize,
      uiInterestSize,
      uiSkippedSamplesCount);

      i32 i, iSize;

      iSize = (i32) in_get_buffer()->GetBufferCount();

      for(i = 0; i < iSize; i++)
      {

         if(::success != (estatus = ::multimedia::mmsystem::translate(waveInPrepareHeader(m_hwavein, ::multimedia::mmsystem::create_new_WAVEHDR(in_get_buffer(), i), sizeof(WAVEHDR)))))
         {
            TRACE("ERROR OPENING Preparing INPUT DEVICE buffer");
            return estatus;
         }

         in_add_buffer(i);

      }

      if(m_pencoder != nullptr && !in_initialize_encoder())
      {

         m_estate = e_state_opened;

         in_close();

         return (::e_status    ) -1;

      }

      m_estate = e_state_opened;

      return ::success;

   }


   ::e_status     in::in_close()
   {

      single_lock sLock(mutex(), true);

      ::e_status     estatus;

      if(m_estate != e_state_opened && m_estate != state_stopped)
         return ::success;

      estatus = in_reset();

      i32 i, iSize;

      iSize = (i32) in_get_buffer()->GetBufferCount();

      for(i = 0; i < iSize; i++)
      {

         if(::success != (estatus = ::multimedia::mmsystem::translate(waveInUnprepareHeader(m_hwavein, wave_hdr(i), sizeof(WAVEHDR)))))
         {
            TRACE("ERROR OPENING Unpreparing INPUT DEVICE buffer");
            //return estatus;
         }

         delete wave_hdr(i);

      }

      estatus = ::multimedia::mmsystem::translate(waveInClose(m_hwavein));

      m_hwavein = nullptr;

      m_estate = e_state_initial;

      return ::success;

   }

   ::e_status     in::in_start()
   {

      single_lock sLock(mutex(), true);

      if(m_estate == state_recording)
         return ::success;

      //ASSERT(m_estate == e_state_opened || m_estate == state_stopped);

      if(m_estate != e_state_opened && m_estate != state_stopped)
         return ::success;

      ::e_status     estatus;

      if(::success != (estatus = ::multimedia::mmsystem::translate(waveInStart(m_hwavein))))
      {
         TRACE("ERROR starting INPUT DEVICE ");
         return estatus;
      }

      m_estate = state_recording;

      return ::success;

   }

   ::e_status     in::in_stop()
   {

      single_lock sLock(mutex(), true);

      if(m_estate != state_recording)
         return error_failed;

      ::e_status     estatus;

      m_estate = e_state_stopping;

      try
      {

         if(::success != (estatus = ::multimedia::mmsystem::translate(waveInStop(m_hwavein))))
         {

            TRACE("in::in_stop : ERROR OPENING stopping INPUT DEVICE ");

         }

      }
      catch(...)
      {

         TRACE("in::in_stop : Exception OPENING stopping INPUT DEVICE ");

      }

      m_estate = state_stopped;

      m_eventStopped.SetEvent();

      return ::success;

   }


   void CALLBACK in::in_proc(HWAVEIN hwi, UINT uMsg, DWORD dwInstance, DWORD dwParam1, DWORD dwParam2)
   {

      __UNREFERENCED_PARAMETER(hwi);
      __UNREFERENCED_PARAMETER(dwInstance);
      __UNREFERENCED_PARAMETER(dwParam1);
      __UNREFERENCED_PARAMETER(dwParam2);
      if(uMsg == WIM_DATA)
      {
         ASSERT(false);
         /*      u32 msSampleTime = timeGetTime();
         thread * pthread = (thread *) dwInstance;
         ASSERT(pthread != nullptr);
         LPWAVEHDR lpWaveHdr = (LPWAVEHDR) dwParam1;
         LPWAVEPROCDATAMESSAGE lpxfwm = new WAVEPROCDATAMESSAGE;
         lpxfwm->bDelete = true;
         lpxfwm->msSampleTime = msSampleTime;
         //      lpxfwm->tkSamplePosition = tkPosition;
         lpxfwm->lpWaveHdr = lpWaveHdr;
         pthread->post_thread_message(
         WM_USER,
         (WPARAM) WAVM_WAVE_PROC_DATA,
         (LPARAM) lpxfwm);
         //      i++;
         //      if( i > 2)
         //         i = 0;*/
      }

   }


   ::e_status     in::in_reset()
   {

      single_lock sLock(mutex(), true);

      m_bResetting = true;

      if(m_hwavein == nullptr)
      {

         return ::success;

      }

      ::e_status     estatus;

      if(m_estate == state_recording)
      {

         if(::success != (estatus = in_stop()))
         {

            TRACE("in::Reset error stopping input device");

            return estatus;

         }

      }


      try
      {

         if(::success != (estatus = ::multimedia::mmsystem::translate(waveInReset(m_hwavein))))
         {

            TRACE("in::Reset error resetting input device");

            return estatus;

         }

      }
      catch(...)
      {
      }

      m_estate = e_state_opened;

      m_bResetting = false;

      return ::success;

   }


   void in::translate_in_message(::message::message * pmessage)
   {

      ASSERT(pmessage->m_id == MM_WIM_OPEN || pmessage->m_id == MM_WIM_CLOSE || pmessage->m_id == MM_WIM_DATA);

      if(pmessage->m_id == MM_WIM_DATA)
      {

         m_iBuffer--;

         u32 msSampleTime = timeGetTime();

         LPWAVEHDR lpwavehdr = (LPWAVEHDR)pmessage->m_lparam.m_lparam;

         in_get_buffer()->get_buffer((i32) lpwavehdr->dwUser)->OnMultimediaDone();

         m_listenerset.in_data_proc(this, msSampleTime, (i32) lpwavehdr->dwUser);

         if(m_pencoder != nullptr)
         {
            m_pencoder->EncoderWriteBuffer(lpwavehdr->lpData, lpwavehdr->dwBytesRecorded);
         }

         if(!in_is_resetting() && in_is_recording())
         {
            in_add_buffer((i32) lpwavehdr->dwUser);
         }

      }

      pmessage->m_bRet = true;

   }


   ::e_status     in::in_add_buffer(i32 iBuffer)
   {

      return in_add_buffer(wave_hdr(iBuffer));

   }


   ::e_status     in::in_add_buffer(LPWAVEHDR lpwavehdr)
   {

      ::e_status     estatus;

      if(::success != (estatus = ::multimedia::mmsystem::translate(waveInAddBuffer(m_hwavein, lpwavehdr, sizeof(WAVEHDR)))))
      {

         TRACE("ERROR OPENING Adding INPUT DEVICE buffer");

      }

      m_iBuffer++;

      return estatus;

   }


   bool in::in_initialize_encoder()
   {

      if(m_pencoder == nullptr)
         return false;

      if(!::wave::in::in_initialize_encoder())
         return false;

      return true;

   }

   WAVEFORMATEX * in::wave_format()
   {

      ::multimedia::mmsystem::translate(m_waveformatex, m_pwaveformat);

      return &m_waveformatex;

   }

   HWAVEIN in::in_get_safe_HWAVEIN()
   {

      if(this == nullptr)
         return nullptr;

      return m_hwavein;

   }

   void * in::get_os_data()
   {

      return m_hwavein;

   }


   LPWAVEHDR in::wave_hdr(int iBuffer)
   {

      return ::multimedia::mmsystem::get_os_data(in_get_buffer(), iBuffer);

   }


} // namespace audio_mmsystem



