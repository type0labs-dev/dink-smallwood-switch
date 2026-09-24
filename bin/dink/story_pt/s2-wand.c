void main( void )
{
 int &pap;
 int &beat;
 &beat = 0;
 &pap = random(15, 1)
 if (&pap == 1)
 {
  say_stop("`4Olá, meu bom senhor.", &current_sprite);
 }
}

void talk( void )
{
 freeze(1);
 freeze(&current_sprite);
 choice_start()
 "Dizer oi"
 "Perguntar sobre suas histórias"
 "Ir embora"
 choice_end()
  if (&result == 1)
  {
   say_stop("Então, o que você faz?", 1);
   wait(250);
   say_stop("`4Bom, eu sou caçador.", &current_sprite);
   wait(250);
   say_stop("`4Espero encontrar umas peles boas por essas bandas.", &current_sprite);
   wait(250);
   say_stop("Boa profissão.", 1);
   wait(250);
   say_stop("Teve sorte ultimamente?", 1);
   wait(250);
   say_stop("`4Não, na real não. Tá meio estranho.", &current_sprite);
   wait(250);
   say_stop("`4Ando vendo um monte de monstro por aí ultimamente,", &current_sprite);
   wait(250);
   say_stop("`4parece que eles espantaram todos os bichos.", &current_sprite);
  }
  if (&result == 2)
  {
   &pap = random(2, 1);
   if (&pap == 1)
   {
    goto story1;
   }
   if (&pap == 2)
   {
    goto story2;
   }
  }
 unfreeze(1);
 unfreeze(&current_sprite);
}

void hit( void )
{
 if (&beat == 0)
 {
  &beat = 1;
  say_stop("`4Senhor, nãooo. Eu não gosto de levar porrada.", &current_sprite);
  return;
 }
 if (&beat == 1)
 {
  &beat = 2;
  say_stop("`4Estou avisando, senhor, pare com isso.", &current_sprite);
  return;
 }
 if (&beat == 2)
 {
  say_stop("`4Cansei, tô vazando!", &current_sprite);
  sp_speed(&current_sprite, 4);
  move_stop(&current_sprite, 3, 700, 1);
  freeze(&current_sprite);
  wait(500);
  say_stop("Falou.", 1);
  sp_active(&current_sprite, 0);
 }
}

void story1( void )
{
 story1:
 say_stop("`4Já ouvi muitas histórias estranhas na minha vida.", &current_sprite);
 wait(250);
 say_stop("`4Uma delas falava de uma ilha no mar.", &current_sprite);
 wait(250);
 say_stop("`4Onde humanos e dragões viviam juntos.", &current_sprite);
 wait(250);
 say_stop("`4E em paz, sem guerras, sem brigas.", &current_sprite);
 wait(250);
 say_stop("`4Diziam até que havia um túnel subterrâneo pra chegar lá.", &current_sprite);
 wait(250);
 say_stop("`4Dizem que era uma ilha linda de se visitar.", &current_sprite);
 wait(250);
 say_stop("`4Mas acho que não existe, é só uma lenda antiga.", &current_sprite);
 unfreeze(1);
 unfreeze(&current_sprite);
}

void story2( void )
{
 story2:
 say_stop("`4Há muito tempo, existia um castelo de goblins inteiro", &current_sprite);
 wait(250);
 say_stop("`4nessas terras.", &current_sprite);
 wait(250);
 say_stop("`4Dizem que eles lançavam ataque após ataque dali,", &current_sprite);
 wait(250);
 say_stop("`4aterrorizando a região.", &current_sprite);
 wait(250);
 say_stop("`4Mas um mago apareceu e lançou um feitiço poderoso no castelo.", &current_sprite);
 wait(250);
 say_stop("`4Tão forte que o teleportou para as terras geladas do norte.", &current_sprite);
 wait(250);
 say_stop("`4Provavelmente os goblins morreram no frio brutal.", &current_sprite);
 wait(250);
 say_stop("`4Fora isso, ninguém nunca mais ouviu falar do castelo.", &current_sprite);
 unfreeze(1);
 unfreeze(&current_sprite);
}
