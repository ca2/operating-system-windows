#pragma once


namespace multimedia
{


   namespace audio_directsound
   {


      class CLASS_DECL_AUDIO_DIRECTSOUND factory_exchange :
         virtual public ::multimedia::directsound::factory_exchange
      {
      public:


         factory_exchange(::object * pobject);
         virtual ~factory_exchange();

      };


   } // namespace audio_directsound


} // namespace multimedia






