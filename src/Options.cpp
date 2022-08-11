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
  int c;

  opterr = 0;

  while ((c = getopt (argc, argv, "hc:l:e:")) != -1)
    switch (c)
      {
      case 'h':
        Usage();
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
        return 1;
      default:
        abort ();
      }

}

Options::~Options()
{
}

void Options::Usage()
{
  fprintf (stderr, "Usage: \n");
  fprintf (stderr, "robot -h \t Prints this help\n");
  fprintf (stderr, "robot -c [fileName] \t Alternate options file. Default is cfg/robot.cfg\n");
  fprintf (stderr, "robot -l [fileName] \t Alternate log4cxx options file. Default is log4cxx.properties\n");
  fprintf (stderr, "robot -e [level] \t Log level. Can be one of OFF,TRACE,DEBUG,INFO,WARN,ERROR or FATAL. Default is INFO\n");
}
