/*
 * ButtonTest.hpp
 * 
 * Copyright 2022 David <david.lopez.velazquez@gmail.com>
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 * 
 * 
 */
#ifndef __BUTTONTEST__
#define __BUTTONTEST__
#include <cxxtest/TestSuite.h>
#include "../inc/Button.hpp"
#include "../inc/Component.hpp"
#include "../inc/Constants.hpp"


/*! \class ButtonTest
 *  \brief Test class
 * 
 * Tests are run by runner.cpp, created by the tool cxxtestgen
 * This class holds all the tests for the Button class
 */  
class ButtonTest : public CxxTest::TestSuite
{
public:
    /*! \brief testButton01 Build a correct button and initializes by name
     * 
     */  
    void testButton01(void)
    {
        Button a_button();
    //    ComponentType componentType=a_button.GetType();
    //    string componentName=a_button.GetName();
    //    TSM_ASSERT_EQUALS("The constructor should create a Component of type button",componentType,ComponentType::button);
    //    a_button.InitName("ButtonName");
    //    TSM_ASSERT_EQUALS("The constructor should create a Component of type button",componentName,"ButtonName");
    }
     
    
    /*! \brief testButton02 Build a correct button and initializes by name and pin
     * 
     */  
    void testButton02(void)
    {
        Button a_button();
//        TSM_ASSERT_EQUALS("The constructor should create a Component of type button",a_button.GetType(),ComponentType::button);
 //       a_button.InitNamePin("ButtonName",5);
//        TSM_ASSERT_EQUALS("The button name should be stored",a_button->GetName(),"ButtonName");
//        TSM_ASSERT_EQUALS("The pin number should be stored",a_button->GetPin(),5);
    }
};
#endif
