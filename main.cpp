/*
 * main.cxx
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

#include <stdio.h>
#include <iostream>
#include <pigpio.h>
#include <string>

#include "Robot.hpp"
#include "Config.hpp"

int main(int argc, char **argv)
{
	string configFile="robot.cfg";
	if (argc > 1) configFile=argv[1];	
	std::cerr << "main" << endl;
	std::cout << "Starting plotter" << std::endl;
	if (gpioInitialise() < 0)
	{
		std::cout << "GPIO fails to initialise" << endl;
		return EXIT_FAILURE;
	}
	Config* config=new Config(configFile);
	std::cerr << "config contents " << config->components.size() << " components" << endl;
	Robot robot(config);
	if (!robot.IsReady()) 
	{
		std::cout << "Robot fails to start" << endl;
		gpioTerminate();
		delete(config);
		return EXIT_FAILURE;
	}
	if (robot.Run() ==  ERROR){
		std::cout << "Robot exits with error" << endl;
		delete(config);
		gpioTerminate();
		return EXIT_FAILURE;
	}
	time_sleep(5.0);

    std::cout << "Ending plotter" << std::endl;
    gpioTerminate();
    delete(config);
    std::cout << "Done." << std::endl;
	return EXIT_SUCCESS;
}

