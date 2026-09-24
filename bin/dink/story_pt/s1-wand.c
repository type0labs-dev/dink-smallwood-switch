void main ( void )
{
 int &maybe;
 &maybe = random(3,1);
 if (&maybe == 1)
  {
   say_stop("`6E aí, colega viajante!", &current_sprite);
  }
}

//playmidi("xfiles.mid");

void talk ( void )
{
 freeze(1);
 freeze(&current_sprite);
 choice_start()
 "Perguntar sobre as viagens dele"
 "Perguntar as novidades"
(&story == 2)"Perguntar sobre as nozes AlkTree"
 "Ir embora"
 choice_end()
 wait(300);
  if (&result == 1)
   {
    story();
   }
  if (&result == 2)
   {
    news();
   }
  if (&result == 3)
   {
    say_stop("`6Nozes AlkTree?? Isso dá um banquete e tanto. Deixa eu ver...", &current_sprite);
    say_stop("`6Acho que tem uma árvore a sudeste da vila pequena", &current_sprite);
    say_stop("`6aqui perto.", &current_sprite);
   }
 unfreeze(1);
 unfreeze(&current_sprite);
}

void hit ( void )
{
 int &dir;
 say("`6Ai, seu maluco desgraçado!!", &current_sprite);
 sp_speed(&current_sprite, 4);
 sp_timing(&current_sprite, 0);
 //Disappear off screen
 &dir = random(4, 1);
 if (&dir == 1)
 {
         move(&current_sprite, 1, -100, 1);
 }
 if (&dir == 2)
 {
         move(&current_sprite, 3, 700, 1);
 }
 if (&dir == 3)
 {
         move(&current_sprite, 7, -100, 1);
 }
 if (&dir == 4)
 {
         move(&current_sprite, 9, 700, 1);
 }
 sp_brain(&current_sprite, 0);
 sp_kill(&current_sprite, 2000);
 script_attach(0);

}

void die ( void )
{
 say("Tô achando que ele não vai chegar no destino dele.", 1);
}

void story( void )
{
 int &maybe = random(3,1);
 if (&maybe == 1)
  {
   say_stop("`6Toma cuidado no Oeste. O castelo dos goblins tem uma", &current_sprite);
   say_stop("`6defesa extrema, pra dizer o mínimo.", &current_sprite);
   wait(250);
   say_stop("`6Já vi muito viajante perder a cabeça por lá, saca?", &current_sprite);
  }
 if (&maybe == 2)
  {
   say_stop("`6Ouvi dizer que tem um velho que mora logo ao norte do lago SunCool.", &current_sprite);
   say_stop("`6Nunca vi ele, mas já escutei uns barulhos estranhos quando", &current_sprite);
   say_stop("`6passei por lá.", &current_sprite);
  }
 if (&maybe == 3)
  {
   say_stop("`6Viajar de barco tá caro pra caramba hoje em dia. Se você", &current_sprite);
   say_stop("`6não for rico, talvez seja melhor", &current_sprite);
   say_stop("`6trabalhar pra pagar a passagem ou arrumar um amigo que pague", &current_sprite);
   say_stop("`6pra você. Se não, vai ter que juntar grana por muito tempo.", &current_sprite);
  }
}

void news( void )
{
int &maybe = random(3,1);
  if (&maybe == 1)
   {
    makefun();
    return;
   }
 &maybe = random(3,1); 
 if (&maybe == 1)
  {
   say_stop("`6Tem um papo de que um mal antigo tá despertando", &current_sprite);
   say_stop("`6no oeste. Mas sei lá, acho que é tudo", &current_sprite);
   say_stop("`6superstição besta.", &current_sprite);
   wait(500);
   say_stop("É... com certeza é só supers... tição...", 1);
  }
 if (&maybe == 2)
  {
   say_stop("`6Na cidade de Porto Town, o povo pode ser bem", &current_sprite);
   say_stop("`6bagunceiro às vezes. Uns dizem que é por causa dos", &current_sprite);
   say_stop("`6piratas que vivem por lá. De qualquer jeito, toma cuidado se", &current_sprite);
   say_stop("`6for viajar pra lá.", &current_sprite);
  }
 if (&maybe == 3)
  {
   say_stop("`6Se um dia cruzar com goblins, se liga.", &current_sprite);
   say_stop("`6Eles são bem violentos, então só não", &current_sprite);
   say_stop("`6irrita eles. Mas são bem burros.", &current_sprite);
   say_stop("`6Dá pra contar qualquer mentira pra eles,", &current_sprite);
   say_stop("`6que eles acreditam.", &current_sprite);
  }
}

void makefun( void )
{
 //I think story = 5 ???
 if (&story == 6)
  {
   int &maybe = random(3,1);
   if(&maybe == 1)
   {
    say_stop("`6Ouvi dizer que teve um incêndio feio numa vila aqui perto,", &current_sprite);
    say_stop("`6espero que ninguém tenha se ferido muito.", &current_sprite);
    wait(500);
    say_stop("É... com certeza ninguém se feriu...", 1);
   }
  }
 if (&old_womans_duck == 3)
  {
   say_stop("`6Nessa vila pequena aqui perto, ouvi dizer que tem", &current_sprite);
   say_stop("`6um maluco. Um assassino que persegue e mata os bichinhos de estimação do povo!", &current_sprite);
   wait(250);
   say_stop("`6Horrível, né?", &current_sprite);
   wait(250);
   say_stop("É... muito... horrível...", 1);
  }
 if (&old_womans_duck == 5)
  {
   say_stop("`6Nessa vila pequena aqui perto, ouvi dizer que tem", &current_sprite);
   say_stop("`6um maluco. Um assassino que persegue e mata os bichinhos de estimação do povo!", &current_sprite);
   wait(250);
   say_stop("`6Horrível, né?", &current_sprite);
   wait(250);
   say_stop("É... muito, uh... horrível...", 1);
  }
 else
 {
  say_stop("`6Então, jovem, qual é o seu nome?", &current_sprite);
  say_stop("Smallwood, Dink Smallwood.", 1);
  wait(250);
  say_stop("`6Prazer, Sr. Smallwood.", &current_sprite);
 }
}
