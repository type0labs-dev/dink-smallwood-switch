void main ( void )
{
int &toldall;
int &s1;
int &s2;
int &s3;
int &s4;
 int &talkme;
 &talkme = 0;
 int &tip;
 &tip = random(3,1);
sp_hitpoints(&current_sprite, 30);
 if (&tip == 1)
  {
  say("`5Lá lá lááá Lá Lá", &current_sprite);
  }
}

void talk( void )
{

freeze(1);
freeze(&current_sprite);
say_stop("`5E aí, Dink, beleza?", &current_sprite);
say_stop("Oi, Chealse...", 1);
wait(250);
choice_start()
"Flertar com ela"
"Perguntar das fofocas"
"Perguntar sobre Milder FlatStomp"
(&old_womans_duck == 3)"Contar que você matou o pato da Rita"
"Deixa pra lá"
choice_end()
wait(300);
  if (&result == 1)
   {
    say_stop("Então, gata, ainda tá solteira e carente?", 1);
    say_stop("Porque sabe que eu sou o cara certo pra você.", 1);
    wait(250);
    say_stop("`5Fala sério, Smallwood!!", &current_sprite);
   }
  if (&result == 2)
   {
    say_stop("Então, qual é a fofoca mais quente da vila, Chealse?", 1);
    wait(250);

crapper:

   if (&s1 != 0)
{
   if (&s2 != 0)
   {
   if (&s3 != 0)
     {
   if (&s4 != 0)
       {
        unfreeze(&current_sprite);
        unfreeze(1);
        say_stop("`5Ah, Dink, não tô sabendo de mais nada, foi mal.",&current_sprite);
        return;
         }
      }
    }
    }
    if (&old_womans_duck == 3)
     {
      &tip = random(3,1);
      if (&tip == 1)
       {
       duck:
       say_stop("`5Bom, ouvi dizer que teve um assassinato horrível do pato da Rita!", &current_sprite);
       say_stop("`5Agora não sei de muita coisa, mas te conto quando souber.", &current_sprite);
       say_stop("Ah, que tragédia... é...", 1);
       wait(250);
       say_stop("...tenho que ir", 1);
        unfreeze(&current_sprite);
        unfreeze(1);

       return;
       }
     }
    if (&old_womans_duck == 5)
     {
      &tip = random(3,1);
      if (&tip == 1)
      {
      goto duck;
      }
     }


     &tip = random(4,1);
     Debug("Ok, tip is &tip.");
     if (&tip == 1)
      {
      if (&s1 == 1)
      goto crapper;
       say_stop("`5Bom, ouvi dizer que os SmileStein tão com uma família bem problemática agora.", &current_sprite);
       say_stop("`5Apesar do pai deles ser um fazendeiro exemplar.", &current_sprite);
       wait(250);
       say_stop("Tem certeza? Isso parece meio forçado.", 1);
       wait(250);
       say_stop("`5Sim, sim, outro dia quando eu tava voltando", &current_sprite);
       say_stop("`5de colher flores, ouvi a Libby chorando no quarto dela.", &current_sprite);
       wait(250);
       say_stop("Não... a Libby? Nossa.", 1);
    if (&gossip == 0)
    {
     &gossip = 1;

    }
       &s1 = 1;
      }
     if (&tip == 2)
      {
      if (&s2 == 1)
      goto crapper;
       say_stop("`5A Libby e o novo namorado dela parecem bem felizes juntos.", &current_sprite);
       wait(250);
       say_stop("É aquele cara de PortTown, né?", 1);
       say_stop("Ele parece meio mandão.", 1);
       wait(250);
       say_stop("`5É, mas ela diz que gosta muito dele e que quando", &current_sprite);
       say_stop("`5você o conhece melhor, ele é um cara legal.", &current_sprite);
       &s2 = 1;
      }
     if (&tip == 3)
      {
      if (&s3 == 1)
      goto crapper;
       say_stop("`5Ouvi dizer que os monstros no campo do fazendeiro SmileStein", &current_sprite);
       say_stop("`5tão deixando ele maluco. Até ouvi ele falando que tá", &current_sprite);
       say_stop("`5pensando em contratar um caçador pra acabar com eles.", &current_sprite);
       wait(250);
       say_stop("Nossa", 1);
       wait(250);
       say_stop("`5É, coisa grande..", &current_sprite);
       &s3 = 1;
      }
     if (&tip == 4)
      {
      if (&s4 == 1)
      goto crapper;
       
       say_stop("`5Bom, quando fui à costa outro dia, ouvi que os piratas", &current_sprite);
       say_stop("`5de PortTown tão precisando de mais ajuda e que podem", &current_sprite);
       say_stop("`5entrar em guerra com a Companhia Comercial do Norte!", &current_sprite);
       say_stop("Nossa, Chealse, isso é grande.", 1);
       wait(250);
       say_stop("Como você ficou sabendo de TUDO isso??", 1);
       wait(250);
       say_stop("`5Tá bom, tá bom, foi minha irmã mais velha, a Aby, que mora em PortTown, que me contou.", &current_sprite);
       &s4 = 1;
      }
   Debug("result is &result.");
   }
  if (&result == 3)
   {
    say_stop("E aquele baita idiota do Milder Flatstomp, como é que ele tá?", 1);
    wait(250);
    say_stop("`5Bom, ouvi dizer que ele se candidatou pra Guarda Real.", &current_sprite);
    say_stop("`5Mas fora isso, ele é só um grandalhão bobo, mas eu", &current_sprite);
    say_stop("`5também vi ele flertando com a Libby E com a Lyna!", &current_sprite);
    wait(250);
    say_stop("Caramba.. elas devem curtir o uniforme dele. EU TENHO que entrar!", 1);
   }
  if (&result == 4)
   {
    say_stop("Adivinha, tenho um segredo pra te contar, Chealse.", 1);
    wait(250);
    say_stop("`5Sério? O que é, Dink?", &current_sprite);
    say_stop("Bem....", 1);
    wait(500);
    say_stop("EU FUI QUEM MATOU O PATO DA RITA!!!!!!!!!", 1);
    unfreeze(&current_sprite);
    say("`5Nãaaaaao", &current_sprite);
    sp_timing(&current_sprite, 0);
    sp_speed(&current_sprite, 10); 
   }
unfreeze(1);
unfreeze(&current_sprite);
}

void hit ( void )
{
 playsound(12, 22050, 0, 0, 0);
sp_timing(&current_sprite, 0);
sp_speed(&current_sprite, 4);
say("`5Ei, se liga, criador de porco!!", &current_sprite);
wait(3000);
sp_timing(&current_sprite, 33);
sp_speed(&current_sprite, 1);
}

void die ( void )
{
    external("achievement", "award", 8);

&little_girl = 2;
say("Ela não vai mais incomodar ninguém.", 1);
}


