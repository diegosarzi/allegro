#include <stdio.h>
#include <allegro5/allegro.h>

int main(){
//------------------------------------------------------    
    allegro_init();
    install_keyboard();
    set_color_depth(32);
    set_gfx_mode(GFX_AUTODETECT_WINDOWED, 640,480,0,0);
    
//------------------------------------------------------
    int xpersonagem = 0;
    int ypersonagem = 380;
    int gravidade = 1;
    int fpulo = 30; 
    int alturazero = 380;
           

//------------------------------------------------------    
    BITMAP *buffer;
    buffer = create_bitmap(640,480);
    
    BITMAP *imagem;
    imagem = create_bitmap(640,480);
    rectfill(imagem,0,0,640,480,makecol(150,150,255));
    
    BITMAP *nuvem;
    nuvem = load_bitmap("nuvem.bmp",NULL);
    
    BITMAP *grama;
    grama = load_bitmap("gramaimg.bmp",NULL);
    
    BITMAP *personagem;
    personagem = load_bitmap("pimg.bmp",NULL);
    
    
//----------------------------------------------------
    draw_sprite(imagem, grama, 0,430);
    draw_sprite(imagem, grama, 50,430);
    draw_sprite(imagem, grama, 100,430);
    draw_sprite(imagem, grama, 150,430);
    draw_sprite(imagem, grama, 200,430);
    draw_sprite(imagem, grama, 250,430);
    draw_sprite(imagem, grama, 300,430);
    draw_sprite(imagem, grama, 350,430);
    draw_sprite(imagem, grama, 400,430);
    draw_sprite(imagem, grama, 450,430);
    draw_sprite(imagem, grama, 500,430);
    draw_sprite(imagem, grama, 550,430);
    draw_sprite(imagem, grama, 600,430);
    draw_sprite(imagem, grama, 650,430);
    
    draw_sprite(imagem, nuvem,100,200);
    draw_sprite(imagem, nuvem,400,50);
    draw_sprite(buffer, imagem,0,0);
    draw_sprite(buffer,personagem, xpersonagem,ypersonagem);
    draw_sprite(screen, buffer,0,0);
    

    while(!key[KEY_ESC]){
           
           clear(buffer);              
           draw_sprite(imagem, nuvem,100,200);
           draw_sprite(imagem, nuvem,400,50);
           draw_sprite(buffer, imagem,0,0);
           draw_sprite(buffer,personagem, xpersonagem,ypersonagem);
           draw_sprite(screen, buffer,0,0);              
   
                 
           if(key[KEY_A]){
             
              xpersonagem = xpersonagem-5;
                                       
              }
           if(key[KEY_D]){
            
              xpersonagem = xpersonagem+5;
                                       
              }
              
              if(key[KEY_SPACE]){
              
              ypersonagem = ypersonagem-fpulo;
              gravidade=gravidade+2;
                                      
              }
              
              if(ypersonagem>alturazero){ //para a gravidade quando chega no chão.
                 gravidade=0;
                 
                 }
              
              if(ypersonagem<alturazero){ //aumenta a gravidade conforme a altura.
                 gravidade=gravidade+1;
                 }
              
              ypersonagem = ypersonagem+gravidade; //puxa o personagem para baixo.
              
              
              
                         
    } //fim do while esc
    
    allegro_exit();
    return 0;
    
}END_OF_MAIN();
