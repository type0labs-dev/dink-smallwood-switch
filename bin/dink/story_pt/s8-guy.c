void main( void )
{
sp_hitpoints(&current_sprite, 30);
sp_base_walk(&current_sprite, 370);
preload_seq(371);
preload_seq(373);
preload_seq(375);
preload_seq(377);
preload_seq(379);
sp_speed(&current_sprite, 1);
sp_timing(&current_sprite, 33);
}

void talk( void )
{

if (&story < 14)
 {
 freeze(1);
 freeze(&current_sprite);

  say_stop("`5Eu tô trabalhando no arco mais poderoso do mundo!", &current_sprite);
  wait(300);
  say_stop("Caraca, manda pra cá agora!", 1);
  wait(300);
  say_stop("`5Ainda não terminei. Volta mais tarde.", &current_sprite);
        unfreeze(1);
        unfreeze(&current_sprite);
        return;
 }

int &mcrap = count_item("item-b3");

 freeze(1);
 freeze(&current_sprite);
 choice_start();
        set_y 240
        set_title_color 5
        title_start();
"Minha obra-prima tá pronta!"
        title_end();
(&mcrap == 0) "Comprar o Arco de Fogo por $25.000"
"Sair"
 choice_end();
  if (&result == 1)
    {
     if (&gold < 25000)
       {
        say("Não tenho grana suficiente!", 1);
       }
       else
       {


int &junk = free_items();


if (&junk < 1)
 {
         choice_start()
        set_y 240
        title_start();
Você tá carregando coisa demais.
        title_end();
         "Ok"
         choice_end()
unfreeze(1);
unfreeze(&current_sprite);

 return;
 }


        say("`0* ARCO DE FOGO COMPRADO *", 1);
         playsound(43, 22050,0,0,0);
         &gold -= 25000;
 add_item("item-b3",438, 13);
       }
    }

unfreeze(1);
unfreeze(&current_sprite);


}

void hit( void )
{
say("`5Socorro!!! Assassino!", &current_sprite);

}

void die ( void )
{

//come back in 5 mins

  int &hold = sp_editor_num(&current_sprite);
  if (&hold != 0)
  editor_type(&hold, 6); 

}
