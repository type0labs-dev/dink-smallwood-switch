//hellfire man

void main( void )
{
 preload_seq(381);
 preload_seq(383);
 preload_seq(385);
 preload_seq(387);
 preload_seq(389);
 sp_base_walk(&current_sprite, 380);
 sp_hitpoints(&current_sprite, 50);
 sp_brain(&current_sprite, 16);
 sp_speed(&current_sprite, 1);
 sp_timing(&current_sprite, 33);

}

void hit( void )
{
 say("`5Acho que vou morrer logo. Não tô nem aí.",&current_sprite);

}

void talk( void )
{

int &mcrap = count_magic("item-sfb");

 freeze(1);
 freeze(&current_sprite);


if (&mcrap > 0)
  {

  say_stop("`0Por favor, senhor, não tenho mais nada pra vender.", &current_sprite);
  wait(400);
  say_stop("Me vende outra coisa, seu desgraçado!", 1);
  wait(400);
  say_stop("`0Nem.", &current_sprite);
  wait(400);
  say_stop("Mas o que você tá fazendo nessa caverna, hein?",1);
  wait(400);
  say_stop("`0Tava esperando você.", &current_sprite);
  wait(400);
  say_stop("Você tem família?", 1);
  wait(400);
  say_stop("`0Não.", &current_sprite);
  wait(400);
  say_stop("Você tem um lar?", 1);
  wait(400);
  say_stop("`0Não tenho.", &current_sprite);
  wait(400);
  say_stop("Sua vida não faz sentido pra mim.", 1);
  wait(400);
  say_stop("`0A vida não tem que fazer sentido.", &current_sprite);
  wait(400);
  say_stop("E eu suponho que você sabe tudo.", 1);
  wait(400);
  say_stop("`0Nem. Se soubesse, acho que nem ia querer viver.", &current_sprite);
  wait(400);
  say_stop("Vou indo então.", 1);
  unfreeze(1);
  unfreeze(&current_sprite);

  return;
  }

 choice_start();
        set_y 240
        set_title_color 0
        title_start();
"Olá, amigo. Vou ensinar a magia Fogo do Inferno por $1500 de ouro."
        title_end();
"Aprender Fogo do Inferno"
"Sair"
 choice_end();

  if (&result == 1)
    {
     if (&gold < 1500)
       {
        say("Não tenho dinheiro suficiente!", 1);
       }
       else
       {

int &junk = free_magic();


if (&junk < 1)
 {
         choice_start()
        set_y 240
        title_start();
Você está carregando demais.
        title_end();
         "Ok"
         choice_end()
unfreeze(1);
unfreeze(&current_sprite);

 return;
 }


if (&junk < 1)
 {
         choice_start()
        set_y 240
        title_start();
Você está carregando demais.
        title_end();
         "Ok"
         choice_end()
unfreeze(1);
unfreeze(&current_sprite);

 return;
 }


        say("`0* VOCÊ APRENDEU FOGO DO INFERNO *", 1);
         playsound(43, 22050,0,0,0);
         &gold -= 1500;
 add_magic("item-sfb",437, 2);
       
       }
    }

unfreeze(1);
unfreeze(&current_sprite);


}
