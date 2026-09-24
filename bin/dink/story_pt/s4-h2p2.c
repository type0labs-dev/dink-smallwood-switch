//House 2 script for the DAD person
void main( void )
{
 int &neat;
}

void talk( void )
{
 if (&story > 10)
 {
  freeze(1);
  say_stop("`2Valeu, pequenino.", &current_sprite);
  wait(250);
  say_stop("Seu Smallwood.", 1);
  wait(250);
  say_stop("`2Pois não.", &current_sprite);
  unfreeze(1);
  return;
 }
 freeze(1);
 &neat = random(3, 1);
 if (&neat == 1)
 {
  say_stop("`2Tô com tanta fome que não consigo nem falar.", &current_sprite);
 }
 if (&neat == 2)
 {
  say_stop("`2Oi, e aí?", &current_sprite);
 }
 if (&neat == 3)
 {
  say_stop("`2Bem-vindo à nossa vila.", &current_sprite);
 }
 unfreeze(1);
 //unfreeze(&current_sprite);
}

void hit( void )
{
 if (&story > 10)
 {
  say_stop("`2Primeiro nos alimenta, depois nos bate, é assim que você faz?", &current_sprite);
  reutrn;
 }
 say_stop("`2Que costumes estranhos vocês têm.", &current_sprite);
}
