void main( void )
{
preload_seq(371);
preload_seq(373);
int &myrand;
sp_brain(&current_sprite, 0);
sp_base_walk(&current_sprite, 370);
sp_speed(&current_sprite, 2);
sp_timing(&current_sprite, 0);
//set starting pic

sp_pseq(&current_sprite, 371);
sp_pframe(&current_sprite, 1);
}

void talk( void )
{
 freeze(1);
 choice_start()
 "Falar oi"
(&thief == 0) "Perguntar o que ele faz"
(&thief == 1) "Se oferecer pra ajudar"
 "Vazar"
 choice_end()

 if (&result == 1)
 {
  wait(400);
  say_stop("E aí, beleza?", 1);
  wait(400);
  say_stop("`2Cê é o cara pro serviço?", &current_sprite);
  wait(400);
  say_stop("Ué, que serviço?", 1);
  wait(400);
  say_stop("`2Ah, deixa pra lá.", &current_sprite);
  say("`2Ahh, cadê aquele cara?!", &current_sprite);
  unfreeze(1);
 }
 if (&result == 2)
 {
  wait(400);
  say_stop("Então, o que cê faz, parça?", 1);
  wait(400);
  say_stop("`2Eu?", &current_sprite);
  wait(400);
  say_stop("Isso, eu mesmo. Se liga, sou aventureiro.", 1);
  wait(400);
  say_stop("`2Hehe, é... eu sou um... um especialista.", &current_sprite);
  wait(400);
  say_stop("Ah, e no que cê é especialista?", 1);
  wait(400);
  say_stop("`2Digamos que eu ajudo a adquirir certas coisas...", &current_sprite);
  wait(400);
  say_stop("Ah, entendi. E o que cê tá adquirindo agora?", 1);
  wait(400);
  say_stop("`2Nada que deva te interessar.", &current_sprite);
  wait(400);
  say_stop("`2Agora segue seu caminho.", &current_sprite);
  //Set it up
  &thief = 1;
 }
 if (&result == 3)
 //Helping the guy out!!
 {
  wait(400);
  say_stop("`2De novo você?", &current_sprite);
  wait(400);
  say_stop("Seja lá o que for que cê tá fazendo... eu posso te ajudar.", 1);
  wait(400);
  say_stop("`2VOCÊ?!?", &current_sprite);
  wait(400);
  say_stop("`2Cê tá certo disso?", &current_sprite);
  wait(400);
  say_stop("Pode crer, eu sei fazer um monte de coisas.", 1);
  wait(400);
  say_stop("`2Hmmmmm", &current_sprite);
  wait(400);
  say_stop("`2Bom, acho que meu outro contato não vai aparecer.", &current_sprite);
  wait(400);
  say_stop("`2Então cê tá dentro.", &current_sprite);
  wait(400);
  say_stop("`2Me encontra a oeste daqui quando estiver pronto", &current_sprite);
  move_stop(&current_sprite, 4, 317, 1);
  move_stop(&current_sprite, 2, 430, 1);
  unfreeze(1);                                         
  &thief = 2;
  sp_active(&current_sprite, 0);
 }
unfreeze(1);                                         
}
