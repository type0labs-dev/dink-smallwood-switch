void main( void )
{
 int &hi;
 &hi = 0;
}


void buys3( void)
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
 return;
 }


if (&gold < 4000)
 {
         choice_start()
        set_y 240
        title_start();
Cê tá meio sem grana agora.
        title_end();
         "Ok"
         choice_end()
 return;
 }

&gold -= 4000;
add_item("item-sw3",438, 21);

}



void buyb2( void)
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
 return;
 }


if (&gold < 5000)
 {
         choice_start()
        set_y 240
        title_start();
Cê tá meio sem grana agora.
        title_end();
         "Ok"
         choice_end()
 return;
 }

&gold -= 5000;
add_item("item-b2",438, 12);

}


void talk( void )
{
 freeze(1);
 freeze(&current_sprite);
 choice_start()
 "Dizer oi"
 "Ver o que ela tem"
 "Sair"
 choice_end()
  if (&result == 1)
  {
  if (&story > 14)
    {
    say_stop("`2Então cê voltou, aventureiro Smallwood.", &current_sprite);
   wait(250);
   say_stop("Eu matei o Seth.", 1);
   wait(250);
   say_stop("`2Louvado seja! Você é um herói de verdade, Dink!", &current_sprite);
    unfreeze(1);
    unfreeze(&current_sprite);
    return;


    }

   if (&hi == 1)
   {
    say_stop("`2Por favor, Dink, você precisa se apressar até seu amigo.", &current_sprite);
   wait(250);
   say_stop("Mas como? Cadê ele?", 1);
   wait(250);
   say_stop("`2O portal fica bem perto daqui. Você vai achar.", &current_sprite);
    unfreeze(1);
    unfreeze(&current_sprite);
    return;
   }
   say_stop("`2Ah, Dink, já ouvi falar de você.", &current_sprite);
   wait(250);
   say_stop("`2Não pensei que você chegaria tão rápido por essas bandas.", &current_sprite);
   &hi = 1;
   wait(250);
   say_stop("Às vezes eu me surpreendo até a mim mesmo.", 1);
   wait(500);
   say_stop("E por aqui, como é que tá?", 1);
   wait(250);
   say_stop("`2Estranho, tenho visto muito movimento vindo das terras sombrias.", &current_sprite);
   wait(250);
   say_stop("`2Parece que eles tão se espalhando pelo mundo.", &current_sprite);
   wait(250);
   say_stop("Bom, eles podem fazer o que quiserem,", 1);
   wait(250);
   say_stop("mas eu preciso achar o Milder!", 1);
   wait(250);
   say_stop("`2Tenho certeza que o tempo tá acabando pro seu amigo, Dink.", &current_sprite);
   wait(250);
   say_stop("`2Quem sabe até já converteram o Milder pro mal.", &current_sprite);
   wait(500);
   say_stop("`2Dink, se eles continuarem ficando mais fortes, eu temo que minha igreja", &current_sprite);
   wait(250);
   say_stop("`2não vai mais conseguir segurar o mal.", &current_sprite);
   wait(250);
   say_stop("Que 'mal' é esse que você fica falando?", 1);
   wait(250);
   say_stop("`2É uma abominação da natureza. Não quero falar sobre isso.", &current_sprite);
  }

  if (&result == 2)
  {

         choice_start()
        set_y 240
        set_title_color 2
        title_start();
"Só tenho algumas coisas... armas poderosas que achei perto da 'máquina'..."
        title_end();
         "Espada de Luz - $4000"
         "Arco Massivo - $5000"
         "Sair"
         choice_end()

          if (&result == 1)
          {
           buys3();
           unfreeze(&current_sprite);
           unfreeze(1);
           return;
          }

          if (&result == 2)
          {
           buyb2();
           unfreeze(&current_sprite);
           unfreeze(1);
           return;
          }


   }


 unfreeze(1);
 wait(500);
 unfreeze(&current_sprite);
}

void hit( void )
{
 say("Hahaha!!", 1);
}
