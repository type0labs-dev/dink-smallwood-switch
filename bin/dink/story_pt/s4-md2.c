void main( void )
{
}

void touch( void )
{
 if (&story > 10)
 {
  move_stop(1, 4, 397,1 );
  sp_dir(1, 6);
  say_stop("`6Ahh Dink, valeu, valeu!", &current_sprite);
  return;
 }
 freeze(1);
 move_stop(1, 4, 397,1 );
 sp_dir(1, 6);
 say_stop("`6Quem tá aí?", &current_sprite);
 wait(250);
 say_stop("Meu nome é Dink.", 1);
 wait(250);
 say_stop("`6Deixa isso pra lá.", &current_sprite);
 say_stop("`6Cê tem comida?", &current_sprite);
 wait(250);
 say_stop("Nada ...", 1);
 wait(250);
 say_stop("`6Preciso de comida!", &current_sprite);
 wait(250);
 say_stop("Foi mal ...", 1);
 wait(250);
 say_stop("`6Então cai fora!!", &current_sprite);
 unfreeze(1); 
}
