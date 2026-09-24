void main( void )
{
 if (&thief == 2)
 {
 int &poop;
 &vision = 1;
 //so the real warping door will appear
 &poop = create_sprite(300, 200, 0, 0, 0);
 sp_script(&poop, "s2-ryan2");
 }
 if (&thief == 3)
 {
 freeze(1);
 int &bad;
 int &poop;
 int &poop2;
 &bad = create_sprite(370, 190, 0, 0, 0);
 sp_brain(&bad, 0);
 sp_base_walk(&bad, 370);
 sp_speed(&bad, 2);
 sp_timing(&bad, 0);
//set starting pic
 sp_pseq(&bad, 371);
 sp_pframe(&bad, 1);

 &poop = create_sprite(410, 250, 0, 0, 0);
 sp_brain(&poop, 0);
 sp_base_walk(&poop, 290);
 sp_speed(&poop, 2);
 sp_timing(&poop, 0);
//set starting pic
 sp_pseq(&poop, 297);
 sp_pframe(&poop, 1);

 &poop2 = create_sprite(300, 175, 0, 0, 0);
 sp_brain(&poop2, 0);
 sp_base_walk(&poop2, 290);
 sp_speed(&poop2, 2);
 sp_timing(&poop2, 0);
//set starting pic
 sp_pseq(&poop2, 293);
 sp_pframe(&poop2, 1);

 wait(500);
 say_stop("`3Valeu por ajudar a gente a pegar esse cara, Dink.", &poop);
 wait(250);
 say_stop("`4É, ele tava enchendo nosso saco há muito tempo.", &poop2);
 wait(250);
 say_stop("Ah, ué... que bom que pude ajudar, pessoal.", 1);
 wait(250);
 say_stop("`4Ele não vai incomodar ninguém tão cedo.", &poop2);
 wait(250);
 say_stop("`3É, fala aí, o Tom e o Bob tão bem lá dentro?", &poop);
 wait(250);
 say_stop("Ué... Sim, eles tão bem.", 1);
 &tombob = 1;
 wait(250);
 say_stop("`3Acho que eles já vão sair.", &poop);
 wait(250);
 say_stop("`4Bora, vamos levar esse perdedor pra cadeia.", &poop2);
 move(&bad, 8, 130, 1);
 move(&poop, 8, 190, 1);
 move_stop(&poop2, 8, 115, 1);
 move(&bad, 4, -20, 1);
 move(&poop2, 4, -20, 1);
 move_stop(&poop, 4, -20, 1);
 &thief = 4;
 unfreeze(1);
 sp_active(&bad, 0);
 sp_active(&poop, 0);
 sp_active(&poop2, 0);
 }
}
 