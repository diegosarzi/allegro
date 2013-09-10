// Programa que exemplica como exibir sprites usando a Allegro.
// Quando executado, eh aberta uma janela com tres sprites que ficam
// andando de um lado para o outro da janela. Para encerrar a execucao
// do programa basta pressionar ESC ou clicar no botao de fechar a
// janel.
//
// Curso de Especializacao em Desenvolvimento de Jogos Digitais
// Disciplina: Programacao 2D
// Professores: Isabel H. Manssour e Marcio S. Pinho

#include <iostream>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_opengl.h>

// Constantes que contem o frame rate e o numero maximo de sprites
#define FPS 60
#define MAX_SPRITES 512

// Estrutura para armazenar as informacoes de uma sprite
typedef struct Sprite {
   float x, y, dx, dy;
} Sprite;

// Variaveis que guarda a dimensao da janela
int width, height;

// Vetor para armazenar um conjunto de Sprites com seu contador
Sprite sprites[MAX_SPRITES];
int contSprites;

// Variavel que guarda a fila de eventos.
ALLEGRO_EVENT_QUEUE *event_queue;

// Variavel que guarda a referencia para uma imagem.
ALLEGRO_BITMAP *dragon;

// Funcao que adiciona uma nova sprite no vetor de sprites.
void add_sprite(void)
{
   if (contSprites < MAX_SPRITES) {
      int w = width; 
      int h = height; 
      Sprite s;
      float a = rand() % 400;
      s.x = w - 128 - a;
      s.y = h - 128 - a;
      s.dx = 1 + rand() % 6;
      s.dy = 1 + rand() % 6;
	  sprites[contSprites] = s;
	  contSprites++;
   }
}


// Funcao que adiciona "n" sprites.
void add_sprites(int n)
{
    for (int i = 0; i < n; i++)
       add_sprite();
}

// Funcao que remove "n" sprites.
void remove_sprites(int n)
{
   contSprites--;
   if (contSprites < 0)
      contSprites = 0;
}

// Funcao que atualiza a posicao das sprites na janela.
void update()
{
	for(int i=0; i < contSprites; i++) {
		sprites[i].x += sprites[i].dx ;
		sprites[i].y += sprites[i].dy ;

		if ( sprites[i].x > (width - 128) )
			sprites[i].dx = - sprites[i].dx;
		else if ( sprites[i].x < (0) )
			sprites[i].dx = - sprites[i].dx;

		if ( sprites[i].y > (height - 128) )
			sprites[i].dy = - sprites[i].dy;
		else if ( sprites[i].y < (0) )
			sprites[i].dy = - sprites[i].dy;
	}
}


// Funcao que contem os comandos para o desenho das sprites.
void draw_sprites(void)
{
	al_clear_to_color(al_map_rgb_f(0, 0, 0));

	for (int i = 0; i < contSprites; i++) {
		Sprite s = sprites[i];
		// Prototipo: void al_draw_bitmap(ALLEGRO_BITMAP *bitmap, float dx, float dy, int flags)
		// Desenha um bitmap sem escala e sem rotacao na posicao (dx,dy) passada por parametro
		al_draw_bitmap(dragon, s.x, s.y, 0);
	}
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
			draw_sprites();
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
					if (event.keyboard.keycode == ALLEGRO_KEY_UP)
						add_sprite();
					else if (event.keyboard.keycode == ALLEGRO_KEY_DOWN)
						remove_sprites(1);
					else if (event.keyboard.keycode == ALLEGRO_KEY_ESCAPE)
						return; // Encerra a execucao do programa
					break;
			// Indica que uma tecla foi pressionada por um tempo longo o suficiente
			// para "repetir" a acao. Este evento eh util quando se trabalhando
			// com uma interacao que requer uma entrada constante.
			// O campo "keycode" do evento "keyboard" contem uma constante que
			// representa a tecla.
			case ALLEGRO_EVENT_KEY_CHAR:
					if (event.keyboard.keycode == ALLEGRO_KEY_UP)
						add_sprite();
					else if (event.keyboard.keycode == ALLEGRO_KEY_DOWN)
						remove_sprites(1);
					else if (event.keyboard.keycode == ALLEGRO_KEY_ESCAPE)
						return;
					break;
			// Indica que o contador do timer foi incrementado.
			case ALLEGRO_EVENT_TIMER:
					update();
					break;
		}
	}
}


// Funcao principal.
int main(void)
{
	int bitmapSize;

	srand(time(0));

    // Funcao de inicializacao da Allegro
	al_init();

	// Chamada de funcao para forcar o uso de OpenGL ao inves de DirectX (DirectX eh o default)
	al_set_new_display_flags(ALLEGRO_OPENGL);

	// Funcao para criar uma janela com as dimensoes passadas como parametro, que torna-se
	// automaticamente ativa, com o backbuffer selecionado para desenho. Os parametros
	// da janela sao determinados pelas ultimas chamadas a "al_set_new_display_*".
    ALLEGRO_DISPLAY *display = al_create_display(600, 600);

	width = 600;  
	height = 600;

	// Inicializa the "Image IO addon", que tem funcoes declaradas no seguinte
	// header: #include <allegro5/allegro_image.h>
	al_init_image_addon();

	// Prototipo: ALLEGRO_BITMAP *al_load_bitmap(const char *filename)
	// Carrega uma imagem para a struct ALLEGRO_BITMAP. O tipo do 
	// arquivo é determinado pela extensao (bmp ou png).
	// "spacedragon1.png" is a sprite courtesy of Ari Feldman.
	dragon = al_load_bitmap("spacedragon1.png");
	if (!dragon) {
		std::cout << "Erro ao carregar a sprite spacedragon1.png\n";
      return 1;
	}

	add_sprites(3);

	// Funcao usada para especificar o titulo da janela.
//	al_set_window_title("Teste da Allegro com Sprites");

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

	// Destroi o bitmap liberando os recursos usados por ele
	al_destroy_bitmap(dragon);

    return 0;
}
