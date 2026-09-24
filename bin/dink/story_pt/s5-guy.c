void main( void )
{
 //setup guy

 sp_base_walk(&current_sprite, 410);
 sp_speed(&current_sprite, 1);
 sp_brain(&current_sprite, 16);

 preload_seq(411);
 preload_seq(413);
 preload_seq(415);
 preload_seq(417);
 preload_seq(419);

wait(10);

if (&s5-jop == 1)
  {
   freeze(&temp2hold);
   freeze(&temp1hold);
   freeze(1);
   sp_dir(&temp2hold, 3);

    sp_dir(&temp1hold, 9);
   wait(700);

   say_stop("`#Olha! Alguém desceu!",&temp2hold);
   wait(400);
   say_stop("Olá, eu sou o Dink Smallwood.",1);
   wait(400);
    
   say_stop("`2Ah, sim, já ouvi falar de você! Por favor, você viu alguém lá fora?",&temp1hold);
   wait(400);
   sp_dir(1, 1);
   say_stop("Lá fora onde? Na vila?",1);
   wait(400);
   say_stop("`2Sim! Nossa filha ainda está lá fora! Ela vai ser morta!",&temp1hold);
   wait(400);
   say_stop("Por quê? Não vi nada perigoso.",1);
   wait(400);
   say_stop("`#Eles devem ter ido embora. Precisamos ir achá-la... e se ela estiver...",&temp2hold);
   wait(400);
   sp_dir(&temp1hold, 7);
   say_stop("`2Não fale essas coisas! Fique aqui, eu volto já.",&temp1hold);
   move_stop(&temp1hold, 9, 530, 1);
   //hide man
   sp_nodraw(&temp1hold, 1);
  move_stop(&temp2hold, 6, 300, 1);
  wait(500);
  say_stop("`#Não posso ficar parado enquanto minha filha está em perigo!", &temp2hold);
  wait(500);
  move_stop(&temp2hold, 6, 450, 1);
  move_stop(&temp2hold, 9, 530, 1);
  sp_active(&temp2hold, 0);
  unfreeze(1);
  sp_active(&temp1hold, 0);
  say("Que vila mais esquisita.", 1);
  &s5-jop = 2;
  }
}
