void main( void )
{
 int &pap;
}

void talk( void )
{
 freeze(1);
 choice_start()
 "Tomar uma bebida"
 "Inserir uma moeda"
 "Sair"
 choice_end()
  if (&result == 1)
  {
   say("Ah, que refrescante.", 1);
   &life = &lifemax;
   Playsound(22,22050,0,0,0);
  }
  if (&result == 2)
  {
   if (&gold < 1)
   {
    say("Não tenho nenhuma moeda!", 1);
    unfreeze(1);
    return;
   }
   &gold -= 1;
   &pap = random(4, 1);
   if (&pap == 1)
   {
    say("Espero que isso ajude.", 1);
   }
   if (&pap == 2)
   {
    say("Pra dar sorte.", 1);
   }
   if (&pap == 3)
   {
    say("Tomara que esse desejo se realize.", 1);
   }
   if (&pap == 4)
   {
    say("Pra mamãe.", 1);
   }
  }
 unfreeze(1);
}
