#include <iostream>
#include <allegro5/allegro.h>
#include <allegro5/allegro_opengl.h>

// Funcao que contem os comandos OpenGL para fazer o desenho de um triangulo vermelho na janela
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
     glOrtho(-100, 100, -100, 100, -1, 1);
 
     // Inicializa sistema de coordenadas do modelo
     glMatrixMode(GL_MODELVIEW);
     glLoadIdentity();
 
     // Desenha um triangulo vermelho no centro da janela
     glColor3f(1, 0, 0);
     glBegin(GL_TRIANGLES);
         glVertex2f(-50, -50);
         glVertex2f(  0,  50);
         glVertex2f( 50, -50);
     glEnd();
}

int main()
{
	al_init();

	al_set_new_display_flags(ALLEGRO_OPENGL);

	ALLEGRO_DISPLAY *display = al_create_display(800, 600);

	al_clear_to_color(al_map_rgb(0,0,0));

	draw_opengl();

	al_flip_display();

	al_rest(5);
}
