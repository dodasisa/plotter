/*
 * OptionsTest.hpp
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
#ifndef __OPTIONSTEST__
#define __OPTIONSTEST__
#include <cxxtest/TestSuite.h>
#include "../inc/Options.hpp"



/*! \class OptionsTest
 *  \brief Test class
 * 
 * Tests are run by runner.cpp, created by the tool cxxtestgen.
 * This suite tests the Options class
 */  
class OptionsTest : public CxxTest::TestSuite
{
public:
    /*! \brief testOptions01 Using no options at all
     * 
     * No options. Must retrieve the defaults.
     */  
    void testOptions01(void)
    {
   //     Options options(0,"");
   //     TSM_ASSERT_EQUALS("Options file should be /cfg/robot.cfg",options.GetRobotOptionsFileName(),"/cfg/robot.cfg");
   //     TSM_ASSERT_EQUALS("Logging options file should be log4cxx.properties",options.GetLoggingOptionsFileName(),"log4cxx.properties");
   //     TSM_ASSERT_EQUALS("Logging level should be INFO",options.GetLoggingLevel(),"INFO");
    }
    
    /*! \brief testOptions02 Using "-c newOpt.cfg -e DEBUG -l log.properties"
     * 
     * Full options. Must retrieve the parameters.
     */  
    void testOptions02(void)
    {
    //    Options options(3,"-c newOpt.cfg","-e DEBUG","-l log.properties");
    //    TSM_ASSERT_EQUALS("Options file should be /cfg/robot.cfg",options.GetRobotOptionsFileName(),"newOpt.cfg");
    //    TSM_ASSERT_EQUALS("Logging options file should be log4cxx.properties",options.GetLoggingOptionsFileName(),"log.properties");
    //    TSM_ASSERT_EQUALS("Logging level should be INFO",options.GetLoggingLevel(),"DEBUG");
    }
    
    /*! \brief testOptions03 Option loaded twice "-c file1 -c file2"
     * 
     * Repeated options. Must stop, or load the second?
     */  
    void testOptions03(void)
    {
    //    Options options(3,"-c file1.cfg","-e DEBUG","-c file2.cfg");
     //   TSM_ASSERT_EQUALS("An error should be detected",options.IsValid(),false);
     //   TSM_ASSERT_EQUALS("Stored the latest version",options.GetRobotOptionsFileName(),"file2.cfg");
    }
    
    /*! \brief testOptions04 Contradictory parameters "-b -l file.properties"
     * 
     * With -b we ask not to use -l, but we provide -l. UseBasic must return true, and the file must be stored anyway
     */  
    void testOptions04(void)
    {
    //    Options options(3,"-b","-l file2.cfg");
    //    TSM_ASSERT_EQUALS("Should be correct",options.IsValid(),true);
    //    TSM_ASSERT_EQUALS("An error should be detected",options.IsValid(),false);
     //   TSM_ASSERT_EQUALS("Flag basic must have priority",options.UseBasicLogging(),true);
    //    TSM_ASSERT_EQUALS("Stored the file, even if ignored",options.GetLoggingOptionsFileName(),"file2.cfg");
    }
    
    /*! \brief testOptions05 Unknown option "-q -b"
     * 
     * With -b we ask not to use -l, but we provide -l. UseBasic must return true, and the file must be stored anyway
     */  
    void testOptions05(void)
    {
     //   Options options(2,"-q","-b");
     //   TSM_ASSERT_EQUALS("Should be wrong",options.IsValid(),false);
    }
    
    /*! \brief testOptions06 Missing value "-c -b"
     * 
     * With -b we ask not to use -l, but we provide -l. UseBasic must return true, and the file must be stored anyway
     */  
    void testOptions06(void)
    {
    //    Options options(2,"-c","-b");
    //    TSM_ASSERT_EQUALS("Should be wrong",options.IsValid(),false);
    }
};
#endif
