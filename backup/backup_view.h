#pragma once


namespace backup
{


   class CLASS_DECL_CA2_BACKUP view :
      virtual public production::view
   {
   public:
	   
      
      view(::object * pobject);
      virtual ~view();


      virtual ::production::production * create_production();


   };


} // namespace backup



