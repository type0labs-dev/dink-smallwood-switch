void main( void )
{
 int &say;
 &say = random(4,1);
 if (&say == 4)
 {
  say_stop("`7Me desculpe, minha querida, eu sinto sua falta...", &current_sprite);
  say_stop("`7Oh Dink!! Desculpa, não te vi aí.", &current_sprite);
 }
 if (&story == 5)
 {
  &say = random(3,1);
  if (&say == 1)
  {
   say_stop("`7Dink! Espero que você esteja bem.", &current_sprite);
   wait(250);
   say_stop("`7Trágico, o que aconteceu.", &current_sprite);
  }
 }
 if (&farmer_quest == 1)
 {
  say("`7Oh Dink, como vai a batalha?", &current_sprite);
 }
 if (&farmer_quest == 2)
 {
  say("`7Ah Dink, salvador da minha fazenda!", &current_sprite);
 }
}

void talk( void )
{
 freeze(1);
 freeze(&current_sprite);
 choice_start()
 "Perguntar como vai a família"
(&farmer_quest == 0)"Perguntar sobre a fazenda dele"
 "Pedir para ver a Libby"
(&farmer_quest == 1)"Conseguir informações sobre a fazenda"
 "Sair"
 choice_end()
 wait(200);
  if (&result == 1)
  {
 say_stop("Então, como vai a família?", 1);
          say_stop("`7A gente tá bem.", &current_sprite);
           wait(200);
          say_stop("Ah.", 1);
   if (&story == 5)
   {
    say_stop("`7Dink, sinto muito pela sua mãe.", &current_sprite);
    say_stop("`7Ela era uma boa mulher.", &current_sprite);
           wait(200);
    say_stop("Valeu.", 1);
   }
  }
  if (&result == 2)
  {
          say_stop("E a sua fazenda? Tá rendendo muito?", 1);

          wait(200);
          say_stop("`7A fazenda... ah, a fazenda!! Esses malditos monstros,", &current_sprite);
   say_stop("`7tão começando a me encher o saco.", &current_sprite);
   say_stop("`7Eles vêm da floresta e destroem os campos!", &current_sprite);
   say_stop("`7Preciso fazer algo com eles logo..." ,&current_sprite);
      choice_start()
      "Oferecer para resolver o problema"
      "Perguntar o que ele pretende fazer"
      choice_end()
   if (&result == 1)
   {
    &farmer_quest = 1;
    say_stop("Não se preocupe, Sr. SmileStein, eu cuido do problema.", 1);
    wait(250);
    say_stop("`7Sério, Dink?? Ah, muito obrigado, obrigado.", &current_sprite);
    say_stop("`7Volte aqui e me avise quando tiver derrotado eles.", &current_sprite);
    say_stop("Sem problema, senhor.", 1);
   }
   if (&result == 2)
   {
    say_stop("O que você está planejando?", 1);
    wait(250);
    say_stop("`7Tô pensando em contratar um caçador de PortTown pra vir", &current_sprite);
    say_stop("`7cuidar deles! Isso vai ajudar na colheita do ano que vem.", &current_sprite);
   }
  }
  if (&result == 3)
  {
          say_stop("Posso subir pra ver a Libby?", 1);
   wait(250);

   if (&farmer_quest == 2)
   {
    say_stop("`7Pra você, Dink, pode subir.", &current_sprite);
    unfreeze(1);
                  unfreeze(&current_sprite);
    return;
   }
   say_stop("`7Não, agora não pode.", &current_sprite);
   say_stop("`7Ela não pode ser incomodada.", &current_sprite);
   say_stop("Ah.", 1);
  }
  if (&result == 4)
  {
   say_stop("`7Bem, minha fazenda fica um pouco pro oeste.", &current_sprite);
   say_stop("`7Os monstros parecem estar pisoteando ela sem parar.", &current_sprite);
   say_stop("`7Por favor, veja o que pode fazer, Dink.", &current_sprite);
  }
  unfreeze(1);
  unfreeze(&current_sprite);
}

void hit( void )
{
 say_stop("`7Por favor, não tô a fim.", &current_sprite);
}
