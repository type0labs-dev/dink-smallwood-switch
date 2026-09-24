void main ( void )
{
 int &maybe;
 &maybe = random(3,1);
 if (&maybe == 1)
  {
  &maybe = random(3,1);
  if (&maybe == 1)
  {
     sp_speed(&current_sprite, 7);
     sp_timing(&current_sprite, 0);
     move(&current_sprite, 6, 510, 1);
  sp_speed(&current_sprite, 1);
     sp_timing(&current_sprite, 33);
  say_stop("`9Espero que eles não tenham me seguido...", &current_sprite);
  }
  else
     {
     say_stop("`9Olá, amigo...", &current_sprite);
  }
  }
}

void talk ( void )
{
 freeze(1);
 freeze(&current_sprite);
 choice_start()
 "Perguntar sobre as viagens dele"
 "Perguntar por novidades"
(&story == 2)"Perguntar se ele tem nozes de Árvore Alcalina"
 "Sair"
 choice_end()

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
    say_stop("`9Nozes de Árvore Alcalina?? Eu não como essas há muito, muito tempo.", &current_sprite);
    say_stop("`9Na minha cidade antiga eu talvez pudesse te dizer,", &current_sprite);
    say_stop("`9mas não conheço nenhuma por aqui.", &current_sprite);
   }
 unfreeze(1);
 unfreeze(&current_sprite);
}

void hit ( void )
{
 int &dir;
 say("`9Ow, qual é o seu problema, porra?!", &current_sprite);
 sp_speed(&current_sprite, 4);
 sp_timing(&current_sprite, 0);
 //Dissapear off screen
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
 say_stop("Ele não vai mais incomodar ninguém...", 1);
}

void story( void )
{
int &maybe = random(3,1);
 if (&maybe == 1)
  {
   say_stop("`9Acabei de escapar do Santuário dos Goblins.", &current_sprite);
   say_stop("`9É um lugar bem horrível e eu não recomendo ir até lá.", &current_sprite);
   wait(250);
   say_stop("Esse lugar é bem a oeste, como você veio parar aqui?", 1);
   say_stop("`9Bem, eu só fui me afastando de lá desde que saí.", &current_sprite);
   say_stop("`9Espero conseguir chegar em Porto Cidade e dar um tempo.", &current_sprite);
  }
 if (&maybe == 2)
  {
   say_stop("`9Eu sempre quis sair pelo mundo e viver aventuras.", &current_sprite);
   say_stop("`9Seja trabalhando na Guarda Real ou me alistando", &current_sprite);
   say_stop("`9num bando de mercenários.", &current_sprite);
   wait(250);
   say_stop("`9Infelizmente pra mim, um dos meus primeiros empregos me levou direto", &current_sprite);
   say_stop("`9pra ser capturado pelos goblins. Última vez que vou às Terras do Oeste.", &current_sprite); 
  }
 if (&maybe == 3)
  {
   say_stop("`9Depois de tanto tempo perto daqueles goblins, tô feliz de ter saído.", &current_sprite);
   say_stop("`9Aqueles caras são burros que nem uma porta, mano!", &current_sprite);
   say_stop("`9Eu tô envergonhado de ter sido capturado em primeiro lugar.", &current_sprite);
  }
}

void news( void )
{
int &maybe = random(5,1);

  if (&maybe == 1)
   {
    makefun();

   }

 &maybe = random(3,1);
 if (&maybe == 1)
  {
   //playmidi("creepy.mid");
   wait(1000);
   say_stop("`9Quando fui capturado no Santuário dos Goblins, notei uma coisa.", &current_sprite);
   say_stop("`9Todas as patrulhas que voltavam do norte pareciam diferentes.", &current_sprite);
   say_stop("`9Logo começaram a agir de um jeito muito estranho, e pouco depois alguns", &current_sprite);
   say_stop("`9foram trancados do meu lado e ficaram malucos!", &current_sprite);
   wait(200);
   say_stop("Cara, isso parece bem assustador.", 1);
   wait(200);
   say_stop("`9Mais um motivo pra eu me mandar por um tempo.", &current_sprite);
   wait(200);
  }
 if (&maybe == 2)
  {
   say_stop("`9Enquanto estava preso, os goblins disseram que perto dos Penhascos de Crag", &current_sprite);
   say_stop("`9tinha um mago contra quem eles lutavam, eles achavam", &current_sprite);
   say_stop("`9que conseguiriam pegar a magia dele se o derrotassem.", &current_sprite);
   say_stop("`9Enfim, eles diziam que esse cara podia transformar pessoas em gelo!!", &current_sprite);
   say_stop("`9Acho que perderam uns 30 soldados antes de desistirem.", &current_sprite);
  }
 if (&maybe == 3)
  {
   say_stop("`9Ouvi dizer que sua mãe é uma puta. Mas isso é só o que tão falando", &current_sprite);
   say_stop("`9por aí. Ha Ha Ha", &current_sprite);
   say_stop("`9Ha Ha .. Ha ..", &current_sprite);
   say_stop("`9... Ha ...", &current_sprite);
   say_stop("Ha Ha Ha ...", 1);
   say_stop("`9.. Ha Ha ..", &current_sprite);

   if (&story > 4)
   {
   say_stop("Ha Ha ... espera!!!!", 1);
   say_stop("Minha mãe tá morta!!!!!", 1);
   }
  }

}

void makefun( void )
{
 if (&story == 5)
  {
   say_stop("`9Um outro cara que conheci viajando me disse que teve um incêndio feio", &current_sprite);
   say_stop("`9por essas bandas. Espero que ninguém tenha se ferido.", &current_sprite);
   wait(200);
   say_stop("Sim... tenho certeza que ninguém se ... feriu ...", 1);
   unfreeze(1);
   unfreeze(&current_sprite);
   return;
  }
  say_stop("Saudações, amigo, alguma novidade?", 1);
  wait(200);
  say_stop("`9Nada demais. Qual é o seu nome mesmo?", &current_sprite);
  wait(200);
  say_stop("Smallwood,", 1);
  wait(250);
  say_stop("Dink Smallwood.", 1);
  wait(200);
  say_stop("`9Olá, eu sou o Chance `Zands", &current_sprite);
  wait(200);
  say_stop("`9Você tem um nome bem interessante.", &current_sprite);
  wait(200);
  say_stop("Obrigado.", 1);    
}
