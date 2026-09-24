void main( void )
{
 int &talker;
 &talker = 0;
 int &smell;
 &smell = random(3, 1);
 if (&smell == 1)
 {
  say_stop("`6Bom dia pra você também, seu moço.", &current_sprite);
 }
 if (&smell == 2)
 {
  say_stop("`6Argh, como sinto falta do mar...", &current_sprite);
 }
}


void buys1( void)
{
int &junk = free_items();


if (&junk < 1)
 {
         choice_start()
        set_y 240
        title_start();
Você tá carregando coisa demais, seu leso!
        title_end();
         "Tá bom"
         choice_end()
 return;
 }


if (&gold < 400)
 {
         choice_start()
        set_y 240
        set_title_color 6
        title_start();
Você não tem ouro suficiente pra comprar essa espada, seu marinheiro de água doce!
        title_end();
         "Tá bom"
         choice_end()
 return;
 }

&gold -= 400;
add_item("item-sw1",438, 7);

}


void buy( void )
{
buy:
         choice_start()
        set_y 240
        set_title_color 6
        title_start();
"Argh, aprecia essas ferramentas de primeira..."
        title_end();
         "Espada longa - $400"
         "Bomba - $20"
         "Espada garra - $2000"
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

          if (&result == 3)
          {
           buysw2();
           unfreeze(1);
           goto mainloop;
           return;

          }


   unfreeze(1);
   goto mainloop;
   return;

}

void buybomb( void)
{
if (&gold < 20)
 {
         choice_start()
        set_y 240
        set_title_color 6
        title_start();
Argh, você não tem ouro suficiente pra comprar essa bomba, meu chapa!
        title_end();
         "Tá bom"
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
Você tá carregando coisa demais, seu leso!
        title_end();
         "Tá bom"
         choice_end()
 return;
 }

&gold -= 20;
add_item("item-bom",438, 3);
&bombs_total = 1;
draw_status();
}

void buysw2( void)
{
int &junk = free_items();


if (&junk < 1)
 {
         choice_start()
        set_y 240
        title_start();
Você tá carregando coisa demais, seu leso!
        title_end();
         "Tá bom"
         choice_end()
 return;
 }


if (&gold < 2000)
 {
         choice_start()
        set_y 240
        set_title_color 6
        title_start();
Argh! Cê não tem ouro suficiente pra comprar a Espada Garra!
        title_end();
         "Tá bom"
         choice_end()
 return;
 }
&gold -= 2000;
add_item("item-sw2",438, 20);
}


void talk( void )
{
 freeze(1);
 freeze(&current_sprite);
 choice_start()
(&talker == 0)"Perguntar sobre a loja"
(&talker == 1)"Perguntar sobre o Pete"
 "Ver o que tem à venda"
 "Sair"
 choice_end()
  if (&result == 1)
  {
   say_stop("Loja maneirinha, hein? O que é isso?", 1);
   wait(250);
   say_stop("`6Que lugar é esse, cê pergunta? Cê não tá vendo não?!", &current_sprite);
   wait(250);
   say_stop("`6Essa é a loja de armas do Pete Pimenta,", &current_sprite);
   wait(250);
   say_stop("`6as lâminas mais afiadas deste lado do mar.", &current_sprite);
   &talker = 1;
  }
  if (&result == 2)
  {
   say_stop("Cê é pirata?", 1);
   wait(250);
   say_stop("`6Argh, já fui...", &current_sprite);
   wait(250);
   say_stop("`6e dos bons, se quer saber.", &current_sprite);
   wait(250);
   say_stop("Bom, e o que cê tá fazendo aqui?", 1);
   wait(250);
   say_stop("Não devia estar nos mares, saqueando tesouros?", 1);
   wait(250);
   say_stop("`6Eu vivia daquele jeito, sangue na lâmina,", &current_sprite);
   wait(250);
   say_stop("`6rum na barriga, e pilhagem no porão.", &current_sprite);
   wait(250);
   say_stop("`6Mas tive um pequeno problema com a marinha real,", &current_sprite);
   wait(250);
   say_stop("`6e tive que dar uma sumida por um tempo.", &current_sprite);
   wait(250);
   say_stop("`6Mas pode ter certeza que meu tesouro me espera", &current_sprite);
   wait(250);
   say_stop("`6bem onde eu enterrei!", &current_sprite);
   wait(500);
   say_stop("`6Por que cê tá perguntando?", &current_sprite);
   wait(250);
   say_stop("Ah, só por curiosidade, seu moço.", 1);
  }
  if (&result == 3)
  {                                         f
 
  goto buy;
   //Stuff here
  }
 unfreeze(1);
 unfreeze(&current_sprite);
}

void hit( void )
{
 if (&story > 10)
 {
  say_stop("`6Eu vou te matar, herói.", &current_sprite); 
 }
 say_stop("`6Não me desafia, garoto, ou eu te dou uma perna de pau!!", &current_sprite);
}
