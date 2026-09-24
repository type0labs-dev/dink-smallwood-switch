void main( void )
{
 int &guy;
 int &what;
 &what = random(3,1);
 //Spawn the guy...
 &guy = create_sprite(258, 146, 0, 0, 0);
 sp_brain(&guy, 0);
 sp_base_walk(&guy, 410);
 sp_speed(&guy, 1);
 sp_timing(&guy, 0);
 //set starting pic
 sp_pseq(&guy, 417);
 sp_pframe(&guy, 1);
 //Coversation
 freeze(1);
 freeze(&guy);
 move_stop(1, 8, 222, 1);
 move_stop(&guy, 3, 265, 1);
 wait(250);
 if (&what == 1)
 {
  say_stop("`9Posso te ajudar em quê?", &guy);
  wait(250);
  say_stop("Uhh... talvez.", 1);
  wait(1000);
  say_stop("`9Ah é? Então que diabos você tá fazendo aqui?", &guy);
  wait(250);
  say_stop("Como assim?", 1);
  wait(250);
  say_stop("`9Tô dizendo que você entrou aqui sem bater, sem nada!", &guy);
  say_stop("`9Que história é essa?", &guy);
  wait(500);
  sp_dir(1, 2);
  wait(500);
  sp_dir(1, 8);
  wait(1000);
  say_stop("E tem alguma coisa... ERRADA nisso?", 1);
  wait(250);
  say_stop("`9TEM SIM, agora CAI FORA DAQUI!!", &guy);
 }
 if (&what == 2)
 {
  say_stop("`9Posso te ajudar em quê?", &guy);
  wait(250);
  say_stop("Não, só tô olhando as casas e tal.", 1);
  wait(750);
  say_stop("`9Sabe, você é muito folgado.", &guy);
  wait(250);
  say_stop("Tanto faz...", 1);
  wait(250);
  say_stop("`9Humpf.", &guy);
  wait(250);
  say_stop("Ei, velho, o pessoal do cemitério ligou...", 1);
  say_stop("já tão prontos pra te enterrar!", 1);
  wait(250);
  say_stop("`9QUÊ? Sai AGORA!!", &guy);
 }
 if (&what == 3)
 {
  say_stop("`9O que você quer?", &guy);
  wait(250);
  say_stop("Vim buscar sua filha.", 1);
  wait(250);
  say_stop("`9Por favor... só vai embora.", &guy);
 }
 //Leave.
 unfreeze(1);
 move_stop(1, 2, 640, 0);
  unfreeze(&guy);
}
