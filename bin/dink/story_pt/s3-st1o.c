void main( void )
{
 if (&mayor == 1)
 {
  int &woman;
  //Actually Spawn the girl, and her script
  &woman = create_sprite(29, 320, 0, 0, 0);
  sp_brain(&woman, 16);
  sp_base_walk(&woman, 250);
  sp_speed(&woman, 1);
  sp_timing(&woman, 0);
  //set starting pic
  sp_pseq(&woman, 253);
  sp_pframe(&woman, 1);
  //Start stuff
  freeze(1);
  freeze(&woman);
  say_stop("`9Por aqui.", &woman);
  wait(250);
  move_stop(&woman, 6, 150, 1);
  move_stop(&woman, 9, 264, 1);
  move_stop(&woman, 8, 180, 1);
  say_stop("`9O prefeito às vezes tá aí.", &woman);
  wait(250);
  say_stop("`9Se o que você disse é verdade, você tem que ir falar com ele.", &woman);
   move_stop(1, 2, 332, 1);
   move_stop(1, 8, 331, 1);
  move_stop(1, 6, 140, 1);
  move_stop(1, 9, 285, 1);
  sp_dir(1, 4);
  say_stop("Ok, vou falar.", 1);
  wait(250);
  say_stop("E aí, o que você vai fazer?", 1);
  wait(250);
  say_stop("`9Vou voltar pra fonte e avisar o povo.", &woman);
  wait(250);
  say_stop("`9Boa sorte.", &woman);
  &mayor = 2;
  move_stop(&woman, 1, -20, 1);
  unfreeze(1);
  unfreeze(&woman);
  sp_active(&woman, 0);
 }
}

