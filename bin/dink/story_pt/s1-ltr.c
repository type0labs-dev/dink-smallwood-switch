void main ( void )
{
//this script needs to survive a screen load, lets unattach it from the
//letter

int &mycur = &current_sprite;

  script_attach(1000);

 //1000 means can't be killed unless we do it, but now &current_sprite
 //won't work..

 freeze(1);
 &letter = 2;
 &story = 6;
 wait(2000);
 say_stop("`2Querido Dink,", &mycur);
 wait(250);
 say_stop("`2Acabamos de saber do trágico acidente que aconteceu na...", &mycur);
 say_stop("`2sua casa há um tempinho. Nem preciso dizer que estamos chocados.", &mycur);
 say_stop("`2Isso deve estar sendo difícil pra você, sendo tão novo e sofrendo...", &mycur);
 say_stop("`2uma perda tão grande. Você é super bem-vindo pra vir ficar...", &mycur);
 say_stop("`2com a gente em Terris por um tempo. Acho que o Jack não vai se importar.", &mycur);

 say_stop("`2Com carinho, Tia Maria Kneedlewood", &mycur);
 wait(500);
 say_stop("Hmm... Terris. Acho que é a oeste daqui.", 1);
 wait(500);
 say_stop("Ei! Veio um mapa junto!", 1);
 wait(500);
 &s2-map = 1;
 say_stop_xy("`%(Veja o mapa no menu de pausa)", 20,380);
 fade_down();
 fill_screen(0);
 //move Dink
 &player_map = 439;
 sp_x(1, 362);
 sp_y(1, 303);
 load_screen();
 draw_screen();
 draw_status();
 fade_up();
 unfreeze(1);

 kill_this_task();
}
