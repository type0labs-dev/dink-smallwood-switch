void talk( void )
{

if (&story > 14)
  {
 say("`9Olha Tom, o Dink voltou!", &current_sprite);
  return;
  }
 //guard 1
 say("`9É esse o caminho, Dink. Boa sorte pra você.", &current_sprite);
}

void hit( void )
{
int &dinky = sp_y(1, -1);
//get dinks y cord

if (&dinky < 280)
  {
   //dink is above them
   say_stop("`9Ai, isso doeu pra caramba.", &current_sprite);
   wait(300);
   say_stop("`9Será que veio da onde isso?", &current_sprite);
   return;
  }
   say_stop("`9Testando suas armas? Elas funcionam certinho, pode confiar.", &current_sprite);


}
