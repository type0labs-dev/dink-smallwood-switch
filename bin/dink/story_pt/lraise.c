//raise their level

void raise( void )
{
    if (&level >= 18) external("achievement", "award", 25);

playsound(33, 22000, 0, 0,0);
script_attach(1000);


   Playsound(10,22050,0,0,0);
wait(1000);
if (&level < 32)
  {
stop_entire_game(1);
   &level += 1;
        choice_start();
        set_y 240
        title_start();
VOCÊ AGORA ESTÁ NO NÍVEL &level

Você pode aumentar um dos seus atributos.
        title_end();
        "Aumentar Ataque"
        "Aumentar Defesa"
        "Aumentar Magia"
        choice_end();
    
  if (&result == 1)
  {
   &strength += 1;
  }
  if (&result == 2)
  {
   &defense += 1;
  }
  if (&result == 3)
  {
   &magic += 1;
  }

   &lifemax += 3;
 }
else
{
 &exp = 0;
 say("Que sacanagem! Fui tapeado na cara dura!", 1);
}
draw_status();
kill_this_task();
}

