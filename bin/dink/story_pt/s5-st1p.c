void main( void )
{
 int &play;
}


void hit( void )
{
 &play = random(3, 1);
 if (&play == 1)
 {
  say_stop("`2Precisa me bater?", &current_sprite);
 }
 if (&play == 2)
 {
  say_stop("`2Você é um assassino, não é?", &current_sprite);
 }
 if (&play == 3)
 {
  say_stop("`2Então, bater no dono da loja de armas, hein?", &current_sprite);
  say_stop("`2Tem cada uma.", &current_sprite);
 }
}


void buyaxe( void)
{
int &junk = free_items();


if (&junk < 1)
 {
         choice_start()
        set_y 240
        title_start();
Você está carregando coisa demais.
        title_end();
         "Ok"
         choice_end()
 return;
 }


if (&gold < 3000)
 {
         choice_start()
        set_y 240
        title_start();
Você não tem ouro suficiente pra comprar isso.
        title_end();
         "Ok"
         choice_end()
 return;
 }

&gold -= 3000;
add_item("item-axe",438, 6);

}




void talk( void )
{
         choice_start()
        set_y 240
        set_title_color 2
        title_start();
"O que vai ser, herói?"
        title_end();
         "Machado de arremesso - $3000"
         "Sair"
         choice_end()

          if (&result == 1)
          {
           buyaxe();
           unfreeze(1);
           return;

          }

   unfreeze(1);
   return;

}
