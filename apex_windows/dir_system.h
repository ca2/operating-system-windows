﻿#pragma once


namespace windows
{


   class CLASS_DECL_APEX_WINDOWS dir_system:
      virtual public ::dir_system
   {
   public:


      ::file::path            m_strTimeFolder;
      ::file::path            m_strNetSeedFolder;

      ::file::path            m_strCommonAppData;
      ::file::path            m_strAppData;
      ::file::path            m_strPrograms;
      ::file::path            m_strCommonPrograms;


      dir_system();
      virtual ~dir_system();
      
      
      virtual ::e_status initialize(::context_object * pcontextobject) override;


      virtual ::e_status init_system() override;


   };


} // namespace windows



