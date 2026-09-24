//script for store manager, actually attached to the bench

void main( void )
{
int &bsword;
int &bnut


 int &crap = create_sprite(180,260, 0, 0, 0);
 &temphold = &crap;


preload_seq(389);
preload_seq(383);
int &myrand;
sp_brain(&temphold, 0);
sp_base_walk(&temphold, 380);
sp_speed(&temphold, 0);

//set starting pic

sp_pseq(&temphold, 383);
sp_pframe(&temphold, 1);

mainloop:
wait(500);
&myrand = random(8, 1);

  if (&myrand == 1)
  {
  sp_pseq(&temphold, 383);
  }

  if (&myrand == 2)
  {
  sp_pseq(&temphold, 389);
  }

&myrand = random(20, 1);

  if (&myrand == 1)
  {
  say_stop_npc("`6Se precisar de ajuda pra achar alguma coisa, é só falar.", &temphold);
  }


goto mainloop;
}


void hit( void )
{
sp_speed(&current_sprite, 0);
wait(400);
say_stop_npc("`6Não quebra o lugar, hein, valeu.", &temphold);
wait(800);  
goto mainloop;
}


void buys1( void)
{
int &junk = free_items();


if (&junk < 1)
 {
         choice_start()
        set_y 240
        title_start();
Você tá carregando coisa demais, mané.
        title_end();
         "Ok"
         choice_end()
 return;
 }


if (&gold < 400)
 {
         choice_start()
        set_y 240
        title_start();
Cê não tem ouro suficiente pra comprar essa espada. Awk!
        title_end();
         "Ok"
         choice_end()
 return;
 }

&gold -= 400;
add_item("item-sw1",438, 7);

}

void buyb1( void)
{
int &junk = free_items();


if (&junk < 1)
 {
         choice_start()
        set_y 240
        title_start();
Você tá carregando coisa demais, mané.
        title_end();
         "Ok"
         choice_end()
 return;
 }


if (&gold < 400)
 {
         choice_start()
        set_y 240
        title_start();
Cê não tem ouro suficiente pra comprar esse arco. Awk!
        title_end();
         "Ok"
         choice_end()
 return;
 }

&gold -= 400;
add_item("item-b1",438, 8);

}

void buybomb( void)
{
if (&gold < 20)
 {
         choice_start()
        set_y 240
        title_start();
Você tá sem ouro suficiente pra comprar essa bomba. Awk!
        title_end();
         "Ok"
         choice_end()
 return;
 }

int &has_bom = count_item("item-bom");
if (&has_bom > 0)
{
    &gold -= 20;
    &bombs_total += 1;
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
Você tá carregando coisa demais, mané.
        title_end();
         "Ok"
         choice_end()
 return;
 }

&gold -= 20;
add_item("item-bom",438, 3);
&bombs_total = 1;
draw_status();
}

void sell(void )
{
//let's sell some stuff back

sell:

//how many items do they have?

&bsword = count_item("item-sw1");
&bnut = count_item("item-nut");

         choice_start()
        set_y 240
        set_title_color 6
        title_start();
"A gente quer comprar umas coisas. O que você tem aí?"
        title_end();
       (&bsword > 0)  "Vender uma Espada Longa - $200"
       (&bnut > 0)  "Vender uma noz - $2"
        "Não vender nada"
        choice_end()

if (&result == 1)
    {
     kill_this_item("item-sw1");
     &gold += 200;
    goto sell;
    }

if (&result == 2)
    {
     kill_this_item("item-nut");
     &gold += 2;
    goto sell;
    }
   unfreeze(1);
   goto mainloop;
   return;


}


void buy( void )
{
buy:
         choice_start()
        set_y 240
        set_title_color 6
        title_start();
"Nossas mercadorias são da melhor qualidade. A gente bate qualquer preço!"
        title_end();
         "Espada Longa - $400"
         "Bomba - $20"
         "Sair"
         choice_end()

          if (&result == 1)
          {
           buys1();
           unfreeze(1);
           goto mainloop;
           return;

          }
          if (&result == 2)
          {
           buybomb();
           unfreeze(1);
           goto mainloop;
           return;

          }


   unfreeze(1);
   goto mainloop;
   return;

}


void talk( void )
{

 freeze(1);
         choice_start()
        set_y 240
        set_title_color 6
        title_start();
"O que posso fazer pelo senhor hoje?"
        title_end();
         "Comprar"
         "Vender"
         "Sair"
         choice_end()

   if (&result == 1)
           {
            goto buy;
           }

   if (&result == 2)
           {
            goto sell;
           }


   unfreeze(1);
   goto mainloop;
   return;

}

