#include<TVout.h>
#include<video_gen.h>
#include "game.h"

TVout tv;

const uint8_t FUNCTIONNING_INDICATIVE_LED = 13;
uint32_t asteroids_x = 0;
uint32_t asteroids_y[5];

uint32_t rocket_x;
uint32_t rocket_y; 

void setup() {
	pinMode(FUNCTIONNING_INDICATIVE_LED, OUTPUT);
	
	digitalWrite(FUNCTIONNING_INDICATIVE_LED, LOW);
	
	if(tv.begin(NTSC, 128, 96) == 0){
		digitalWrite(FUNCTIONNING_INDICATIVE_LED, HIGH);
	}	

	delay(1000);

	randomSeed(analogRead(A5));
	
	for (int i=0; i<5; i++){
		asteroids_y[i] = random(1, tv.hres());
	}

	rocket_x = tv.hres() - 1;
	rocket_y = tv.hres() / 2;
}

void loop() {	
	tv.clear_screen();

	uint32_t rocket_position = map( analogRead(A0), 0, 1024, 0, tv.vres() );

	print_rocket(rocket_position);
	print_asteroids();

	if( asteroids_x > tv.hres()) {
		for ( int i=0; i<5; i++ ) {
			asteroids_y[i] 		= random( 0, tv.hres() );
			asteroids_x    		= 0;
		}	
	} else {
		asteroids_x++;
	}

	if(asteroids_collided_with_the_rocket( rocket_position )){
		game_over_bitch();
	}

	delay( 10 );
}

void print_rocket( uint32_t rocket_position ) {
	tv.draw_line( rocket_x, rocket_position - 2, rocket_x, rocket_position + 2, WHITE ); 
}

void print_asteroids() {
	for(int i=0; i<5; i++){
		tv.set_pixel( asteroids_x, asteroids_y[i], WHITE );
	}
}

bool asteroids_collided_with_the_rocket( uint32_t rocket_position) {
	if ( asteroids_x >= rocket_x) {
		for ( int i=0; i<5; i++ ) {
			if((asteroids_y[i] >= rocket_position-2) && (asteroids_y[i] <= rocket_position + 2)) {
				return true;
			}  
		}		
	}

	return false;
}

void game_over_bitch() {
	tv.clear_screen();
	
	for ( int d=0; d<tv.hres(); d++ ){
		tv.draw_circle( tv.hres()/2, tv.vres()/2, d, WHITE );
		delay( 10 );
	}
	
	delay( 15000 );

	for( int i=0; i<5; i++ ){
		asteroids_y[i] = random( 0, tv.hres() );
	}

	tv.clear_screen();
}

