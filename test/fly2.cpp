//FILE:         fly2.cpp
//AUTHOR:       Nathan Cournia <nathan@cournia.com>

#include <iostream>
#include <unistd.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include "camera.h"
#include "fob/fob.h"

#define ENABLE_FBB 1

const unsigned int MAX_ENTS = 14;

void render_axis( float len );

///////////////////////////////////////////////////////////////////////////////
struct entity {
	math::quaternion orientation;
	math::vector3 position;
	math::matrix4 matrix;

	void render( void );
};




///////////////////////////////////////////////////////////////////////////////
void
entity::render( void )
{
	//save modelview
	glPushMatrix( );

	//translate and rotate to bird position
	//glTranslatef( position.x( ), position.y( ), position.z( ) );
	//glMultMatrixf( orientation.get_transposed_rotation_matrix( ) );
	matrix.transpose( );
	glMultMatrixf( matrix );
	
	//render the mesh
	render_axis( 10 );

	//back to the old matrix
	glPopMatrix( );
}



//////////////////////////////////////////////////////////////////////////
//globals!  yeah!
entity entities[ MAX_ENTS ];
camera cam;
fob flock;
unsigned int num_birds;
fob::bird_list *p_birds;



//////////////////////////////////////////////////////////////////////////
void 
render_axis( float len )
{
	glLineWidth( 2.0 );
	glBegin( GL_LINES );
		//+x bright red
		glColor3f( 1.0, 0.0, 0.0 );
		glVertex3f( len, 0.0, 0.0);
		glVertex3f( 0.0, 0.0, 0.0 );

		//+y bright green
		glColor3f( 0.0, 1.0, 0.0 );
		glVertex3f( 0.0, len, 0.0 );
		glVertex3f( 0.0, 0.0, 0.0 );

		//+z bright blue
		glColor3f( 0.0, 0.0, 1.0 );
		glVertex3f( 0.0, 0.0, len );
		glVertex3f( 0.0, 0.0, 0.0 );
	glEnd( );
}



///////////////////////////////////////////////////////////////////////////////
void
init_gl( void )
{
	//opengl options
	glEnable( GL_DEPTH_TEST );
	glDepthFunc( GL_LEQUAL );
	glDisable( GL_TEXTURE_2D );
	glDisable( GL_LIGHTING );
}



///////////////////////////////////////////////////////////////////////////////
void
handle_keyboard( unsigned char key, int x, int y )
{
	if( key == 27 ) { //ESC pressed
		exit( 0 );
	}
}



///////////////////////////////////////////////////////////////////////////////
void
handle_resize( int w, int h )
{
	//prevent divide by zero
	if( h == 0 ) h = 0;

	glMatrixMode( GL_PROJECTION );
	glLoadIdentity( );
	glViewport( 0, 0, w, h );
	gluPerspective( 45.0, static_cast<float>( w ) / h, 1.0, 1000.0 );

	glMatrixMode( GL_MODELVIEW );
	glLoadIdentity( );
}

///////////////////////////////////////////////////////////////////////////////
void
handle_exit( void )
{
	flock.close( );
}

///////////////////////////////////////////////////////////////////////////////
void
render( void )
{
		//clear gl buffers
		glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

		//reset modelview
		glLoadIdentity( );

		//view from camera
		cam.view( );

		//render a reference frame
		render_axis( 100000 );

#if ENABLE_FBB
		//update entity positions
		for( unsigned int i = 0; i < num_birds; ++i ) {
			//(*p_birds)[ i ]->get_position( entities[ i ].position );
			//(*p_birds)[ i ]->get_quaternion( entities[ i ].orientation );
			(*p_birds)[ i ]->get_matrix( entities[ i ].matrix );
		}
#endif

		//render entities
		for( unsigned int i = 0; i < num_birds; ++i ) {
			entities[ i ].render( );
		}

		//done
		glutSwapBuffers( );
}



///////////////////////////////////////////////////////////////////////////////
int 
main( int argc, char *argv[ ] )
{
	//check command line
	if( argc < 2 ) {
		std::cerr << "usage: fly2 <fob-device>" << std::endl;
		return 1;
	}
	char *serial = argv[ 1 ];

	//setup glut
	glutInit( &argc, argv );
	glutInitDisplayMode( GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA );
	glutInitWindowSize( 640, 480 );
	glutCreateWindow( "Flock of Birds Demo" );

	//setup gl
	init_gl( );

	//set callbacks
	glutKeyboardFunc( handle_keyboard );
	glutReshapeFunc( handle_resize );
	glutDisplayFunc( render );
	glutIdleFunc( render );

#if ENABLE_FBB
	fob::hemisphere hemisphere = fob::DOWN;
	fob::port_speed speed = fob::FAST;
	
	//talk to flock
	flock.open( serial, hemisphere, speed );
	if( !flock ) {
		std::cerr << "fatal: " << flock.get_error( ) << std::endl;
		return 1;
	}

	//get a list of birds connected to the machine
	fob::bird_list& birds = flock.get_birds( );
	p_birds = &flock.get_birds( );
	num_birds = birds.size( );
	if( num_birds > MAX_ENTS ) num_birds = MAX_ENTS;
#else
	unsigned int num_birds = 1;
#endif
	
#if ENABLE_FBB
	//for each bird, set that we want position and orientation
	for( unsigned int i = 0; i < birds.size( ); ++i ) {
		if( !birds[ i ]->set_mode( fob::POSITION | fob::ORIENTATION ) ) {
			std::cerr << "fatal: " << flock.get_error( ) << std::endl;
			return 1;
		}
	}
#endif

	//setup the camera
	cam.set_position( 0.0, 100.0, 0.0 );
	cam.set_look_right( math::vector3( 0.0, 0.0, 0.0 ), math::vector3::X_AXIS );
	
#if ENABLE_FBB
	//set the flock flying
	flock.fly( );
	atexit( handle_exit );

	//let the bird start up . . .
	sleep( 1 );
#endif

	//start glut
	glutMainLoop( );

	//no errors
	return 0;
}
