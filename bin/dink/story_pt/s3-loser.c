void main( void )
{
sp_hitpoints(&current_sprite, 40);

}

void talk( void )
{
 freeze(1);
 freeze(&current_sprite);
 if (&mayor == 6)
 {
  say_stop("Ei, uhh ... cadê todo mundo?", 1);
  wait(250);
  say_stop("`6A parada já acabou, mano.", &current_sprite);
  wait(250);
  say_stop("`6Todo mundo vazou.", &current_sprite);
  wait(250);
  say_stop("Tão rápido assim?!?", 1);
  wait(250);
  say_stop("`6Sei lá, cara, eu só trabalho aqui.", &current_sprite);
  &mayor = 7;
  unfreeze(1);
  wait(500)
  unfreeze(&current_sprite);
  return;
 }
 if (&mayor == 7)
 {
  say_stop("Ei, uhh ... cadê todo mundo?", 1);
  wait(250);
  say_stop("`6Já te falei, parceiro, eles foram embora.", &current_sprite);
  wait(250);
  say_stop("`6Cê é o quê, algum tipo de esquisito?", &current_sprite);
  wait(250);
  say_stop("Entendi ...", 1);
 }
 unfreeze(1);
 wait(500)
 unfreeze(&current_sprite);
}

void hit( void )
{
 freeze(&current_sprite);
 say_stop("`6Tipo, aaaai mano.", &current_sprite);
 wait(500);
 unfreeze(&current_sprite);
}
