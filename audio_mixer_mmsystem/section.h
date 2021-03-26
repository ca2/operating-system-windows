#pragma once


namespace multimedia
{


   namespace audio_mixer_mmsystem
   {


      class CLASS_DECL_AUDIO_MIXER_MMSYSTEM department :
         virtual public ::apex::department,
         virtual public ::user::interaction
      {
      public:



         enum EIds
         {

            IdsMuteAll,
            IdsMute

         };


         department();
         virtual ~department();


         virtual bool initialize1();



         bool initialize();


         virtual ::e_status finalize() override;





      };


   } // namespace mixguserbase


} // namespace multimedia






