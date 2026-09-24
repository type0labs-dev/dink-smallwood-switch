void main( void )
{
 int &mom;
 &mom = random(3,1)
 if (&mom == 1)
 {
  say_stop("`1Bom dia, seu moço.", &current_sprite);
 }
}

void hit( void )
{
int &rcrap = sp_pseq(&missle_source, -1);
int &scrap = compare_weapon("item-b1");
&scrap += compare_weapon("item-b2");
&scrap += compare_weapon("item-b3");
if (&rcrap == -1)
{
if (&scrap > 0)
{
 say("`1Viu, agora furou meu pulmão! Ai!", &current_sprite);
 return;
}
}
say("`1Isso dói e tal, mas você podia causar muito mais dano com um arco!", &current_sprite);
}

void buy( void )
{
buy:
int &junk = free_items();
say_stop("Bem, apesar do assalto a mão armada, eu queria comprar um arco.", 1);
if (&junk < 1)
 {
  choice_start()
  set_y 240
  title_start();
Você tá carregando coisa demais.
  title_end();
  "Ok"
  choice_end()
  return;
 }

if (&gold < 1000)
 {
  say_stop("`1Desculpa, chefe, mas você NÃO tem ouro suficiente!", &current_sprite);
  wait(250);
  say_stop("Ops, foi mal.", 1);
  unfreeze(1);
  unfreeze(&current_sprite);
  return;
 }

&gold -= 1000;

 say_stop("`1Excelente, chefe! Tenho certeza de que não vai se arrepender.", &current_sprite);
 wait(250);
 say_stop("É, então eu te aviso.", 1);
   wait(250);
   say_stop("`1Só mais uma coisa... se você segurar o botão, você vai puxar", &current_sprite);
   wait(250);
   say_stop("`1a corda do arco mais pra trás, e aí bate mais forte. Sem devolução. Divirta-se!", &current_sprite);
 add_item("item-b1",438, 8);
 unfreeze(1);
 unfreeze(&current_sprite);

}

void talk( void )
{
 freeze(1);
 freeze(&current_sprite);
 choice_start()
 "Perguntar sobre arcos"
 "Comprar um arco e flechas por $1000"
 "Sair"
 choice_end()
  if (&result == 1)
  {

int &hasbow = count_item("item-b1");
   if (&hasbow > 0)
   {
   say_stop("Bem, você me convenceu e eu comprei um.", 1);
   wait(250);
   say_stop("`1Você vai amar seu novo arco, chefe!", &current_sprite);
   wait(250);
   say_stop("Tem alguma dica de como usar?", 1);
   wait(250);
   say_stop("`1Bem... Tem um velho que mora na praia, perto", &current_sprite);
   wait(250);
   say_stop("`1daqui, que pode te ensinar a arte do arco. Isso vai te dar o triplo", &current_sprite);
   wait(250);
   say_stop("`1de dano... quando funciona.", &current_sprite);
   wait(250);
   say_stop("Legal! Como vou reconhecer a casa dele?", 1);
   wait(250);
   say_stop("`1É meio escondida.", &current_sprite);

 unfreeze(1);
 unfreeze(&current_sprite);
 return;

   }

   say_stop("Bom dia.", 1);
   wait(250);
   say_stop("`1Pra você também, chefe. Eu sou Arturous, às suas ordens.", &current_sprite);
   wait(250);
   say_stop("Sim, então, eu queria saber por quanto você vende seus arcos?", 1);
   wait(250);
   say_stop("`1Meu preço atual por um arco e flechas é 1000 de ouro.", &current_sprite);
   wait(250);
   say_stop("CARAMBA! Você não acha que é um pouco salgado demais?", 1);
   wait(250);
   say_stop("`1De jeito nenhum, minha qualidade é impecável.", &current_sprite);
   wait(250);
   say_stop("Droga, mais que seja!", 1);
  }
  if (&result == 2)
  {
   goto buy;
  }
 unfreeze(1);
 unfreeze(&current_sprite);
}
