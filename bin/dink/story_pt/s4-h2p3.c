void main( void )
{
}

void talk( void )
{
 freeze(1);
 freeze(&current_sprite);
 if (&story > 10)
 {
  say_stop("Oi, garotinha...", 1);
  wait(250);
  say_stop("`1Oi, moço! Valeu por deixar a gente comer.", &current_sprite);
  wait(250);
  say_stop("De nada.", 1);
  unfreeze(1);
  unfreeze(&current_sprite);
  return;
 }
 choice_start()
 "Dizer oi"
 "Perguntar sobre comida"
 "Deixa pra lá"
 choice_end()
  if (&result == 1)
  {
   say_stop("Oi, garotinha...", 1);
   wait(250);
   say_stop("`1Oi, moço.", &current_sprite);
  }
  if (&result == 2)
  {
   say_stop("Você consegue comer bastante, garotinha?", 1);
   wait(250);
   say_stop("`1Ultimamente não, mamãe diz que a gente não pode comer muito,", &current_sprite);
   say_stop("`1por causa dos patos.", &current_sprite);
   wait(250);
   say_stop("`1Eu não gosto dos patos.", &current_sprite);
  }
 unfreeze(1);
 unfreeze(&current_sprite);
}

void hit( void )
{
 say_stop("`2Não, moço!", &current_sprite);
}
