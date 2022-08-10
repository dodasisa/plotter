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

#include "../inc/main.hpp"
#include "../inc/Robot.hpp"
#include "../inc/Config.hpp"

LoggerPtr logger(Logger::getLogger("plotter"));

int main(int argc, char **argv)
{
	int opt;
	string configFile="cfg/robot.cfg";
	string logSetup="log4cxx.properties";
	string logLevel="INFO";
	while ((opt = getopt(argc, argv, "hc:l:e:")) != -1) 
	{
		switch (opt)
		{
			case 'h':
				Usage();
				return EXIT_SUCCESS;
				break;
			case 'c':
				configFile=optarg;
				break;
			case 'l':
				logSetup=optarg;
				break;
			case 'e':
				logLevel=optarg;
				break;
			default:
				Usage();
				return EXIT_FAILURE;
		}
	}
	
	int state=OK;
	if (logSetup == "BASIC")
	{
		try
		{
			BasicConfigurator::configure();
		}
		catch(Exception&)
		{
			std::cerr << "logger fails to start using basic configuration" << endl;
			return EXIT_FAILURE;
		}
	}
	else
	{
		try
		{
			PropertyConfigurator::configure(logSetup);
		}
		catch(Exception&)
		{
			std::cerr << "logger fails to start using log4cxx.properties" << endl;
			state=ERROR;
			return EXIT_FAILURE;
		}
	}
	
	LOG4CXX_INFO(logger, "Starting robot." << " Version " << VERSION);
	
	if (argc > 1) configFile=argv[1];
	LOG4CXX_INFO(logger, "Using configuration file " + configFile);
	

	if (gpioInitialise() < 0)
	{
		LOG4CXX_ERROR(logger, "GPIO fails to initialise.");
		return EXIT_FAILURE;
	}
	Config* config=new Config(configFile,false);
	if (config->IsValid()==ERROR)
	{
		LOG4CXX_ERROR(logger, "The config file has errors.");
		return EXIT_FAILURE;
	}
	if (config->components.size()==0)
	{
		LOG4CXX_ERROR(logger, "No components found in the config file.");
		return EXIT_FAILURE;
	}
	LOG4CXX_INFO(logger, config->components.size() << " components found.");
	Robot robot(config);
	if (!robot.GetReady()) 
	{
		LOG4CXX_ERROR(logger, "Robot fails to start.");
		gpioTerminate();
		delete(config);
		return EXIT_FAILURE;
	}
	if (robot.Run() ==  ERROR){
		LOG4CXX_ERROR(logger, "Robot exits with error.");
		delete(config);
		gpioTerminate();
		return EXIT_FAILURE;
	}
	time_sleep(5.0);

	LOG4CXX_INFO(logger, "Stopping robot.");
    gpioTerminate();
    delete(config);
	return EXIT_SUCCESS;
}

void Usage()
{
	cout << "Usage:" << endl;
	cout << "\trobot" << VERSION << " [-h] [-c configFile] [-l logSetup] [-e (OFF|TRACE|DEBUG|INFO|WARN|ERROR|FATAL)]" << endl;
	cout << "Values by default are:" << endl;
	cout << "\trobot" << VERSION << endl;
	cout << "\t\t-c cfg/robot.cfg" << endl;
	cout << "\t\t-l log4cxx.properties" << endl;
	cout << "\t\t-e INFO" << endl;
}

