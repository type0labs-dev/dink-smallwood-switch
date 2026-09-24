void main( void )
{
 int &bot;
 &bot = random(7,1);
 if (&bot == 1)
 
 {
  say_stop("Tá um cheirinho de mofo aqui dentro.", 1);
 }
 if (&bot == 2)
 
 {
  say_stop("Tô gostando nada disso...", 1);
 }

if (&wizard_see > 2)
{
set_callback_random("noise", 5000, 10000);
}
}

void noise( void )
{
if (&wizard_see > 2)
  {
  //killed monster already, why would it roar?
  return;
  }

playsound(32, 11000, 4000, 0, 0);
wait(4000);
&bot = random(4,1);
if (&bot == 1)
say_stop("Já dá pra vazar? <tremedeira>", 1);
if (&bot == 2)
say_stop("Tô com medo.", 1);
if (&bot == 3)
say_stop("Ué, que barulho estranho é esse?", 1);

if (&bot == 4)
say_stop("Essa caverna é uma droga, bora meter o pé...", 1);

}
