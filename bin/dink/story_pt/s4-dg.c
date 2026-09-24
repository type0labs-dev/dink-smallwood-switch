void main( void )
{
 int &talker;
 &talker = 0;
}

void hit( void )
{
   say("`5Para de me bater, por favor.", &current_sprite);

}

void talk( void )
{
 freeze(1);
 choice_start()
 "Perguntar o que ele está guardando"
 "Perguntar como entrar"
 "Sair"
 choice_end()

  if (&result == 1)
  {
   say_stop("O que você está guardando aí?", 1);
   wait(250);
   say_stop("`5Este é o altar de patos da cidade.", &current_sprite);
   wait(250);
   say_stop("`5Nós os adoramos aqui.", &current_sprite);
   wait(250);
   say_stop("Ah, pensei que fosse um rancho ou algo assim.", 1);
   wait(250);
   say_stop("`5Em algumas ocasiões, oferecemos comida aos patos aqui.", &current_sprite);
   wait(250);
   say_stop("Vocês dão sua comida aos PATOS?", 1);
   wait(250);
   say_stop("`5Sim, claro.", &current_sprite);
   &talker = 1;
  }

  if (&result == 2)
  {
   say_stop("Então, como se faz para entrar e ver o altar?", 1);
   wait(250);
   say_stop("`5É uma grande honra adorar lá dentro... uma honra que você não merece.", &current_sprite);
   wait(250);
   say_stop("`5Você pode rezar para o pato daqui.", &current_sprite);
  }
 unfreeze(1);
}
