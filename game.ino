#include<TVout.h>
#include<video_gen.h>

TVout tv;

int led = 13;
int x   = 0;
int y     [5];

int spaceship_x;
int spaceship_y; 

int punctuation = 0;

int punctuation_x = 0;	
int punctuation_y = 0;

void setup() {
	pinMode(led, OUTPUT);
	
	if(tv.begin(NTSC, 128, 96) == 0){
		digitalWrite(led, HIGH);
	}	
	else {
		digitalWrite(led, LOW);
	}
	
	delay(1000);

	randomSeed(analogRead(A5));
	
	for (int i=0; i<5; i++){
		y[i] = random(1, tv.hres());
	}

	spaceship_x = tv.hres() - 1;
	spaceship_y = tv.hres() / 2;
}

void loop() {	
	
	int ctrl = map( analogRead(A0), 0, 1024, 0, tv.vres() );

	tv.draw_line( 
		spaceship_x, 
		ctrl - 2, 
		spaceship_x, 
		ctrl + 2, 
		WHITE );

	delay( 10 );

	tv.draw_line( 
		spaceship_x, 
		ctrl - 2, 
		spaceship_x, 
		ctrl + 2, 
		BLACK );

	
	for(int i=0; i<5; i++){
		tv.set_pixel( x, y[i], WHITE );
	}

	delay( 10 );

	for(int i=0; i<5; i++){
		tv.set_pixel( x, y[i], BLACK );
	}

	if( x > tv.hres()) {
		for ( int i=0; i<5; i++ ) {
			y[i] 		= random( 0, tv.hres() );
			x    		= 0;
			punctuation	++;
		}	
	} else {
		x++;
	}

	if ( x >= spaceship_x) {
		for ( int i=0; i<5; i++ ) {
			if((y[i] >= ctrl-2) && (y[i] <= ctrl + 2)) {
				tv.clear_screen();
				
				for ( int d=0; d<tv.hres(); d++ ){
					tv.draw_circle( tv.hres()/2, tv.vres()/2, d, WHITE );
					delay( 10 );
				}
				
				delay( 15000 );

				for( int i=0; i<5; i++ ){
					y[i] = random( 0, tv.hres() );
				}

				tv.clear_screen();
			}  
		}		
	}	

}
