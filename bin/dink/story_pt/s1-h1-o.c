void main( void)
{
 if (&story == 4)
  {
  //the old lady
  int &person1 = create_sprite(520, 300, 0, 231, 5);
  sp_speed(&person1, 1);
  sp_base_walk(&person1, 230);
  //girl
  int &person2 = create_sprite(520, 120, 0, 221, 5);
  sp_speed(&person2, 1);
  sp_base_walk(&person2, 220);

  if (&old_womans_duck != 3)
  {
  if (&old_womans_duck != 5)
   {
  int &duck1 = create_sprite(470, 270, 0, 24, 2);
   }
   }
  //Silver knight?
  int &person3 = create_sprite(600, 310, 0, 411, 1);
  sp_speed(&person3, 1);
  sp_base_walk(&person3, 410);
  //Girl2 at bottom
  int &person4 = create_sprite(545, 360, 0, 257, 2);
  sp_speed(&person4, 1);
  sp_base_walk(&person4, 250);
  &vision = 1;
  freeze(1);
  //move(int sprite, int direction, int destination, int nohard);
  move(&person1, 4, 500, 0);
  move(&person2, 2, 210, 0);
  move(&person3, 4, 570, 0);
  say_stop("`4Dink!!!", &person2);
  move(&person4, 4, 515, 1);
  move_stop(1, 6, 437, 1);
  say_stop("Eu... eu não consegui salvar ela", 1);
  wait(500);
  say_stop("Eu cheguei tarde demais.", 1);
  say_stop("`3Não é sua culpa, Dink.", &person1);
  if (&old_womans_duck == 3)
  {
  wait(250);
  say_stop("`3Espero que meu pato não estivesse lá dentro!", &person1);
  }
  if (&old_womans_duck == 5)
  {
  wait(250);
  say_stop("`3Se você não tivesse matado meu pato, ele teria salvado sua mãe.", &person1);
  wait(250);
  say_stop("Isso não faz o menor sentido Rita!", 1);
  wait(250);
  say_stop("`3Ah.. sei lá né...", &person1);
  }


  wait(250);

  say_stop("`4Não tinha nada que você pudesse fazer..", &person2);
  wait(250);
  say_stop("`6Não fica se culpando, garoto.", &person3);
  wait(750);
  fade_down();
  wait(250);
  &story = 5;
  force_vision(2);
  fade_up();
  unfreeze(1);
//force vision keep this task alive, now we need to kill it manually
  kill_this_task();
  return;
  }

if (&story > 4)
{
&vision = 2;
}



 if (&story == 3)
 {
 &vision = 1;
 freeze(1);
 move_stop(1, 4, 570, 1);
 playmidi("insper.mid");
 say_stop("O quê, a casa, mãe nãooooo!!!", 1);
 wait(500);
 say_stop("Ela ainda tá lá dentro!!", 1);
 unfreeze(1);
 kill_this_task();
 }

}
