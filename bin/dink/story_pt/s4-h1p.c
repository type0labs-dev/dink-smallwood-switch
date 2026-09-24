void main( void )
{
 preload_seq(514);
 preload_seq(70);
 int &talker;
 int &junk;
 &talker = 0;
 move(1, 6, 157, 1);
 freeze(&current_sprite);
 freeze(1);
 if (&story > 10)
 {
  unfreeze(&current_sprite);
  unfreeze(1);
  return;
 }
 say("`7AHHHHH!!!!!!", &current_sprite);
 wait(250);
 //Fire here
 playsound(42,22050,0,0,0);
 &junk = create_sprite(385, 151, 11, 506, 1);
 sp_seq(&junk, 514); 
 sp_dir(&junk, 4);
 sp_speed(&junk, 4);
 sp_flying(&junk, 1);
 say("AHHHHH!!!!!", 1);
 wait(290);
 move(1, 2, 240, 1);
 wait(560);
 sp_active(&junk, 0);
 &junk = create_sprite(157, 131, 7, 168, 1);
 sp_seq(&junk, 70);
 playsound(37,22050,0,0,0);
 wait(1200);
 sp_dir(1, 6);
 wait(500);
 say_stop("Que porra é essa?!?", 1);
 wait(250);
 say_stop("`7Desculpa aí.", &current_sprite);
 unfreeze(1);
 unfreeze(&current_sprite);
 //end
}

void talk( void )
{
 if (&story > 10)
 {
  freeze(&current_sprite);
  freeze(1);
  say_stop("`7Ah, Dink. Como vai, meu garoto, como vai.", &current_sprite);
  say_stop("`7Muito obrigado por salvar nossa cidade.", &current_sprite);
  wait(250);
  say_stop("Ei, sem problema.", 1);
  wait(250);
  unfreeze(1);
  unfreeze(&current_sprite);
  return;
 }
 if (&talker == 2)
 {
  freeze(1);
  say_stop("`7Já cansei de falar com você, tenho coisas mais importantes pra me preocupar.", &current_sprite);
  wait(250);
  say_stop("Hmmm.", 1);
  unfreeze(1);
  return;
 }
 freeze(1);
 freeze(&current_sprite);
 choice_start()
"Perguntar o que houve"
"Perguntar sobre a cidade"
 "Sair"
 choice_end()
  if (&result == 1)
  {
   say_stop("Ei, valeu pela bola de fogo!", 1);
   say_stop("Que porra tá errada com você?", 1);
   wait(250);
   say_stop("`7Eu... Eu sinto muito, pensei que você fosse outra pessoa.", &current_sprite);
   wait(250);
   say_stop("Tipo quem?!?", 1);
   wait(250);
   say_stop("`7Tipo outro saqueador vindo pegar minha comida.", &current_sprite);
   say_stop("`7Tenho que me defender.", &current_sprite);
   wait(250);
   say_stop("Essa cidade é uma bagunça.", 1);
   &talker = 1;
  }
  if (&result == 2)
  {
   &junk = sp_dir(1, -1);
   say_stop("Então, qual é a dessa cidade aqui?", 1);
   wait(250);
   say_stop("`7Nós, nós todos adoramos o pato aqui.", &current_sprite);
   sp_dir(1, 2);
   wait(1000);
   say_stop("Ok, vou me virar de volta pra você...", 1);
   say_stop("e dessa vez você vai dar uma resposta normal.", 1);
   wait(250);
   say_stop("Preparado....", 1);
   sp_dir(1, &junk);
   wait(750);
   say_stop("`7Nós todos adoramos o pato aqui.", &current_sprite);
   wait(1000);
   say_stop("É...", 1);
   say_stop("Isso é algum tipo de religião?", 1);
   wait(250);
   say_stop("`7Sim, devemos tudo ao pato e damos tudo ao pato.", &current_sprite);
   wait(250);
   say_stop("Bem, tudo bem então, eu... eu volto a falar com você sobre isso.", 1);
   &talker = 2;
  }
 unfreeze(1);
 unfreeze(&current_sprite);
}

void hit( void )
{
 if (&story > 10)
 {
  freeze(&current_sprite);
  say_stop("`7Ah, que herói você é!", &current_sprite);
  unfreeze(&current_sprite);
  return;
 }
 freeze(&current_sprite);
 say_stop("`7Ahhh, para com isso!", &current_sprite);
 unfreeze(&current_sprite);
}
 