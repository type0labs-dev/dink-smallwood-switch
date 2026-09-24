void main( void )
{
 if (&caveguy == 5)
 {
  script_attach(1000);
  //preload_seq(740);  <-- for sucking.
preload_seq(375);
  preload_seq(168);
  int &junk;
  int &dude;
  int &evil;
  int &evil2;
  int &evil3;
  freeze(1);
  &dude = create_sprite(551, 157, 0, 0, 0);
  sp_brain(&dude, 0);
  sp_base_walk(&dude, 370);
  sp_speed(&dude, 2);
  sp_timing(&dude, 0);
  //set starting pic
  sp_pseq(&dude, 371);
  sp_pframe(&dude, 1);
  //Now EVIL
  &evil = create_sprite(-20, 130, 0, 0, 0);
  sp_brain(&evil, 0);
  sp_base_walk(&evil, 300);
  sp_speed(&evil, 1);
  sp_timing(&evil, 0);
  //set starting pic
  sp_pseq(&evil, 303);
  sp_pframe(&evil, 1);
  //Now EVIL's friend
  &evil2 = create_sprite(-20, 210, 0, 0, 0);
  sp_brain(&evil2, 0);
  sp_base_walk(&evil2, 300);
  sp_speed(&evil2, 1);
  sp_timing(&evil2, 0);
  //set starting pic
  sp_pseq(&evil2, 303);
  sp_pframe(&evil2, 1);
  //And the third EVIL
  &evil3 = create_sprite(300, 470, 0, 0, 0);
  sp_brain(&evil3, 0);
  sp_base_walk(&evil3, 300);
  sp_speed(&evil3, 1);
  sp_timing(&evil3, 0);
  //set starting pic
  sp_pseq(&evil3, 307);
  sp_pframe(&evil3, 1);
  Playmidi("1004.mid");
  say_stop("`5Beleza, vamos nessa antes que eles cheguem.", &dude);
  wait(500);
  say_stop("`5Por aqui.", &dude);
  move(&dude, 4, 500, 1);
  wait(50);
  move(1, 4, 550, 1);
  wait(150);
  say("`4Calma aí, mermão.", &evil);
  move(&evil, 6, 100, 1);
  wait(850);
  move(&evil3, 8, 380, 1);
  move_stop(&evil2, 6, 67, 1);
  say_stop("`4A gente tem um assunto pra resolver com seu amigo aí.", &evil);
  say("`4Hahahaaahaha", &evil);
  say("`4Haha ha ha", &evil2);
  say_stop("`4Ha ha haaa", &evil3);
  wait(800);
  sp_dir(&dude, 3);
  say_stop("`5Tranquilo, Dink, eu dou conta deles.", &dude);
  wait(250);
  say("`5Beleza.", &dude);
  move_stop(&dude, 4, 400, 1);
  sp_dir(&dude, 1);
  say_stop("`5Qual de vocês vai ser o primeiro?", &dude);
  wait(250);
  say("`4Haha ha ha", &evil2);
  wait(500);
  say_stop("`4Ha ha haaa", &evil3);
  wait(500);
  say_stop("`4Sou eu!!", &evil);
  move_stop(&evil, 2, 157, 1);
  move_stop(&evil, 6, 170, 1);
  wait(500);
  //say("`4Ahhhhhh!", &evil);
  &junk = create_sprite(240, 157, 11, 506, 1);
  sp_seq(&junk, 506); 
  sp_dir(&junk, 6);
  sp_speed(&junk, 6);
  sp_flying(&junk, 1);
  wait(390);
  sp_active(&junk, 0);
  &junk = create_sprite(390, 157, 7, 168, 1);
  sp_seq(&junk, 168);
  sp_pseq(&dude, 375);
  sp_pframe(&dude, 1);

  say_stop("`5Nãoooo!!", &dude);
  wait(50);
  sp_active(&junk, 0);
  //Kill guy too

  say("Haha ha ha", 1);
  move(1, 4, 450, 1);
  wait(500);
  say("`4Ha ha haaa", &evil2);
  say_stop("`4Nosso trabalho aqui tá feito.", &evil3);
  wait(500);
   say_stop("`4Você sai vivo, se esquecer tudo o que viu aqui.", &evil);
   wait(500);
   say_stop("`4Esquecer ...", &evil);
   wait(250);
   say_stop("Vou esquecer sim... nunca nem vi!", 1);
   wait(500);
   say_stop("...Só se for esquecer de meter a mão na tua FUÇA!!", 1);
   wait(250);
   move(&evil, 4, -20, 1);
   wait(360);
   move(&evil2, 4, -20, 1);
   move_stop(&evil3, 4, 180, 1);
   move_stop(&evil3, 2, 470, 1);
   sp_active(&evil, 0);
   sp_active(&evil2, 0);
   sp_active(&evil3, 0);
   wait(250);
   say_stop("Você tá bem?", 1);
   wait(500);
   say_stop("Tomei uma bola de fogo em cheio...", 1);
   wait(500);
   say_stop("`5Já era, vou bater as bota!", &dude);
   wait(500);
   say_stop("`5Pô cara, desculpa, não cheguei a tempo.", &dude);
   wait(250);
   say_stop("Não é culpa sua...", 1);
   wait(500);
   say_stop("`5Só... toma muito cuidado... e ó, pega isso aqui...", &dude);
   wait(500);
   say_stop("`5Caraca.. o que é isso?", &dude);
   wait(500);
   say_stop("O pergaminho de Mordavia. Tem a magia que precisava pra...", 1);
   wait(500);
   say_stop("`5Ahhhhhh.", &dude);
   say_stop("`5Pô, mano...", &dude);
   wait(1000);
   say_stop("Pô, mano...", 1);
  sp_active(&dude, 0);
  &caveguy = 6;
  add_magic("item-p1", 438,14);
  &story = 7;
  unfreeze(1);
  //Fade
  fade_down();
  fill_screen(0);
  //move Dink
  &player_map = 625;
  sp_x(1, 268);
  sp_y(1, 173);
  sp_dir(1, 8);
  load_screen();
  draw_screen();
  draw_status();
  fade_up();
  kill_this_task();
 }
}
