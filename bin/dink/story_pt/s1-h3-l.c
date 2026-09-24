void main( void )
{
 int &say;
 //playsound("cry.wav");
 &say = random(4,1);
 if (&say == 1)
 {
 say_stop("`3Ah Dink, é você..", &current_sprite);
 wait(250);
 }
}

void talk( void )
{
 freeze(1);
 freeze(&current_sprite);
 choice_start()
 (&mlibby == 0) "Convencê-la a contar por que está chateada"
 "Tentar confortá-la"
(&farmer_quest == 2)"Se gabar de ter limpado a fazenda deles"
 "Deixa pra lá"
 choice_end()
 wait(300);
  if (&result == 1)
  {
   say_stop("Libby, o que foi? Por que você tá tão chateada?", 1);
   say_stop("`3Nada Dink, você não ia entender.", &current_sprite);
   wait(250);
   if (&gossip == 0)
   {
    unfreeze(1);
    unfreeze(&current_sprite);
    return;
   }
         &mlibby = 1;
   say_stop("É seu pai, não é? Ele faz alguma coisa com você?", 1);
   wait(250);
   say_stop("`3O quê? Do que você tá falando?", &current_sprite);
   say_stop("Eu ouvi uns boatos, Libby, pode admitir, tá tudo bem.", 1);
   wait(250);
   say_stop("`3Admitir? Admitir o quê?", &current_sprite);
   say_stop("Que seu pai bate em você.", 1);
   say_stop("`3Seu idiota, claro que não!! Ele não faz isso!!", &current_sprite);
   say_stop("`3Eu tô chorando porque meu pai tá muito chateado.", &current_sprite);
   wait(250);
   say_stop("Ah... eu... entendi.", 1);
          say_stop("`3<sniff>", &current_sprite);
   say_stop("Seu pai tá chateado porque você não satisfaz ele?", 1);
   wait(250);
   say_stop("`3DINK!! Que porra é essa??", &current_sprite);
   say_stop("`3Faz exatamente um ano que minha mãe morreu, é por isso.", &current_sprite);
   wait(200);
   say_stop("Uhhh. Eu... uhm...", 1);
   wait(250);
   say_stop("Ah", 1);
   wait(200);
   choice_start()
 "Tentar confortá-la sobre a família dela"
 "Pedir desculpas por ter sido um idiota"
      choice_end()
      wait(300);
   if (&result == 1)
   {
    say_stop("Sinto muito pela sua mãe. Mas eu sei como você se sente", 1);
    say_stop("Eu também tô bem chateado, sabia?", 1);
    say_stop("`3Obrigada Dink, você me deixou feliz.", &current_sprite);
                  unfreeze(1);
                  unfreeze(&current_sprite);
    return;

   }
   if (&result == 2)
   {
                  say_stop("Ah, hehe, desculpa por ter sido tão insensível e falado aquelas coisas.", 1);
    say_stop("Acho que não devia dar ouvidos a boatos.", 1);
    wait(250);
    say_stop("Ah.. hehe.. he..", 1);
    say_stop("Uhhhhh...", 1);
    say_stop("Eita.", 1);
                  unfreeze(1);
                  unfreeze(&current_sprite);
    return;
   }
  }
  if (&result == 2)
  {
   say_stop("Não chora Libby. Tudo bem, seja lá o que for.", 1);
   say_stop("Às vezes coisas ruins simplesmente acontecem com a gente, a gente só", 1);
          say_stop("tem que aprender a perseverar.", 1);
   wait(250);
   say_stop("`3Valeu Dink, foi gentil da sua parte.", &current_sprite);
   wait(250);
  }   
  if (&result == 3)
  {
          say_stop("Então, você notou que sua fazenda tá indo melhor agora, né?", 1);
   wait(250);
   say_stop("Sabe que aquilo ali foi tudo obra minha.", 1);
          say_stop("`3Até que não tá ruim...", &current_sprite);
          say_stop("`3...comparado com o que você costuma fazer.", &current_sprite);
   wait(250);
          say_stop("Droga!", 1);
          
  }
  if (&result == 4)
  {
          say_stop("Ah, deixa pra lá. Eu tenho que ir agora.", 1);
  }
  unfreeze(1);
  unfreeze(&current_sprite);
}

void hit( void )
{
 &say = random(6,1)
  if (&say == 1)
  {
   say_stop("Sabe que eu odeio fazer isso com você, gata.", 1);
   return;
  }
 say_stop("`3Não, Dink!! Qual é o seu problema...", &current_sprite);
}
