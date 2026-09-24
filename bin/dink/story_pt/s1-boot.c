void main( void )
{
sp_hitpoints(&current_sprite, 30);

}



void talk( void )
{

int &mcrap = count_item("item-bt");

 freeze(1);
 freeze(&current_sprite);
 choice_start();
        set_y 240
        set_title_color 5
        title_start();
"I'm a cobbler/pharmacist.  I make
special herb boots.  When the herb
touches your skin, you'll want to
dance and be hyper."
        title_end();
(&mcrap == 0) "Comprar as botas dele ($500)"
(&mcrap == 0) "Reclamar do preço"
(&mcrap != 0) "Reclamar do preço"
"Sair"
 choice_end();

if (&result == 2)
  {
  wait(300);
  say_stop("Sabe, as que eu tô usando eu comprei por só 1 peça de ouro.", 1);
  wait(300);
  say_stop("`5Você paga pelo que compra.", &current_sprite);
  wait(300);
  say_stop("Você vende muita coisa assim?", 1);
  wait(300);
  say_stop("`5Nunca vendi uma.", &current_sprite);
  wait(300);
  say_stop("A tá.", 1);
  }

if (&result == 3)
  {
  wait(300);
  say_stop("Ô, o preço tá salgado demais, dá pra baixar?", 1);
  wait(300);
  say_stop("`5Claro, que tal 2 de ouro?", &current_sprite);
  wait(300);
  say_stop("Fechou! Eu levo... ei!", 1);
  wait(300);
  say_stop("Eu já comprei pelo preço absurdo!", 1);
  wait(300);
  say_stop("`5Azar o seu.", &current_sprite);
  wait(300);
  say_stop("Eu queria devolver.", 1);
  wait(300);
  say_stop("`5E eu quero que você vá ver se eu tô na esquina.", &current_sprite);
  }


  if (&result == 1)
    {
     if (&gold < 500)
       {
        say("Não tenho dinheiro suficiente!", 1);
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



        say("`0* BOTAS HIPER COMPRADAS *", 1);
         playsound(43, 22050,0,0,0);
         &gold -= 500;
 add_item("item-bt",438, 22);
       
       }
    }

unfreeze(1);
unfreeze(&current_sprite);


}

void hit( void )
{
say("`5Socorro!!! Assassino!", &current_sprite);

}
