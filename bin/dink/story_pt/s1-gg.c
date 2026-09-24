void main( void )
{
int &mrandom;
}

void hit( void )
{

&mrandom = random(3, 1);

 if (&mrandom == 1)
 say_stop("`4Cuidado, moleque, até a minha paciência tem limite.", &current_sprite);
 if (&mrandom == 2)
 say_stop("`4Ah, você é guerreiro? <risada>", &current_sprite);
 if (&mrandom == 3)
 say_stop("`4Legal... Você vem treinando isso com seus porcos?", &current_sprite);


}


void talk( void)
{
move_stop(1, 2, 193, 1);
move_stop(1, 8, 190, 1);
 if (&story == 5)
 {
 freeze(1);
 &letter = 1;
 say_stop("`4Sinto muito pelo que aconteceu, Dink, espero que esteja bem.", &current_sprite);
 say_stop("Valeu, eu tô bem.", 1);
 wait(250);
 say_stop("`4Ah, chegou uma carta pra você. Tá na sua casa,", &current_sprite);
 say_stop("`4você devia dar uma olhada nela.", &current_sprite);
 wait(250);
 say_stop("Valeu.", 1);
 unfreeze(1);
 return;
 }
freeze(1);


choice_start();
"Pede pro guarda te deixar sair."
"Deixa pra lá"
choice_end();
wait(200);
if (&result == 1)
  {
  say_stop("Ei, guarda Renton. Preciso resolver umas paradas, deixa eu sair.", 1);
  wait(200);
  say_stop("`4É perigoso demais pra um garoto lá fora, Dink.", &current_sprite);
  wait(200);
  say_stop("Garoto? Me chama de guerreiro de agora em diante.", 1);
  wait(200);
  say_stop("`4Que nada... vai cuidar do teu porco. <risada>", &current_sprite);

  }
unfreeze(1);



}
