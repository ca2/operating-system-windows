#include "framework.h"


__FACTORY_EXPORT void aura_windows_factory(::factory::factory * pfactory);


__FACTORY_EXPORT void windowing_win32_factory(::factory::factory * pfactory)
{

   aura_windows_factory(pfactory);

   pfactory->add_factory_item < ::windowing_win32::windowing, ::windowing::windowing >();
   pfactory->add_factory_item < ::windowing_win32::window, ::windowing::window >();
   pfactory->add_factory_item < ::windowing_win32::display, ::windowing::display >();
   pfactory->add_factory_item < ::windowing_win32::display >();
   pfactory->add_factory_item < ::windowing_win32::buffer, ::graphics::graphics >();
   pfactory->add_factory_item < ::windowing_win32::notify_icon, ::user::notify_icon >();
   pfactory->add_factory_item < ::windowing_win32::cursor, ::windowing::cursor >();
   pfactory->add_factory_item < ::windowing_win32::icon, ::windowing::icon >();
   pfactory->add_factory_item < ::windowing_win32::shell, ::user::shell >();
   pfactory->add_factory_item < ::windowing_win32::copydesk, ::user::copydesk >();
   pfactory->add_factory_item < imm_client, ::user::text_composition_client >();

   pfactory->add_factory_item < ::windowing_win32::keyboard, ::windowing::keyboard >();

   pfactory->add_factory_item < ::windowing_win32::node, ::acme::node >();

}