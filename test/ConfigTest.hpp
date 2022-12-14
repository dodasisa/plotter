/*
 * ConfigTest.hpp
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
#ifndef __CONFIGTEST__
#define __CONFIGTEST__
#include <cxxtest/TestSuite.h>
#include "../inc/Config.hpp"
#include "../inc/Robot.hpp"


/*! \class ConfigTest
 *  \brief Test class
 * 
 * Tests are run by runner.cpp, created by the tool cxxtestgen
 * This class holds all the tests about the Config class
 */  
class ConfigTest : public CxxTest::TestSuite
{
public:
    /*! \brief testConfig01 What happens if the config file is missing
     * 
     * Config::IsValid() must return false
     */ 
    void testConfig01(void) // missing file
    {
        Config config("../cfg/missing.cfg",true);
        TSM_ASSERT_EQUALS("Missing file not detected",config.IsValid(),false);
    }
    
    /*! \brief testConfig02 What happens if the config file is correct
     * 
     * Config::IsValid() must return true
     */ 
    void testConfig02(void) // correct file
    {
        Config config("/home/david/projets/plotter2/cfg/robot.cfg",true);
        TSM_ASSERT_EQUALS("Correct config raises an error",config.IsValid(),true);
    }
    
    /*! \brief testConfig03 What happens if the config file has comments
     * 
     * Config::IsValid() must return true
     */ 
    void testConfig03(void) // comments
    {
        Config config("/home/david/projets/plotter2/cfg/commentedConfig.cfg",true);
        TSM_ASSERT_EQUALS("Comments in config raises an error",config.IsValid(),true);
    }
    
    /*! \brief testConfig04 What happens if one component doesn't have parameters
     * 
     * Config::IsValid() must return false
     */ 
    void testConfig04(void) // Component without config
    {
        Config config("/home/david/projets/plotter2/cfg/componentNoConfig.cfg",true);
        TSM_ASSERT_EQUALS("Component without config undetected",config.IsValid(),false);
    }
    
    /*! \brief testConfig05 What happens if one component doesn't have a type
     * 
     * Config::IsValid() must return false
     */
    void testConfig05(void) // Component without type
    {
        Config config("/home/david/projets/plotter2/cfg/componentNoType.cfg",true);
        TSM_ASSERT_EQUALS("Component without defined type undetected",config.IsValid(),false);
    }
    
    /*! \brief testConfig06 What happens if the robot has no name
     * 
     * Config::IsValid() must return true
     */
    void testConfig06(void) // Robot without name
    {
        Config config("/home/david/projets/plotter2/cfg/noName.cfg",true);
        TSM_ASSERT_EQUALS("Robot without name should be valid",config.IsValid(),true);
    }
    
    /*! \brief testConfig07 What happens if a component line is truncated
     * 
     * Config::IsValid() must return true
     */
    void testConfig07(void) // Truncated Component
    {
        Config config("/home/david/projets/plotter2/cfg/truncatedComponent.cfg",true);
        TSM_ASSERT_EQUALS("Just store what is after the =. Will be ignored anyway",config.IsValid(),true);
    }
    
    /*! \brief testConfig08 What happens if a component detail is truncated
     * 
     * Config::IsValid() must return false
     */    
    void testConfig08(void) // Truncated Detail
    {
        Config config("/home/david/projets/plotter2/cfg/truncatedDetail.cfg",true);
        TSM_ASSERT_EQUALS("Truncated detail of component undetected",config.IsValid(),false);
    }
};
#endif
