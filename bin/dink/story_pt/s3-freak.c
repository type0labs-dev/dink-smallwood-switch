void main( void )
{
 int &force;
 &temp1hold = sp(33);
 &temp2hold = sp(34);
 &temp3hold = sp(35);
 &temp4hold = sp(36);

if (get_sprite_with_this_brain(3, &current_sprite) == 0)
 {
  //no more brain 3 (ducks) on the screen.
    say("`9Assassino!", &current_sprite);

 }



sp_frame_delay(&current_sprite, 30);
 start:

if (get_sprite_with_this_brain(3, &current_sprite) == 0)
 {
  //no more brain 3 (ducks) on the screen.
  &force = random(4, 1);
  if (&force == 1)
  {
   &force = random(4, 1);
   if (&force == 1)
   {
    say("`9Cadê vocês, seus danadinhos?", &current_sprite);
   }
   if (&force == 2)
   {
    say("`9Meus patos!!!!!!!! TODOS MORTOS!!!!!!! DROGA!", &current_sprite);
   }
   if (&force == 3)
   {
    say("`9CAI FORA DAQUI!!!!!", &current_sprite);
   }
   if (&force == 4)
   {
    say("`9Lá se vão minhas chances de impressionar a filha do prefeito!!!!", &current_sprite);
   }
  }
 goto loser;
 }


  &force = random(4, 1);
  if (&force == 1)
  {
   &force = random(4, 1);
   if (&force == 1)
   {
    say("`9Esse desfile vai ser foda!!!", &current_sprite);
   }
   if (&force == 2)
   {
    say("`9Eu amo meus patos.", &current_sprite);
   }
   if (&force == 3)
   {
    say("`9Prontos pro nosso número, companheiros?", &current_sprite);
   }
   if (&force == 4)
   {
    say("`9Me preparando pra detonar!!", &current_sprite);
   }
  }
loser:
  move_stop(&current_sprite, 6, 530, 1);
  move_stop(&current_sprite, 4, 100, 1);
//wait(800);
  goto start;
}

void talk( void )
{

if (get_sprite_with_this_brain(3, &current_sprite) == 0)
 {
    say("`9Cai fora!! Você arruinou completamente o meu número!", &current_sprite);
    goto start;
 }



 freeze(1);
 freeze(&current_sprite);
 say_stop("`9Que que você quer, cara? Preciso continuar andando!", &current_sprite);
 choice_start()
(&mayor < 6)"Perguntar por que ele está correndo"
(&mayor < 6)"Perguntar sobre os patos"
(&mayor > 5)"Perguntar sobre o desfile"
 "Sair"
 choice_end()

  if (&result == 1)
  {
  say_stop("Por que você tá correndo tão rápido?", 1);
  wait(250);
  say_stop("`9Porque eu tô animado!!", &current_sprite);
  wait(250);
  say_stop("Animado com o quê?", 1);
  wait(250);
  say_stop("`9Com o grande desfile que vai rolar em breve, cara!!", &current_sprite);
  wait(250);
  say_stop("`9Vai ser foda!!!!!!", &current_sprite);
  }
  if (&result == 2)
  {
  say_stop("O que que há com todos esses patos?", 1);
  wait(250);
  say_stop("`9Ah, eles são meus bichos de estimação. A gente vai desfilar junto.", &current_sprite);
  wait(250);
  say_stop("Entendi ...", 1);
  wait(250);
  say_stop("`9Quer ver o que a gente faz?", &current_sprite);
  wait(250);
  say_stop("Nem quero.", 1);
  wait(250);
  say_stop("`9Beleza, lá vai ...", &current_sprite);
  wait(250);
  say_stop("`9Prontos, galera? Sigam-me!", &current_sprite);
  sp_follow(&temp1hold, &current_sprite);
  sp_follow(&temp2hold, &current_sprite);
  sp_follow(&temp3hold, &current_sprite);
  move_stop(&current_sprite, 4, 100, 1);
  move_stop(&current_sprite, 6, 530, 1);
  say("Ei..", 1);
  move_stop(&current_sprite, 4, 100, 1);
  move_stop(&current_sprite, 6, 300, 1);
  say_stop("`9Que foi?", &current_sprite);
  wait(250);
  say_stop("O que tem aquele outro ali?", 1);
  wait(250);
  say_stop("`9Ah ...", &current_sprite);
  wait(250);
  say_stop("`9ele tem problemas.", &current_sprite);
  unfreeze(&current_sprite);
  wait(1000);
  sp_dir(1, 2);
  say_stop("Eita ...", 1);
  }
  if (&result == 3)
  {
  say_stop("Então... não te vi no desfile.", 1);
  wait(250);
  say_stop("`9Ah.. hehe.. é, eu uhh... eu...", &current_sprite);
  wait(250);
  say_stop("`9um dos patos ficou doente, e bom... a gente não pôde se apresentar.", &current_sprite);
  wait(250);
  sp_dir(1, 2);
  wait(1000);
  sp_dir(1, 4);
  say_stop("Tô ligado. Que pena, depois de tanto treino.", 1);
  wait(250);
  say_stop("`9Bom, ei, não se preocupa...", &current_sprite);
  wait(250);
  say_stop("`9a gente tá treinando pro ano que vem.", &current_sprite);
  wait(250);
  say_stop("Caramba...", 1);
  unfreeze(&current_sprite);
  wait(500);
  sp_dir(1, 2);
  say_stop("Nota mental: Não voltar aqui no ano que vem.", 1);
  }
 unfreeze(1);
 unfreeze(&current_sprite);
 goto start;
}
