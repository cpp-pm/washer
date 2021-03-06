/**
    @file

    Thin layer around Win32 menu functions.

    @if license

    Copyright (C) 2012  Alexander Lamaison <awl03@doc.ic.ac.uk>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.

    If you modify this Program, or any covered work, by linking or
    combining it with the OpenSSL project's OpenSSL library (or a
    modified version of that library), containing parts covered by the
    terms of the OpenSSL or SSLeay licenses, the licensors of this
    Program grant you additional permission to convey the resulting work.

    @endif
*/

#ifndef WASHER_GUI_MENU_DETAIL_MENU_WIN32_HPP
#define WASHER_GUI_MENU_DETAIL_MENU_WIN32_HPP
#pragma once

#include <washer/error.hpp> // last_error

#include <boost/exception/errinfo_api_function.hpp>
#include <boost/exception/info.hpp> // errinfo
#include <boost/throw_exception.hpp> // BOOST_THROW_EXCEPTION

#include <Winuser.h> // CreateMenu, CreatePopupMenu, DestroyMenu

namespace washer {
namespace gui {
namespace menu {
namespace detail {
namespace win32 {

inline HMENU create_menu()
{
    HMENU hmenu = ::CreateMenu();
    if (hmenu == NULL)
        BOOST_THROW_EXCEPTION(
            boost::enable_error_info(washer::last_error()) <<
            boost::errinfo_api_function("CreateMenu"));
    return hmenu;
}

inline HMENU create_popup_menu()
{
    HMENU hmenu = ::CreatePopupMenu();
    if (hmenu == NULL)
        BOOST_THROW_EXCEPTION(
            boost::enable_error_info(washer::last_error()) <<
            boost::errinfo_api_function("CreatePopupMenu"));
    return hmenu;
}

inline void destroy_menu(HMENU hmenu)
{
    if (!::DestroyMenu(hmenu))
        BOOST_THROW_EXCEPTION(
            boost::enable_error_info(washer::last_error()) <<
            boost::errinfo_api_function("DestroyMenu"));
}

inline void insert_menu(
    HMENU menu, UINT position, UINT flags, UINT_PTR new_item_id_or_handle,
    const char* new_item)
{
    if (!::InsertMenuA(menu, position, flags, new_item_id_or_handle, new_item))
        BOOST_THROW_EXCEPTION(
            boost::enable_error_info(washer::last_error()) <<
            boost::errinfo_api_function("InsertMenu"));
}

inline void insert_menu(
    HMENU menu, UINT position, UINT flags, UINT_PTR new_item_id_or_handle,
    const wchar_t* new_item)
{
    if (!::InsertMenuW(menu, position, flags, new_item_id_or_handle, new_item))
        BOOST_THROW_EXCEPTION(
            boost::enable_error_info(washer::last_error()) <<
            boost::errinfo_api_function("InsertMenu"));
}

inline void insert_menu_item(
    HMENU menu, UINT id, BOOL is_by_position, const MENUITEMINFOA* info)
{
    if (!::InsertMenuItemA(menu, id, is_by_position, info))
        BOOST_THROW_EXCEPTION(
            boost::enable_error_info(washer::last_error()) <<
            boost::errinfo_api_function("InsertMenuItem"));
}

inline void insert_menu_item(
    HMENU menu, UINT id, BOOL is_by_position, const MENUITEMINFOW* info)
{
    if (!::InsertMenuItemW(menu, id, is_by_position, info))
        BOOST_THROW_EXCEPTION(
            boost::enable_error_info(washer::last_error()) <<
            boost::errinfo_api_function("InsertMenuItem"));
}

inline void get_menu_item_info(
    HMENU menu, UINT id, BOOL is_by_position, MENUITEMINFOA* info)
{
    if (!::GetMenuItemInfoA(menu, id, is_by_position, info))
        BOOST_THROW_EXCEPTION(
            boost::enable_error_info(washer::last_error()) <<
            boost::errinfo_api_function("GetMenuItemInfo"));
}

inline void get_menu_item_info(
    HMENU menu, UINT id, BOOL is_by_position, MENUITEMINFOW* info)
{
    if (!::GetMenuItemInfoW(menu, id, is_by_position, info))
        BOOST_THROW_EXCEPTION(
            boost::enable_error_info(washer::last_error()) <<
            boost::errinfo_api_function("GetMenuItemInfo"));
}

inline void set_menu_item_info(
    HMENU menu, UINT id, BOOL is_by_position, const MENUITEMINFOA* info)
{
    if (!::SetMenuItemInfoA(menu, id, is_by_position, info))
        BOOST_THROW_EXCEPTION(
            boost::enable_error_info(washer::last_error()) <<
            boost::errinfo_api_function("SetMenuItemInfo"));
}

inline void set_menu_item_info(
    HMENU menu, UINT id, BOOL is_by_position, const MENUITEMINFOW* info)
{
    if (!::SetMenuItemInfoW(menu, id, is_by_position, info))
        BOOST_THROW_EXCEPTION(
            boost::enable_error_info(washer::last_error()) <<
            boost::errinfo_api_function("SetMenuItemInfo"));
}

inline int get_menu_item_count(HMENU menu)
{
    int count = ::GetMenuItemCount(menu);
    if (count < 0)
        BOOST_THROW_EXCEPTION(
            boost::enable_error_info(washer::last_error()) <<
            boost::errinfo_api_function("GetMenuItemCount"));
    return count;
}

inline bool is_menu(HMENU menu)
{
    return ::IsMenu(menu) != FALSE;
}

inline void enable_menu_item(HMENU menu, UINT item, UINT flags)
{
    if (!::EnableMenuItem(menu, item, flags))
        BOOST_THROW_EXCEPTION(
            boost::enable_error_info(washer::last_error()) <<
            boost::errinfo_api_function("EnableMenuItem"));
}

inline UINT get_menu_default_item(HMENU menu, BOOL by_position, UINT gdmi_flags)
{
    return ::GetMenuDefaultItem(menu, by_position, gdmi_flags);
}

inline void set_menu_default_item(HMENU menu, UINT item, BOOL by_position)
{
    BOOL success = ::SetMenuDefaultItem(menu, item, by_position);
    if (!success)
        BOOST_THROW_EXCEPTION(
            boost::enable_error_info(washer::last_error()) <<
            boost::errinfo_api_function("SetMenuDefaultItem"));
}

}}}}} // namespace washer::gui::menu::detail::win32

#endif
