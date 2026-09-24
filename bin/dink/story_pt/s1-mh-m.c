void main( void )
{
 if (&wizard_see == 2)
 {
  say("`0E aí, Dink, como vai a caçada?", &current_sprite);
  return;
 }
 if (&wizard_see == 3)
 {
  sp_active(&current_sprite, 0);
  say("Ele sumiu!!", 1);
  return;
 }
 if (&wizard_see == 4)
 {
  sp_active(&current_sprite, 0);
  return;
 }
 say("`0Ah, Dink, já estava esperando por você.", &current_sprite);
}

void talk( void )
{
 freeze(1);
 freeze(&current_sprite);
 if (&wizard_see == 0)
 {
  say_stop("Oi, sou eu de novo. Mas quem é você de verdade?", 1);
  wait(200);
  say_stop("`0Sou o Mago Martridge, um professor de magia.", &current_sprite);
  wait(200);
  say_stop("Nossa, acho que nunca vi seu lugar por aqui antes.", 1);
  wait(200);
  say_stop("`0Gosto de ficar mais perto da natureza.", &current_sprite);
  wait(200);
  say_stop("`0Estive observando você por um tempo, Dink.", &current_sprite);
  wait(200);
  say_stop("Tipo, espiando pela minha janela e tal?", 1);
  wait(200);
  say_stop("`0Não, Dink, eu tenho magia.", &current_sprite);
  wait(200);
  say_stop("`0Você também pode ter o poder, a habilidade para o sobrenatural.", &current_sprite);
  wait(200);
  say_stop("Sério? Você acha? Legal, o que eu posso fazer?", 1);
  wait(200);
  say_stop("Consigo tipo criar pintinhos na minha frente e tal?", 1);
  wait(200);
  say_stop("`0Hmm, não.", &current_sprite);
  wait(200);
  say_stop("Bem, posso tipo flutuar e voar até as árvores?", 1);
  wait(200);
  say_stop("`0Talvez, depende...", &current_sprite);
  wait(200);
  say_stop("Posso lançar morte das minhas mãos??", 1);
  wait(200);
  say_stop("`0Talvez eu estivesse enganado, Dink.", &current_sprite);
  wait(200);
  say_stop("`0Mas essas coisas são difíceis de saber.", &current_sprite);
  &wizard_see = 1;
 }
 choice_start()
(&wizard_see == 1)"Dizer a ele que você é digno"
 "Perguntar sobre Magia"
 "Deixa pra lá"
 choice_end()
 wait(200);
 if (&result == 1)
 {
  int &boom;
  int &bottle;
  say_stop("Martridge, eu... eu dou conta. Estou preparado.", 1);
  wait(200);
  say_stop("Prometo ser honrado e aprender a usar direito.", 1);
  wait(200);
  say_stop("`0Bem, Dink, você precisa provar seu valor.", &current_sprite);
  wait(200);
  say_stop("Ah, cara, como eu faço isso?", 1);
  wait(200);
  say_stop("`0Bem, numa caverna nessas colinas, há uma fera.", &current_sprite);
  wait(200);
  say_stop("`0Chamada Bonca. Mate-a e volte.", &current_sprite);
  wait(200);
  say_stop("Eu vou fazer isso, posso enfrentar a fera.", 1);
  wait(200);
  say_stop("`0Excelente, excelente.", &current_sprite);
  wait(200);
  say_stop("Onde ela mora?", 1);
  wait(200);
  say_stop("`0Numa caverna a oeste, Dink.", &current_sprite);
  wait(200);
  say_stop("Não vou falhar com você.", 1);
  wait(200);
  &wizard_see = 2;
  say_stop("`0Tome isto, Dink. Esta poção vermelha vai fortalecê-lo.", &current_sprite);
  &boom = create_sprite(187, 157, 7, 167, 1);
  sp_seq(&boom, 167);
  &bottle = create_sprite(187, 157, 0, 56, 1);
  playsound(24, 22052, 0, 0, 0);
  sp_script(&bottle, "rpotion");
 }
 if (&result == 2)
 {
  say_stop("Martridge, me fale sobre magia.", 1);
  wait(200);
  say_stop("`0Bem, a magia é uma arte antiga. Aqueles que a conheceram", &current_sprite);
  wait(200);
  say_stop("`0foram grandes líderes, artistas e guerreiros.", &current_sprite);
  wait(200);
  say_stop("`0É um grande poder e uma dádiva para aqueles que sabem usá-la.", &current_sprite);
 }
 unfreeze(1);
 unfreeze(&current_sprite);
}

void hit( void )
{
 say("`0Por que você está tentando me machucar, Dink?", &current_sprite);
 //Warp the Wizard elsewhere
}
