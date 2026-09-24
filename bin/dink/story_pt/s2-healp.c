//script for store manager, actually attached to the bench

void main( void )
{

 int &crap = create_sprite(185,150, 0, 0, 0);
 &temphold = &crap;
 int &amount = 0;

preload_seq(241);
preload_seq(243);
int &myrand;
sp_brain(&temphold, 0);
sp_base_walk(&temphold, 240);
sp_speed(&temphold, 0);

//set starting pic

sp_pseq(&temphold, 243);
sp_pframe(&temphold, 1);

mainloop:
wait(500);
&myrand = random(8, 1);

  if (&myrand == 1)
  {
  sp_pseq(&temphold, 243);
  }

  if (&myrand == 2)
  {
  sp_pseq(&temphold, 241);
  }

goto mainloop;
}

void buybottle( void)
{
if (&gold < 25)
 {
         choice_start()
        set_y 240
        title_start();
Cê não tem ouro suficiente pra comprar a poção.
        title_end();
         "Ok"
         choice_end()
 return;
 }

int &has_eli = count_item("item-eli");
if (&has_eli > 0)
{
    &gold -= 25;
    &elixir_total += 1;
    playsound(10, 22050, 0, 0, 0);
    draw_status();
    return;
}

int &junk = free_items();

if (&junk < 1)
 {
         choice_start()
        set_y 240
        title_start();
Tá carregando coisa demais, bicho.
        title_end();
         "Ok"
         choice_end()
 return;
 }

&gold -= 25;
add_item("item-eli",438, 9);
&elixir_total = 1;
draw_status();
}


void hit( void )
{
sp_speed(&current_sprite, 0);
wait(400);
say_stop("`%Por favor, não quebra o lugar, valeu.", &temphold);
wait(800);
goto mainloop;
}

void talk( void )
{

 freeze(1);
startok:

if (&life >= &lifemax)
{
 choice_start();
        set_y 240
        set_title_color 15
        title_start();
"Cê tá com uma saúde de dar inveja, chefe."
        title_end();
         "Comprar uma poção por $25"
         "Sair"
 choice_end();

  if (&result == 1)
  {
  buybottle();
  }
   unfreeze(1);
   goto mainloop;
   return;
}


}
startchoice:
&amount = &lifemax;
&amount -= &life;

         choice_start()
        set_y 240
        set_title_color 15
        title_start();
"Cê tá ferrado! Vai custar $&amount de ouro pra te curar."
        title_end();
         "Me curar"
         "Comprar uma poção por $25"
         "Sair"
         choice_end()

if (&result == 1)
  {
   if (&gold < &amount)
   {
         choice_start()
        set_y 240
        title_start();
Cê não tem ouro suficiente.
        title_end();
         "Ok"
         choice_end()
   goto startchoice;    
   }
&life = &lifemax;
&gold -= &amount;
Playsound(22,22050,0,0,0);
say("Tô curado, valeu!", 1);
 unfreeze(1);
 goto mainloop;
  }

  if (&result == 2)
  {
   buybottle();
  }

   unfreeze(1);
   goto mainloop;
   return;

}

