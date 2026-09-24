void main( void )
{
}

void touch( void )
{

 freeze(1);
 move_stop(1, 6, 300,1 );
 sp_dir(1,4);
 if (&caveguy == 2)
 {
 say_stop("Parece que é aqui, mas tá trancado.", 1);
 say_stop("Talvez eu deva tentar bater na porta..", 1);
 unfreeze(1);

 return;
 }

 if (&caveguy == 3)
 {
 say_stop("Tomara que aquele velho chato me dê essa magia.", 1);
 unfreeze(1);
 return;
 }

 say("Tá trancado.", 1);
 unfreeze(1);
}

void hit( void )
{
 goto knocked;
}

void talk( void )
{
 knocked:

 if (&caveguy == 2)
 {
 int &me;
 &me = &current_sprite;
 script_attach(1000);
 freeze(1);
 wait(500);
  playsound(45, 12000, 0,0,0);
 wait(500);
 say_stop("Ô de casa! Tem alguém aí?", 1);
 wait(500);
 say_stop("E aí?!?", 1);
 wait(300);
 say_stop("`0Quem quer saber?", &me);
 wait(300);
 say_stop("Eu.. Eu sou o Dink Smallwood, tô tentando ajudar...", 1);
 wait(200);
 say_stop("um coitado que tá preso na masmorra ao sul daqui.", 1);
 wait(300);
 say_stop("`0Jovem Maulwood, as pessoas se metem em lugares que não deviam toda hora.", &me);
 wait(200);
 say_stop("`0Por que eu deveria me importar com o que acontece com esse cara?", &me);
 wait(500);
 sp_dir(1, 2);
 wait(500);
 sp_dir(1, 4);
 wait(500);
 say_stop("É Smallwood, senhor, e ele diz...", 1);
 wait(200);
 say_stop("que foi preso por agentes do Conselho e que a tranca só pode ser aberta com magia!", 1);
 wait(300);
 say_stop("`0Cê tá fumando?", &me);
 wait(300);
 say_stop("Não.", 1);
 say_stop("`0Ah.", &me);
 wait(200);
 say_stop("`0Bem, se esses caras do Conselho tão envolvidos, é melhor eu ajudar.", &me);
 wait(200);
 say_stop("`0Entra.", &me);
 fade_down();
 fill_screen(0);
 //move Dink
 &player_map = 38;
 sp_x(1, 261);
 sp_y(1, 350);
 load_screen();
 draw_screen();
 draw_status();
 fade_up();
 kill_this_task();
 return;
 }
 if (&caveguy == 3)
 {
 int &me;
 &me = &current_sprite;
 script_attach(1000);
 freeze(1);
  playsound(45, 12000, 0,0,0);
  wait(700);
 say_stop("E aí, voltei!", 1);
 wait(300);
 say_stop("`0Ah, sim, Smallwand, entra..", &me);
 fade_down();
 fill_screen(0);
 //move Dink
 &player_map = 38;
 sp_x(1, 261);
 sp_y(1, 350);
 load_screen();
 draw_screen();
 draw_status();
 fade_up();
 kill_this_task();
  return;
 }

 freeze(1);
 wait(500);
  playsound(45, 12000, 0,0,0);
 wait(500);
 say_stop("Ó de casa! Tem alguém aí?", 1);
  unfreeze(1);

}
