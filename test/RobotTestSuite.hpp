/*
 * TestSuite.hpp
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

#include <cxxtest/TestSuite.h>
#include "../inc/Config.hpp"
#include "../inc/Robot.hpp"
#define TESTING

/*! \class MyTestSuite1
 *  \brief Test class
 * 
 * Tests are run by runner.cpp, created by the tool cxxtestgen
 */  
class MyTestSuite1 : public CxxTest::TestSuite
{
public:

    /*! \brief testConfig01 What happens if the config file is missing
     * 
     * Config::IsValid() must return false
     */ 
    void testConfig01(void) // missing file
    {
        Config config("../cfg/missing.cfg");
        TS_ASSERT_EQUALS(config.IsValid(),false);
    }
    
    /*! \brief testConfig02 What happens if the config file is correct
     * 
     * Config::IsValid() must return true
     */ 
    void testConfig02(void) // correct file
    {
        Config config("/home/david/projets/plotter2/cfg/robot.cfg");
        TS_ASSERT_EQUALS(config.IsValid(),true);
    }
    
    /*! \brief testConfig03 What happens if the config file has comments
     * 
     * Config::IsValid() must return true
     */ 
    void testConfig03(void) // comments
    {
        Config config("/home/david/projets/plotter2/cfg/commentedConfig.cfg");
        TS_ASSERT_EQUALS(config.IsValid(),true);
    }
    
    /*! \brief testConfig04 What happens if one component doesn't have parameters
     * 
     * Config::IsValid() must return false
     */ 
    void testConfig04(void) // Component without config
    {
        Config config("/home/david/projets/plotter2/cfg/componentNoConfig.cfg");
        TS_ASSERT_EQUALS(config.IsValid(),false);
    }
    
    /*! \brief testConfig05 What happens if one component doesn't have a type
     * 
     * Config::IsValid() must return false
     */
    void testConfig05(void) // Component without type
    {
        Config config("/home/david/projets/plotter2/cfg/componentNoType.cfg");
        TS_ASSERT_EQUALS(config.IsValid(),false);
    }
    
    /*! \brief testConfig06 What happens if the robot has no name
     * 
     * Config::IsValid() must return true
     */
    void testConfig06(void) // Robot without name
    {
        Config config("/home/david/projets/plotter2/cfg/noName.cfg");
        TS_ASSERT_EQUALS(config.IsValid(),true);
    }
    
    /*! \brief testConfig07 What happens if a component line is truncated
     * 
     * Config::IsValid() must return true
     */
    void testConfig07(void) // Truncated Component
    {
        Config config("/home/david/projets/plotter2/cfg/truncatedComponent.cfg");
        TS_ASSERT_EQUALS(config.IsValid(),true);
    }
    
    /*! \brief testConfig08 What happens if a component detail is truncated
     * 
     * Config::IsValid() must return false
     */    
    void testConfig08(void) // Truncated Detail
    {
        Config config("/home/david/projets/plotter2/cfg/truncatedDetail.cfg");
        TS_ASSERT_EQUALS(config.IsValid(),false);
    }
    
    /*! \brief testRobot01 Build a correct robot
     * 
     * Config::IsValid() must return false
     */  
    void testRobot01(void)
    {
        Config* config=new Config("/home/david/projets/plotter2/cfg/robot.cfg");
        Robot robot(config);
        TS_ASSERT_EQUALS(robot.GetReady(),true);
        delete(config);
    }

};
