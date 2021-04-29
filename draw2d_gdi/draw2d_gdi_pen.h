#pragma once


namespace draw2d_gdi
{


   class CLASS_DECL_DRAW2D_GDI pen :
      virtual public ::draw2d_gdi::object,
      virtual public ::draw2d::pen
   {
   public:


      bool        m_bProcess;


      pen(::object * pobject);
      virtual ~pen();

      operator HPEN() const;
      int GetLogPen(LOGPEN* pLogPen);
      int GetExtLogPen(EXTLOGPEN* pLogPen);


      virtual void construct(int nPenStyle, int nWidth, COLORREF crColor);
      virtual void construct(int nPenStyle, int nWidth, const LOGBRUSH* pLogBrush, int nStyleCount = 0, const u32* lpStyle = nullptr);
      bool CreatePen(int nPenStyle, int nWidth, COLORREF crColor);
      bool CreatePen(int nPenStyle, int nWidth, const LOGBRUSH* pLogBrush,
                     int nStyleCount = 0, const u32* lpStyle = nullptr);
      bool CreatePenIndirect(LPLOGPEN lpLogPen);


      virtual void dump(dump_context & dumpcontext) const;


      virtual bool create();

   };


} // namespace draw2d_gdi



