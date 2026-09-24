void main( void )
{
if (&gobpass < 5)
  {
   return;
  }

 if (&mayor == 3)
 {

  int &evil;
  int &evil2;
  int &evil3;
  int &evil4;
  //Make Em
  &evil = create_sprite(120, -30, 0, 0, 0);
  sp_brain(&evil, 0);
  sp_base_walk(&evil, 300);
  sp_speed(&evil, 1);
  sp_timing(&evil, 0);
  //set starting pic
  sp_pseq(&evil, 303);
  sp_pframe(&evil, 1);
  //Now EVIL's friend
  &evil2 = create_sprite(490, -30, 0, 0, 0);
  sp_brain(&evil2, 9);
  sp_base_walk(&evil2, 300);
  sp_speed(&evil2, 1);
  sp_timing(&evil2, 0);
  //set starting pic
  sp_pseq(&evil2, 303);
  sp_pframe(&evil2, 1);
  //One more
  &evil3 = create_sprite(310, -30, 0, 0, 0);
  sp_brain(&evil3, 9);
  sp_base_walk(&evil3, 300);
  sp_speed(&evil3, 1);
  sp_timing(&evil3, 0);
  //set starting pic
  sp_pseq(&evil3, 303);
  sp_pframe(&evil3, 1);
  //Hell
  &evil4 = create_sprite(210, 470, 0, 0, 0);
  sp_brain(&evil4, 9);
  sp_base_walk(&evil4, 300);
  sp_speed(&evil4, 1);
  sp_timing(&evil4, 0);
  //set starting pic
  sp_pseq(&evil4, 303);
  sp_pframe(&evil4, 1);
  //Done, now move on
  freeze(1);
  freeze(&evil2);
  freeze(&evil3);
  freeze(&evil4);
  //Should just be escaping from the Camp
  fade_up();
  move_stop(1, 6, 300, 1);
  move(1, 2, 210, 1);
  wait(1000);
  say_stop("Caraca, essa foi por pouco!", 1);
  wait(500);
  say_stop("Parece que esse pergaminho pode ser a prova que eu preciso.", 1);
  wait(1000);
  playmidi("1004.mid");
  move(&evil, 2, 120, 1);
  wait(75);
  move(&evil2, 2, 174, 1);
  wait(65);
  move(&evil3, 2, 140, 1);
  wait(24);
  move(&evil4, 8, 370, 1);
  say("`4Não tão rápido...", &evil);
  say_stop("`7Ha Ha Haaa", &evil2);
  wait(500);
  move(&evil2, 4, 450, 1);
  move_stop(1, 2, 290, 1);
  move_stop(1, 8, 280, 1);
  wait(400);
  say_stop("`4Parece que você tem dificuldade de aprender, pestinha.", &evil);
  wait(250);
  say_stop("`4Eu não te falei pra ficar longe da gente?", &evil);
  wait(250);
  say_stop("É, mas meu pé ainda tem um encontro marcado com a sua cara.", 1);
  wait(250);
  say_stop("Que que vocês, esquisitos, querem com a cidade?", 1);
  wait(250);
  say_stop("`4Nossos negócios não precisam ser contados pra defunto.", &evil);
  wait(250);
  say_stop("`4Acaba com ele.", &evil);
  wait(250);
  screenlock(1);
  move_stop(&evil, 8, -30, 1);
  sp_active(&evil, 0);
  //Battle starts...
  sp_base_attack(&evil2, 740);
  sp_base_attack(&evil3, 740);
  sp_base_attack(&evil4, 740);
  sp_strength(&evil2, 10);
  sp_strength(&evil3, 10);
  sp_strength(&evil4, 10);      
  sp_defense(&evil2, 8);
  sp_defense(&evil3, 8);
  sp_defense(&evil4, 8);
  sp_touch_damage(&evil2, 6);
  sp_touch_damage(&evil3, 6);
  sp_touch_damage(&evil4, 6);
  sp_script(&evil2, "s3-dorks");
  sp_script(&evil3, "s3-dorks");
  sp_script(&evil4, "s3-dorks");
  sp_hitpoints(&evil2, 40);
  sp_hitpoints(&evil3, 40);
  sp_hitpoints(&evil4, 40);
  sp_target(&evil2, 1);
  sp_target(&evil3, 1);
  sp_target(&evil4, 1);
  unfreeze(1);
  unfreeze(&evil2);
  unfreeze(&evil3);
  unfreeze(&evil4);
  //Like if Dink lives ... give him the proof
  &mayor = 4;
 }
}
