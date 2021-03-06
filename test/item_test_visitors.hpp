/**
    @file

    Visitors used to make assertions about menu items.

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

#ifndef WASHER_TEST_MENU_ITEM_TEST_VISITORS_HPP
#define WASHER_TEST_MENU_ITEM_TEST_VISITORS_HPP
#pragma once

#include "wchar_output.hpp" // wchar_t test output

#include <washer/gui/menu/item/command_item.hpp>
#include <washer/gui/menu/item/separator_item.hpp>
#include <washer/gui/menu/item/sub_menu_item.hpp>
#include <washer/gui/menu/menu.hpp> // menu
#include <washer/gui/menu/visitor.hpp> // menu_visitor

#include <boost/test/unit_test.hpp>

#include <string>

namespace washer {
namespace test {

class selectable_state_test : public washer::gui::menu::menu_visitor<>
{
public:

    void operator()(washer::gui::menu::separator_item&)
    {
        BOOST_FAIL("Separator unexpected");
    }

    void operator()(washer::gui::menu::selectable_item& item)
    {
        BOOST_CHECK(item.is_selectable());
        BOOST_CHECK(!item.is_highlighted());
        BOOST_CHECK(!item.check_mark_is_visible());
    }
};

class selectability_test : public washer::gui::menu::menu_visitor<>
{
public:

    selectability_test(bool expected) : m_expected(expected) {}

    void operator()(washer::gui::menu::separator_item&)
    {
        BOOST_FAIL("Separator unexpected");
    }

    void operator()(washer::gui::menu::selectable_item& item)
    {
        BOOST_CHECK_EQUAL(item.is_selectable(), m_expected);
    }

private:
    bool m_expected;
};

class selectability_mutator : public washer::gui::menu::menu_visitor<>
{
public:

    selectability_mutator(
        BOOST_SCOPED_ENUM(washer::gui::menu::selectability) state)
        : m_selectability(state) {}

    void operator()(washer::gui::menu::separator_item&)
    {
        BOOST_FAIL("Separator unexpected");
    }

    void operator()(washer::gui::menu::selectable_item& item)
    {
        item.selectability(m_selectability);
    }

private:
    BOOST_SCOPED_ENUM(washer::gui::menu::selectability) m_selectability;
};

class checkedness_test : public washer::gui::menu::menu_visitor<>
{
public:

    checkedness_test(bool expected) : m_expected(expected) {}

    void operator()(washer::gui::menu::separator_item&)
    {
        BOOST_FAIL("Separator unexpected");
    }

    void operator()(washer::gui::menu::selectable_item& item)
    {
        BOOST_CHECK_EQUAL(item.check_mark_is_visible(), m_expected);
    }

private:
    bool m_expected;
};

class check_mutator : public washer::gui::menu::menu_visitor<>
{
public:

    check_mutator(BOOST_SCOPED_ENUM(washer::gui::menu::check_mark) state)
        : m_checkedness(state) {}

    void operator()(washer::gui::menu::separator_item&)
    {
        BOOST_FAIL("Separator unexpected");
    }

    void operator()(washer::gui::menu::selectable_item& item)
    {
        item.check_mark_visibility(m_checkedness);
    }

private:
    BOOST_SCOPED_ENUM(washer::gui::menu::check_mark) m_checkedness;
};

class is_separator_test : public washer::gui::menu::menu_visitor<>
{
public:

    void operator()(washer::gui::menu::separator_item&)
    {
    }

    void operator()(washer::gui::menu::command_item&)
    {
        BOOST_FAIL("Command item unexpected");
    }

    void operator()(washer::gui::menu::sub_menu_item&)
    {
        BOOST_FAIL("Sub-menu unexpected");
    }
};

class is_command_test : public washer::gui::menu::menu_visitor<>
{
public:

    void operator()(washer::gui::menu::separator_item&)
    {
        BOOST_FAIL("Separator unexpected");
    }

    void operator()(washer::gui::menu::command_item&)
    {
    }

    void operator()(washer::gui::menu::sub_menu_item&)
    {
        BOOST_FAIL("Sub-menu unexpected");
    }
};

class is_sub_menu_test : public washer::gui::menu::menu_visitor<>
{
public:

    void operator()(washer::gui::menu::separator_item&)
    {
        BOOST_FAIL("Separator unexpected");
    }

    void operator()(washer::gui::menu::command_item&)
    {
        BOOST_FAIL("Command item unexpected");
    }

    void operator()(washer::gui::menu::sub_menu_item&)
    {
    }
};

class id_test : public washer::gui::menu::menu_visitor<>
{
public:
    id_test(UINT id) : m_id(id) {}

    template<typename T>
    void operator()(T& item)
    {
        BOOST_CHECK_EQUAL(item.id(), m_id);
    }

private:
    UINT m_id;
};

class sub_menu_test : public washer::gui::menu::menu_visitor<>
{
public:

    sub_menu_test(const washer::gui::menu::menu& menu) : m_menu(menu) {}

    template<typename T>
    void operator()(T&)
    {
        BOOST_FAIL("Unexpected");
    }

    void operator()(washer::gui::menu::sub_menu_item& item)
    {
        washer::gui::menu::menu submenu = item.menu();
        BOOST_CHECK(submenu.valid());

        BOOST_CHECK(submenu == m_menu);
    }

private:
    washer::gui::menu::menu m_menu;
};

template<typename ButtonVisitor>
class button_test :
    public washer::gui::menu::menu_visitor<typename ButtonVisitor::result_type>
{
public:

    button_test(ButtonVisitor test) : m_test(test) {}

    typename ButtonVisitor::result_type operator()(
        washer::gui::menu::separator_item&)
    {
        BOOST_FAIL("Separator unexpected");
        return typename ButtonVisitor::result_type();
    }

    typename ButtonVisitor::result_type operator()(
        washer::gui::menu::selectable_item& item)
    {
        return item.button().accept(m_test);
    }

private:
    ButtonVisitor m_test;
};

template<typename ButtonVisitor>
inline button_test<ButtonVisitor> make_button_test(ButtonVisitor test)
{
    return button_test<ButtonVisitor>(test);
}

}}

#endif
