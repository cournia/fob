/*
-------------------------------------------------------------------------------
libfob - C++ interface to Ascension Technology Corporation's
         Flock of Birds position and orientation measurement system.
Copyright (C) 2002 Nathan Cournia

This library is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public
License as published by the Free Software Foundation; either
version 2.1 of the License, or (at your option) any later version.

This library is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public
License along with this library; if not, write to the Free Software
Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
-------------------------------------------------------------------------------
*/

//FILE:         fly.cpp
//AUTHOR:       Nathan Cournia <nathan@cournia.com>

#include <iostream>
#include <unistd.h>
#include "fob/fob.h"

int main( int argc, char *argv[] )
{
	//check command line
	if( argc != 2 ) {
		std::cerr << "usage: fly port" << std::endl;
		return 1;
	}
	std::string device = argv[ 1 ];

	// open the flock of birds on serial port 1
	// 
	// the sensor is installed in the ceiling so,
	// tell the flock that all birds will operate in the DOWN
	// hemisphere
	//
	// we have a fairly new version of the fob hardware, so
	// run it at a high baud rate
	fob flock( device, fob::DOWN, fob::FAST );
	if( !flock ) {
		std::cerr << "fatal: " << flock.get_error( ) << std::endl;
		return 1;
	}

	//get a list of birds connected to the flock
	fob::bird_list& birds = flock.get_birds( );

	//report how many birds are present
	std::cout << "number of birds: " << birds.size( ) << std::endl;

	//for each bird, set that we want position and orientation information
	for( unsigned int i = 0; i < birds.size( ); ++i ) {
		if( !birds[ i ]->set_mode( fob::POSITION | fob::ORIENTATION ) ) {
			std::cerr << "fatal: " << flock.get_error( ) << std::endl;
			return 1;
		}
	}
	//birds configured, set the flock flying
	flock.fly( );

	//let the bird start up . . .
	sleep( 1 );

	//report position and orientation for each bird
	math::vector3 pos;
	math::quaternion quat;

	while( 1 ) {
		for( unsigned int i = 0; i < birds.size( ); ++i ) {
			//get position and orientation information from the bird
			birds[ i ]->get_position( pos );
			birds[ i ]->get_quaternion( quat );

			//report
			std::cout << i 
				<< ": p: " << pos
				<< " q: " << quat
				<< std::endl;
		}
	}

	return 0;
}
