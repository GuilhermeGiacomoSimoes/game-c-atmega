/*
* 
* O objetivo do jogo e fazer com que asteroides saiam do canto esquerdo dda tela para o canto direito
* e o potenciometro movimente a nave para desviar dos asteroides
*/

#include<TVout.h>
#include<video_gen.h>

TVout tv;

/*
* led para indicacao de normalidade no circuito e no programa 
* x indica a coluna dos asteroides
* y indica a linha dos asteroides, o tamanho do vetor 5 indica que so tera 5 asteroides por vez
*/
int led = 13;
int x   = 0;
int y     [5];

/*
* variaveis que indicam a posicao da nave
*/
int spaceship_x;
int spaceship_y; 

/*
* variavel responsavel por armazenar a pontuacao
*/
int punctuation = 0;

/*
* variaveis responsavel por dizer a posicao da pontuacao na tela
*/
int punctuation_x = 0;	
int punctuation_y = 0;

void setup() {
	pinMode(led, OUTPUT);
	
	/*
	* Inicializa a geracao de imagens na tv com padrao NTSC e resolucao de 128 x 96....
	* Essa funcao retorna 0 caso tudo esteja funcionadno bem
	* returna 1 caso a resolucao horizontal nao seja multipla de 8
	* returna 2 caso a resolucao vertical nao seja multipla de 8
	* returna 3 caso nao haja memoria o suficiente no ATMEGA
	*/
	if(tv.begin(NTSC, 128, 96) == 0){
		/*
		* Caso tudo esteja funcionando como deveria acende o LED indicando que tudo esta normal
		*/
		digitalWrite(led, HIGH);
	}	
	else {
		/*
		* Caso tudo nao esteja funcionando como deveria apaga o LED indicando que tem algo de errado
		*/
		digitalWrite(led, LOW);
	}
	
	/*
	* delay para sincronia do sinal de tv	
	*/

	delay(1000);

	/*
	* gerando numeros aleatorios
	*/
	randomSeed(analogRead(A5));
	
	/*
	* sorteando uma linha para cada asteroid
	*/
	for (int i=0; i<5; i++){
		y[i] = random(1, tv.hres());
	}

	/*
	* inicia a nave na posicao x igual a resolucao da tela - 1
	* inicia a nave na posicao y igual a resolucao da tela / 2
	*/
	spaceship_x = tv.hres() - 1;
	spaceship_y = tv.hres() / 2;
}

void loop() {	
	
	/*
	* transformando o int em char[] para impressao na tela
	*/
	char buffer[33];
	itoa( punctuation, buffer, 10 );	
	tv.println( punctuation_x, punctuation_y,  buffer);

	/*
	* a posicao vertical da nave sera definida pelo valor lido do potenciometro
	* que retorna um valor entre 1024 e e convertido para um valor entre o a 
	* resolucao da tela. Essa conversao e feita pela funcao map();
	*/
	int ctrl = map( analogRead(A0), 0, 1024, 0, tv.vres() );

	/*
	* Desenha na tela uma linha horizontal com os valor lidos pelo potenciometro
	* e o valor da variavel spaceship_x
	*/
	tv.draw_line( 
		spaceship_x, 
		ctrl - 2, 
		spaceship_x, 
		ctrl + 2, 
		WHITE );

	delay( 10 );

	/*
	* apaga a linha anteriormente criada para desenhar uma nova futuramente
	*/
	tv.draw_line( 
		spaceship_x, 
		ctrl - 2, 
		spaceship_x, 
		ctrl + 2, 
		BLACK );

	
	/*
	* denha o pixel do asteroide na posicao x (que e incremnetada a cada loop)
	* e na posicao y[i] que e a linha responsavel pelo asteroide
	*/
	for(int i=0; i<5; i++){
		tv.set_pixel( x, y[i], WHITE );
	}

	delay( 10 );

	/*
	* apaga o pixel para desenhar outro futuramente
	*/
	for(int i=0; i<5; i++){
		tv.set_pixel( x, y[i], BLACK );
	}

	/*
	*  Aqui verificamos se a coluna x (onde esta o asteroide) e maior do que
	* a resolucao horizontal da tela. Caso seja, e preciso sortear uma nova 
	* posicao para as linhas dos asteroides e deixar x = 0
	* Se a posicao do asteroide nao for igual ao da resolucao horizontal da
	* da tela, ele faz x++ pra pintar o proximo pixel na posicao x 
	*/
	if( x > tv.hres()) {
		for ( int i=0; i<5; i++ ) {
			y[i] 		= random( 0, tv.hres() );
			x    		= 0;
			punctuation	++;
		}	
	} else {
		x++;
	}

	/*
	* aqui verificamos se a posicao dos asteroides sao a mesma da posicao da nave
	* caso seja, o jogo acaba desenhando um circulo crescente na tela e o jogo 
	* recomeca
	*/
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
