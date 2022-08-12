/*
 * LedTest.hpp
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
#ifndef __LEDTEST__
#define __LEDTEST__
#include <cxxtest/TestSuite.h>
#include "../inc/Led.hpp"


/*! \class LedTest
 *  \brief Test class
 * 
 * Tests are run by runner.cpp, created by the tool cxxtestgen
 * This class holds all the tests for the Led class
 */  
class LedTest : public CxxTest::TestSuite
{
public:
    /*! \brief testLed01 Build a correct led and initializes by name
     * 
     */  
    void testLed01(void)
    {
        Led a_led();
        TSM_ASSERT_EQUALS("The constructor should create a Component of type button",a_led->GetType(),led);
        a_led.InitName("LedName");
        TSM_ASSERT_EQUALS("The led name should be stored",a_led->GetName(),"LedName");
    }
    
    /*! \brief testLed02 Build a correct led and initializes by name and pin
     * 
     */  
    void testLed02(void)
    {
        Led a_led();
        TSM_ASSERT_EQUALS("The constructor should create a Component of type led",a_button->GetType(),led);
        a_led.InitNamePin("LedName",5);
        TSM_ASSERT_EQUALS("The button name should be stored",a_led->GetName(),"LedName");
        TSM_ASSERT_EQUALS("The pin number should be stored",a_led->GetPin(),5);
    }
};
#endif
