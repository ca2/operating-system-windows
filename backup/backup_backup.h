#pragma once


namespace backup
{



   class CLASS_DECL_CA2_BACKUP backup : 
      public ::production::production 
   {
   public:



      backup(::layered * pobjectContext);
      virtual ~backup();

      virtual ::e_status     run() override;

      bool hotcopy_repos(const char * psz);
      bool compress_repos(const char * psz);

      bool all_db_dump();
      bool db_copy();

      string get_new_repos_local_path(const char * psz);
      string get_new_db_local_path(const char * psz);




   };


} // namespace backup



