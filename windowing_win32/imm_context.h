#pragma once


class CLASS_DECL_WINDOWING_WIN32 imm_context
{
public:


   HIMC                                m_himc;
   __pointer(::user::interaction)      m_pinteraction;


   imm_context(::user::interaction * pinteraction);
   ~imm_context();


   operator HIMC () const { return m_himc; }

   bool close();

   bool is_opened() const;

   void clear_composition();

   bool close_candidate(index iIndex = 0);

   string get_string(int iStr = GCS_COMPSTR);

   string _get_candidate(int iList);

   string get_candidate();


};


