// Programa que exemplica como eh feita uma animacao usando a Allegro.
// Quando executado, eh aberta uma janela com uma estrela que fica
// andando de um lado para o outro da janela. Para encerrar a execucao
// do programa basta pressionar ESC ou clicar no botao de fechar a
// janel.
//
// Curso de Especializacao em Desenvolvimento de Jogos Digitais
// Disciplina: Programacao 2D
// Professores: Isabel H. Manssour e Marcio S. Pinho

#include <iostream>
#include <allegro5/allegro.h>
#include <allegro5/allegro_opengl.h>

// Constante que contem o frame rate
#define FPS 60

// Variaveis que guardam a translacao da estrela.
int txEstrela = -40;
int tyEstrela = 80;
int xStep = 1;
int yStep = 1;

// Variavel que guarda a dimensao da window
int win = 200;

// Variavel que guarda a fila de eventos.
ALLEGRO_EVENT_QUEUE *event_queue;


// Funcao que desenha um triangulo amarelo centralizado na origem.
void draw_triangle(void)
{
	glColor3f(1, 1, 0);
	glBegin(GL_TRIANGLES);
		glVertex2f(-40, -40);
		glVertex2f(  0,  40);
		glVertex2f( 40, -40);
	glEnd();
}

// Funcao que desenha uma estrela centralizada na origem e
// formada por dois triangulos.
void draw_star(void)
{
	glTranslatef(0,15,0);
	draw_triangle();
	glTranslatef(0,-30,0);
	glScalef(1,-1,0);
	draw_triangle();
}


// Funcao que atualiza os valores de translacao da estrela para
// que ela "ande" pela janela.
void update_position()
{
	// Muda a direcao quando chega na borda esquerda ou direita
	if(txEstrela > win-30 || txEstrela < -win+30)
		xStep = -xStep;

	// Muda a direcao quando chega na borda superior ou inferior
    if(tyEstrela > win-30 || tyEstrela < -win+30)
		yStep = -yStep;

	// Atualiza o valor de translacao para animar a estrela
    txEstrela += xStep;
    tyEstrela += yStep;
}


// Funcao que contem os comandos OpenGL para fazer um desenho na janela.
void draw_opengl(void)
{
	// Especifica a cor de fundo da janela
	glClearColor(0, 0, 0, 1);
	// Limpa a janela
	glClear(GL_COLOR_BUFFER_BIT);

	// Inicializa sistema de coordenadas de projecao
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	// Estabelece volume de visualizacao (xMin, xMax, yMin, yMax, zMin, zMax)
	glOrtho(-win, win, -win, win, -1, 1);

	// Inicializa sistema de coordenadas do modelo
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// Desenha uma estrela formada por dois triangulos
	glTranslatef(txEstrela,tyEstrela,0);
	draw_star();
}


// Funcao que estabelece o loop principal do programa. Aqui se fica a espera
// dos eventos (de qualquer fonte de eventos) para fazer o tratamento de cada
// um deles. Enquanto não houver evento, o programa fica "parado", consumindo
// pouco tempo de CPU.
static void main_loop(void)
{
	ALLEGRO_EVENT event;

	while (true) {
		// Verifica se a fila de eventos esta vazia para fazer o "refresh" da tela
		if (al_event_queue_is_empty(event_queue)) {
			draw_opengl();
			al_flip_display();
		}

		// Espera ate que a fila de eventos nao esteja vazia. O primeiro evento
		// da fila será copiado em "event" e removido da fila.
		al_wait_for_event(event_queue, &event);


		// Verifica qual foi o evento gerado e faz o tratamento adequado.
		// ALLEGRO_EVENT eh uma union, e a interpretacao de seu conteudo
		// depende do tipo de evento, que eh definido no campo "type".
		// Cada evento vem de uma fonte (mouse, joystick ou teclado,
		// por exemplo), que pode ser acessada por "event.any.source".
		switch (event.type)
		{
			// Indica que o botao de fechar da janela foi pressionado.
			case ALLEGRO_EVENT_DISPLAY_CLOSE:
					return; // Encerra a execucao do programa
					break;

			// Indica que uma tecla foi pressionada.
			// O campo "keycode" do evento "keyboard" contem uma constante que
			// representa a tecla.
			case ALLEGRO_EVENT_KEY_DOWN:
					if (event.keyboard.keycode == ALLEGRO_KEY_ESCAPE)
						return; // Encerra a execucao do programa
					break;
			// Indica que o contador do timer foi incrementado.
			case ALLEGRO_EVENT_TIMER:
					update_position();
					break;
		}
	}
}


// Funcao principal.
int main(void)
{
    // Funcao de inicializacao da Allegro
	al_init();

	// Chamada de funcao para forcar o uso de OpenGL ao inves de DirectX (DirectX eh o default)
	al_set_new_display_flags(ALLEGRO_OPENGL);

	// Funcao para criar uma janela com as dimensoes passadas como parametro, que torna-se
	// automaticamente ativa, com o backbuffer selecionado para desenho. Os parametros
	// da janela sao determinados pelas ultimas chamadas a "al_set_new_display_*".
        ALLEGRO_DISPLAY *display = al_create_display(600, 600);

	// Funcao usada para especificar o titulo da janela.
	// al_set_window_title("Teste da Allegro com OpenGL e Timer");

	// Funcao que instala um driver de teclado. Se der problema, retorna false, senao retorna true.
	if ( !al_install_keyboard() ) {
		return 1; // encerra se deu problema
	}

	// Funcao que instala um driver de mouse. Se der problema, retorna false, senao retorna true.
	if ( !al_install_mouse() ){
		return 1; // encerra se deu problema
	}

	// ALLEGRO_TIMER* al_install_timer(double speed_secs)
	// Funcao que instala um novo timer, retornando o ponteiro para o mesmo. Se der
	// problema, retorna NULL. O valor passado como parametro deve ser positivo.
	// O novo timer (ou controlador de tempo) é inicializado parado.
	ALLEGRO_TIMER *timer = al_create_timer(1.0 / FPS);

	// Funcao que cria uma fila de eventos nova e vazia, retornando o ponteiro para o objeto criado,
	// ou NULL se ocorreu um erro.
	event_queue = al_create_event_queue();
	if (event_queue==NULL) {
		return 1; // encerra se deu problema
	}

	// al_register_event_source(): registra a fonte de eventos com a fila de eventos especificada.
	// al_get_mouse_event_source(): recupera a fonte de eventos do mouse.
	// al_get_keyboard_event_source(): recupera a fonte de eventos do teclado.
	// al_get_display_event_source(): recupera a fonte de evento associada a janela.
	// al_get_timer_event_source(ALLEGRO_TIMER *timer): recupera a fonte de eventos associada.
	al_register_event_source(event_queue, al_get_mouse_event_source());
	al_register_event_source(event_queue, al_get_keyboard_event_source());
	al_register_event_source(event_queue, al_get_timer_event_source(timer));
	al_register_event_source(event_queue, al_get_display_event_source(display));

	// void al_start_timer(ALLEGRO_TIMER *timer) inicia o timer passado por parametro.
	// A partir disso, o contador do timer vai incrementar em um frequencia constante
	// e vai comecar a gerar eventos. Inicializar um timer que ja foi inicializado nao
	// faz nada.
	al_start_timer(timer);

	// Funcao que estabelece o loop do programa, que fica a espera de eventos
	main_loop();

    return 0;
}
