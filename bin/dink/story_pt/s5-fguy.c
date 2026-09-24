void main( void )
{
//kill door

 int &door = sp(2);
 sp_prop(&door, 0);


 //setup guy
preload_seq(202);
preload_seq(204);
preload_seq(206);
preload_seq(208);
preload_Seq(70);
preload_Seq(166);

 sp_base_walk(&current_sprite, 410);
 sp_speed(&current_sprite, 1);
 sp_brain(&current_sprite, 16);
 sp_hitpoints(&current_sprite, 100);
 sp_pseq(&temp1hold, 401);
 sp_pframe(&temp1hold, 1);

 preload_seq(411);
 preload_seq(413);
 preload_seq(415);
 preload_seq(417);
 preload_seq(419);

wait(10);
freeze(&temp1hold);
freeze(&temp2hold);
freeze(&temp3hold);
freeze(1);
wait(500);
  say_stop("`#Gwen!!!  Vem pra cá, se protege!", &temp2hold);
wait(500);
  say_stop("`#Oh mãe!  Eu tava com tanto medo!", &temp3hold);
move_stop(&temp3hold, 3, 120,1);
playsound(46, 22050, 0,0,0);
wait(1300);
say_stop("`2Esse som...", &temp1hold);
wait(1300);
playsound(47, 22050, 0,0,0);
wait(1300);

//make dragon 1
&temp4hold = create_sprite(300, 480, 0, 0, 0);

sp_timing(&temp4hold, 66);
sp_speed(&temp4hold, 1);
sp_base_walk(&temp4hold, 200);

freeze(&temp4hold);
move_stop(&temp4hold, 8, 370,1);
playsound(12, 22050, &temp3hold, 0,0);
move_stop(&temp4hold, 6, 350,1);

wait(500);
move_stop(&temp3hold, 7, 93,1);
move_stop(&temp3hold, 4, 80,1);
wait(500);
say_stop("`4Não fujam mais de nós, humanos.", &temp4hold);
wait(500);


&temp5hold = create_sprite(670, 300, 0, 0, 0);
sp_timing(&temp5hold, 66);
sp_speed(&temp5hold, 1);
sp_base_walk(&temp5hold, 200);

freeze(&temp5hold);
move_stop(&temp5hold, 4, 580,1);
move_stop(&temp1hold, 4, 480,1);
say_stop("`4Vamos acabar com isso.", &temp5hold);

wait(500);
say_stop("`2Nós vamos lutar!", &temp1hold);
wait(500);
say_stop("`2Protege as mulheres, Smallwood!", &temp1hold);

unfreeze(1);
unfreeze(&temp1hold);
unfreeze(&temp2hold);
unfreeze(&temp3hold);
unfreeze(&temp4hold);
unfreeze(&temp5hold);
sp_script(&temp4hold, "en-drag");
sp_script(&temp5hold, "en-drag");

playmidi("1009");

}

void die( void )
{
 //dink fails
if (&life > 0)
{
 say("Nããão!  O bom padre morreu!  EU FALHEI!!!!!!!", 1);
 &life = 0;
}
}


