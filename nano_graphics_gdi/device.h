//
// Created by camilo on 31/01/2022 14:35 <3ThomasBorregaardSorensen!!
//
#pragma once


#include "acme/nano/graphics/device.h"
#undef USUAL_OPERATING_SYSTEM_SUPPRESSIONS
#include "acme/_operating_system.h"


namespace windows
{


   namespace nano
   {


      namespace graphics
      {


         class CLASS_DECL_NANO_GRAPHICS_GDI device :
            virtual public ::nano::graphics::device
         {
         public:


            //CreatableFromBase(device, device);


            HDC         m_hdc;
            bool        m_bDelete;


            device();
            
            ~device() override;


            void attach(void * posdata) override;

            void _draw_text(const ::string& str, const ::rectangle_i32& rectangleText, const ::e_align& ealign, const ::e_draw_text& edrawtext, ::nano::graphics::brush* pnanobrushBack, ::nano::graphics::brush* pnanobrushText, ::nano::graphics::font* pnanofont) override;
            ::size_i32 get_text_extents(const ::string& str, ::nano::graphics::font* pnanofont) override;
            void rectangle(const ::rectangle_i32& rectangle, ::nano::graphics::brush* pnanobrush, ::nano::graphics::pen* pnanopen) override;


            void draw(::nano::graphics::icon * picon, int x, int y, int cx, int cy) override;


         };




      } // namespace graphics


   } // namespace nano



} // namespace windows


