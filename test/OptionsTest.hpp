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
        int argc=1;
        char **argv1 = new char*[argc];
        argv1[0]=(char*)"robot";
        Options options1(argc,argv1);
        TSM_ASSERT_EQUALS("Options file should be /cfg/robot.cfg",options1.GetRobotOptionsFileName(),"cfg/robot.cfg");
        TSM_ASSERT_EQUALS("Logging options file should be log4cxx.properties",options1.GetLoggingOptionsFileName(),"log4cxx.properties");
        TSM_ASSERT_EQUALS("Logging level should be INFO",options1.GetLoggingLevel(),"INFO");
        delete(argv1);
    }
    
    /*! \brief testOptions02 Using "-c newOpt.cfg -e DEBUG -l log.properties"
     * 
     * Full options. Must retrieve the parameters.
     */  
    void testOptions02(void)
    {
        int argc=4;
        char **argv2 = new char*[argc];
        argv2[0]=(char*)"robot";
        argv2[1]=(char*)"-cnewOpt.cfg";
        argv2[2]=(char*)"-eDEBUG";
        argv2[3]=(char*)"-llog.properties";
        

        Options options2(argc,argv2);
        TSM_ASSERT_EQUALS("Options file should be newOpt.cfg",options2.GetRobotOptionsFileName(),"newOpt.cfg");
        TSM_ASSERT_EQUALS("Logging options file should be log.properties",options2.GetLoggingOptionsFileName(),"log.properties");
        TSM_ASSERT_EQUALS("Logging level should be DEBUG",options2.GetLoggingLevel(),"DEBUG");
        delete(argv2);
    }
    
    /*! \brief testOptions03 Option loaded twice "-c file1 -c file2"
     * 
     * Repeated options. Must stop, or load the second?
     */  
    void testOptions03(void)
    {
        int argc=2;
        char **argv3 = new char*[argc];
        argv3[0]=(char*)"robot";
        argv3[1]=(char*)"-cfile1";
    //    argv3[2]=(char*)"-cfile2";
        Options options3(argc,argv3);
     //   TSM_ASSERT_EQUALS("Options file should be file1",options3.GetRobotOptionsFileName(),"file1");
       
        delete(argv3);
    }
    
    /*! \brief testOptions04 Contradictory parameters "-b -l file.properties"
     * 
     * With -b we ask not to use -l, but we provide -l. UseBasic must return true, and the file must be stored anyway
     */  
    void testOptions04(void)
    {
     //   int argc=3;
     //   char **argv = new char*[argc];
     //   argv[0]=(char*)"robot";
     //   argv[1]=(char*)"-b";
     //   argv[2]=(char*)"-lfile.properties";
     //   Options options(argc,argv);
     //   TSM_ASSERT_EQUALS("Logging options file should be file.properties",options.GetLoggingOptionsFileName(),"file.properties");
      //  TSM_ASSERT_EQUALS("Logging using basic options file should be true",options.UseBasicLogging(),true);
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
