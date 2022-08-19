/*
 * Options.cpp
 * 
 * Copyright 2022  <david.lopez.velazquez@gmail.com>
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

#include <iostream>
#include "../inc/Options.hpp"

using namespace std;

Options::Options(int argc, char **argv)
{
  //cerr << "argc=" << argc << ", argv=" << argv[0] << endl; 
  // Default values
  mRobotOptionsFileName = "cfg/robot.cfg";
  mLoggingOptionsFileName = "log4cxx.properties";
  mLoggingLevel="INFO";
  mBasicLogging=false;
  mValid=true;
  int c;
  opterr = 0;

  while ((c = getopt (argc, argv, "hbc:l:e:")) != -1)
    switch (c)
      {
      case 'h':
        Usage();
        mValid=false;
        break;
      case 'b':
        mBasicLogging=true;
        break;
      case 'c':
        mRobotOptionsFileName = optarg;
        break;
      case 'l':
        mLoggingOptionsFileName = optarg;
        break;
      case 'e':
        mLoggingLevel = optarg;
        break;
      case '?':
        if (optopt == 'c')
          fprintf (stderr, "Option -%c requires an argument. Usually robot.cfg\n", optopt);
        if (optopt == 'l')
          fprintf (stderr, "Option -%l requires an argument. Usually log4cxx.properties\n", optopt);
        if (optopt == 'e')
          fprintf (stderr, "Option -%e requires an argument. Can be one of OFF,TRACE,DEBUG,INFO,WARN,ERROR or FATAL\n", optopt);
        else if (isprint (optopt))
          fprintf (stderr, "Unknown option `-%c'.\n", optopt);
        else
          fprintf (stderr,
                   "Unknown option character `\\x%x'.\n",
                   optopt);
        mValid=false;
        return;
      default:
        mValid=false;
      //  abort ();      
        break;
      }
}

Options::~Options()
{
}

string Options::GetRobotOptionsFileName()
{
  return mRobotOptionsFileName;
}
string Options::GetLoggingOptionsFileName()
{
  return mLoggingOptionsFileName;
}
string Options::GetLoggingLevel()
{
  return mLoggingLevel;
}
bool Options::UseBasicLogging()
{
  return mBasicLogging;
}

void Options::Usage()
{
  fprintf (stderr, "Usage: \n");
  fprintf (stderr, "robot -h \t Prints this help\n");
  fprintf (stderr, "robot -c [fileName] \t Alternate options file. Default is cfg/robot.cfg\n");
  fprintf (stderr, "robot -b \t Use basic logging. Ignores -l if given\n");
  fprintf (stderr, "robot -l [fileName] \t Alternate log4cxx options file. Default is log4cxx.properties\n");
  fprintf (stderr, "robot -e [level] \t Log level. Can be one of OFF,TRACE,DEBUG,INFO,WARN,ERROR or FATAL. Default is INFO\n");
}
bool Options::IsValid()
{
  return mValid;
}
