/*
 ** @file Constants.hpp
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

#ifndef __CONSTANTS__
#define __CONSTANTS__

#define OK 1
#define TRUE 1
#define ON 1
#define ERROR 0
#define FALSE 0
#define OFF 0

/**
 * List of available component types.
 * 
 * Determines the components that derive from BaseComponent
 * and can be put in the robot's component vector
 */ 
enum ComponentType {
	unknown,	/**< type unknown. If a component has this value the full robot is faulty and must stop. */
	led,		/**< type led */
	servo,		/**< type servo */
	camera,		/**< type raspicam */
	button,		/**< type button */
	screen		/**< type screen */
	};

/**
 * List of states in wich the robot can be
 * 
 */ 
enum RunMode {
	stopped,	/**< type stopped. Initial and final mode*/
	starting,	/**< type starting. Creating components and initiating them*/
	waiting,	/**< Everything is ready. Waiting for a client*/
	looking,	/**< Taking the photo, and converting in curves to draw*/
	drawing,	/**< Servos working*/
	stopping	/**< Closing everything*/
	};

#endif
