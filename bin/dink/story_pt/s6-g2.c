void talk( void )
{
if (&story > 14)
  {
  say("`9Dink tá vivo! Vivo!", &current_sprite);
  return;
  }

 //guard 1
 say("`9Você é um cara muito corajoso, Sir Smallwood.", &current_sprite);
}

void hit( void )
{
int &dinky = sp_y(1, -1);
//get dinks y cord

if (&dinky < 280)
  {
   //dink is above them
   say_stop("`9É você aí em cima, Dink?", &current_sprite);

     wait(300);
   say_stop("`9Por que você tá tentando matar a gente?", &current_sprite);
   return;
  }
   say_stop("`9Não mata a gente não, a gente tá do seu lado.", &current_sprite);


}

