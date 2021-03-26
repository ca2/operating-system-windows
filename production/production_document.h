#pragma once


namespace production
{


   class CLASS_DECL_CA2_PRODUCTION document :
      public ::user::document
   {
   public:


      document(::object * pobject);

      DECL_GEN_SIGNAL(data_on_after_change);

	   virtual bool on_new_document();

   public:
	   virtual ~document();
   #ifdef DEBUG
	   virtual void assert_valid() const;
	   virtual void dump(dump_context & dumpcontext) const;
   #endif

      bool on_open_document(const var & varFile) override;


   };


} // namespace production



