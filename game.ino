#include<Tvout.h>
#include<video_gen.h>

TVout tv;
int led - 13;

void setup() {
	pinMode(led, OUTPUT);
	if( tv.begin(NTSC, 128, 96) == 0 ) {
		digitalWrite(led, HIGH);
	}

	else {
		digitalWrite(led, LOW);
	}
}

void loop() {
  // put your main code here, to run repeatedly:

}
