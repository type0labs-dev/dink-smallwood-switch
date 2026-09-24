void main( void )
{
playmidi("insper.mid");
 int &mbot;
 &mbot = random(7,1);
 if (&mbot == 1)
 
 {
  say_stop("Aqui tá com cheiro de mofo, hein.", 1);
 }
 if (&mbot == 2)
 
 {
  say_stop("Tô gostando nada disso...", 1);
 }
//call it once right now
noise();

set_callback_random("noise", 5000, 10000);

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
int &bot = random(4,1);
if (&bot == 1)
say_stop("Dá pra vazar agora? <tremendo>", 1);
if (&bot == 2)
say_stop("Tô todo cagado...", 1);
if (&bot == 3)
say_stop("Que barulho foi esse!?.", 1);

if (&bot == 4)
say_stop("Essa caverna é um lixão, bora vazar...", 1);

}
