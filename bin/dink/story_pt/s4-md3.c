void main( void )
{
 int &talker;
 &talker = 0;
}

void touch( void )
{
 if (&story > 10)
 {
  move_stop(1, 2, 318, 1);
  say_stop("`9Valeu por alimentar a gente, Dink,", &current_sprite);
  say_stop("`9Tamo todos em dívida com você.", &current_sprite);
  return;
 }
 if (&talker == 1)
 {
  move_stop(1, 2, 318, 1);
  say_stop("`9Por favor, cai fora.", &current_sprite);
  return;
 }
 freeze(1);
 move_stop(1, 2, 318, 1);
 sp_dir(1, 8);
 say_stop("`9O que você quer?", &current_sprite);
 choice_start()
(&talker == 0)"Pedir pra entrar"
 "Deixa pra lá"
 choice_end()
  if (&result == 1)
  {
   say_stop("Posso entrar?", 1);
   wait(250);
   say_stop("`9Você trouxe comida? Meus filhos tão morrendo de fome!", &current_sprite);
   wait(250);
   say_stop("Eu... eu não tenho comida, desculpa.", 1);
   say_stop("Por que vocês tão passando fome?", 1);
   wait(250);
   say_stop("`9Eu não devia mais falar com você,", &current_sprite);
   say_stop("`9por favor, só vai.", &current_sprite);
   &talker = 1;
  }
 wait(250);
 unfreeze(1); 
}
                   
