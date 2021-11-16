#include<TVout.h>
#include<video_gen.h>

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
	
	int ctrl = map( analogRead(A0), 0, 1024, 0, tv.vres() );

	tv.draw_line( 
		rocket_x, 
		ctrl - 2, 
		rocket_x, 
		ctrl + 2, 
		WHITE );

	delay( 10 );

	tv.draw_line( 
		rocket_x, 
		ctrl - 2, 
		rocket_x, 
		ctrl + 2, 
		BLACK );

	
	for(int i=0; i<5; i++){
		tv.set_pixel( asteroids_x, asteroids_y[i], WHITE );
	}

	delay( 10 );

	for(int i=0; i<5; i++){
		tv.set_pixel( asteroids_x, asteroids_y[i], BLACK );
	}

	if( asteroids_x > tv.hres()) {
		for ( int i=0; i<5; i++ ) {
			asteroids_y[i] 		= random( 0, tv.hres() );
			asteroids_x    		= 0;
		}	
	} else {
		asteroids_x++;
	}

	if ( asteroids_x >= rocket_x) {
		for ( int i=0; i<5; i++ ) {
			if((asteroids_y[i] >= ctrl-2) && (asteroids_y[i] <= ctrl + 2)) {
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
		}		
	}	

}
