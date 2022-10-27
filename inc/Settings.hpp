/*
 * settings.hpp
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


#ifndef SETTINGS_HPP
#define SETTINGS_HPP
#include <string>
#include <cstdio>
#include "../inc/rapidjson/document.h"
#include "../inc/rapidjson/filereadstream.h"

using namespace std;
using namespace rapidjson;

class Settings
{
	public:
		Settings();
		void SetFile(string fileName);
		bool Parse(); 
		string Message;
	private:
		string FileName;
};

#endif /* SETTINGS_HPP */ 
