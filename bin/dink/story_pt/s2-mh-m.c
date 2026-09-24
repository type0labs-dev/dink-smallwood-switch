void main( void )
{
 freeze(1);
 freeze(&current_sprite);

 say_stop("`0Bem-vindo, jovem BallWood.", &current_sprite);
 wait(250);
 say_stop("É Smallwood, senhor.", 1);
 say_stop("`0Sim, e o que você queria mesmo?", &current_sprite);
 unfreeze(1);
  unfreeze(&current_sprite);
}

void talk( void )
{
 if (&caveguy == 2)
 {
  freeze(1);
 freeze(&current_sprite);
  say_stop("Por favor, me ensine um feitiço de encantamento poderoso pra caramba!", 1);
  wait(250);
  say_stop("Quer dizer, pra ajudar o cara preso na masmorra.", 1);
  wait(250);
  if (&magic > 4)
  {
   say_stop("`0Sinto que você já tá poderoso o bastante agora, Tallwood.", &current_sprite);
  wait(250);
   say_stop("`0Você vai aprender a mágica da Chuva Ácida.", &current_sprite);
  wait(250);
  say_stop("Chuva? Só isso? Essa é a grande mágica que você vai me ensinar?", 1);
  wait(250);
   say_stop("`0Não debocha, garoto, ou você vai se queimar todo e se ferrar com ela!", &current_sprite);
   //Give magic here
   add_magic("item-ice",437, 5);

   //SETH!!!
   //Give magic here
   //This magic will allow Dink to free the guy in the cave ..
   //Even though the guy only walks a few feet to be killed again anyway...
   //Ooops
   playsound(22,22050,0,0,0);
   &caveguy = 4;
   say_stop("Agora eu tenho a Mágica da Chuva. Eba.", 1);
   unfreeze(1);
  unfreeze(&current_sprite);
     return;
  }
  say_stop("`0Desculpa, Smallweed, mas sua mágica ainda não é poderosa o bastante.", &current_sprite);
  wait(250);
  say_stop("`0Você precisa ter pelo menos 5 de mágica pra aprender o novo feitiço.", &current_sprite);
  &caveguy = 3;
  unfreeze(1);
  unfreeze(&current_sprite);
  return;
 }
 if (&caveguy == 3)
 {
 freeze(&current_sprite);
  freeze(1);
  //First check him
  if (&magic > 4)
  {
   say_stop("`0Sinto que você já tá poderoso o bastante agora, Tallwood.", &current_sprite);
   wait(250);
   say_stop("`0Você vai aprender a mágica da Chuva Ácida.", &current_sprite);
  wait(250);
  say_stop("Chuva? Só isso? Essa é a grande mágica que você vai me ensinar?", 1);
  wait(250);
   say_stop("`0Não debocha, garoto, ou você vai se queimar todo e se ferrar com ela!", &current_sprite);
   //Give magic here
   add_magic("item-ice",437, 5);
   playsound(10,22050,0,0,0);
   &caveguy = 4;
   say_stop("Agora eu tenho a Mágica da Chuva. Eba.", 1);

   unfreeze(1);
  unfreeze(&current_sprite);
    return;
  }
  //Otherwise
  say_stop("`0Você ainda não é poderoso o bastante, Brickwood.", &current_sprite);
  wait(250);
  say_stop("Smallwood, senhor.", 1);
  wait(250);
  say_stop("`0Você precisa de 5 de mágica pra esse feitiço.", &current_sprite);
  wait(500);
  sp_dir(1, 2);
  wait(500);
  say_stop("Ah, que saco!", 1);
  unfreeze(1);
  unfreeze(&current_sprite);
  return;
 }
 freeze(1);
 freeze(&current_sprite);
 say_stop("Ei, seu velho, sabe mais alguma mágica que pode me ensinar?", 1);
 wait(250);
 say_stop("`0Não, Smallwood, tô velho e cansado demais pra isso.", &current_sprite);
 wait(250);
 say_stop("Ok, sem problema... e meu nome não é... ah, deixa.", 1);

 unfreeze(1);
  unfreeze(&current_sprite);
}
 