void main( void )
{
 int &crap;
}

void hit( void )
{
  &crap = random(5, 1); 
if (&crap == 1)
 say_stop("`4AI! QUE DOR!", &current_sprite);
if (&crap == 2)
 say_stop("`4Tem uma pedra perto do Ídolo do Pato com uma rachadura...", &current_sprite);
if (&crap == 3)
 say_stop("`4Por favor, seu moço, não me machuca, eu sou a árvore falante do leste!", &current_sprite);
if (&crap == 4)
 say_stop("`4Essa doeu pra caramba!", &current_sprite);
if (&crap == 5)
 say_stop("`4Isso vai deixar marca!", &current_sprite);

}

void talk( void )
{
 say("É uma macieira.", 1);

}
