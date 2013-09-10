// Programa que exemplica como utilizar a Allegro. Quando executado, abre
// uma janela de teste por 5 segundos exibindo uma imagem nela.
//
// Curso de Especializacao em Desenvolvimento de Jogos Digitais
// Disciplina: Programacao 2D
// Professores: Isabel H. Manssour e Marcio S. Pinho

#include <iostream>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_opengl.h>

int main(void)
{
    // Funcao de inicializacao da Allegro
     al_init();

     // Funcao para forcar o uso de OpenGL ao inves de DirectX (DirectX eh o default)
     al_set_new_display_flags(ALLEGRO_OPENGL);

     // Funcao para criar uma janela com as dimensoes passadas como parametro, que torna-se
     // automaticamente ativa, com o backbuffer selecionado para desenho. Os parametros
     // da janela sao determinados pelas ultimas chamadas a "al_set_new_display_*".
     ALLEGRO_DISPLAY *display = al_create_display(800, 600);

     // Prototipo da funcao: void al_clear_to_color(ALLEGRO_COLOR color)
     // Limpa o bitmap de destino e recebe por parametro uma referencia para a struct
     // ALLEGRO_COLOR, que descreve a cor em um dispositivo de forma independente.
     // ALLEGRO_COLOR al_map_rgb(unsigned char r, unsigned char g, unsigned char b)
     // eh a funcao usada para converter uma cor RGB para uma struct ALLEGRO_COLOR.
     al_clear_to_color(al_map_rgb(0, 0, 0));

     // Inicializa the "Image IO addon", que tem funcoes declaradas no seguinte
     // header: #include <allegro5/allegro_image.h>
     al_init_image_addon();

     // Prototipo: ALLEGRO_BITMAP *al_load_bitmap(const char *filename)
     // Carrega uma imagem para a struct ALLEGRO_BITMAP. O tipo do
     // arquivo eh determinado pela extensao (bmp ou png).
     ALLEGRO_BITMAP *img = al_load_bitmap("gnu.png");

     // Verifica se deu problema ou nao e notifica o usuario.
     if (!img)
         std::cout << "Problemas na carga da imagem !";
     else
         std::cout << "Imagem carregada!";


     // Prototipo: void al_draw_bitmap(ALLEGRO_BITMAP *bitmap, float dx, float dy, int flags)
     // Desenha um bitmap sem escala e sem rotacao na posicao (dx,dy) passada por parametro
     al_draw_bitmap(img, 10, 10, 0);

     // Copia ou atualiza os buffers, assim o que foi desenhado previamente fica visivel na tela.
     al_flip_display();

     // Faz uma pausa pelo numero de segundos passado por parametro.
     al_rest(5);

     // Destroi o bitmap liberando os recursos usados por ele
     al_destroy_bitmap(img);

    return 0;
}

