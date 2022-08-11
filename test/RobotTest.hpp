/*
 * RobotTest.hpp
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
#ifndef __TESTING__
#define __TESTING__
#include <cxxtest/TestSuite.h>
#include "../inc/Config.hpp"
#include "../inc/Robot.hpp"


/*! \class RobotTest
 *  \brief Test class
 * 
 * Tests are run by runner.cpp, created by the tool cxxtestgen
 * This class holds all the tests for the Robot class
 */  
class RobotTest : public CxxTest::TestSuite
{
public:
    /*! \brief testRobot01 Build a correct robot
     * 
     * Config::IsValid() must return false
     */  
    void testRobot01(void)
    {
        Config* config=new Config("/home/david/projets/plotter2/cfg/robot.cfg",true);
        Robot robot(config);
        TSM_ASSERT_EQUALS("Robot built with correct config should be correct",robot.GetReady(),true);
        delete(config);
    }
};
#endif
