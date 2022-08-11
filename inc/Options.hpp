/*
 * Options.hpp
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
 
#ifndef __OPTIONS__
#define __OPTIONS__
#include <string>

/*! \class Options
 *  \brief Parses and hold the options coming from the command line
 *  \see main
 *  This class is used before loading the logxcxx config.
 *  Using stderr instead.
 */ 
class Options
{
	private:
	
	public:
	/*! 
		* Constructor, called with the main args
		*/ 
	Options(int argc, char **argv);
	
	/*! 
	* Destructor
	*/
	~Options();

};

#endif