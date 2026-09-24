void main( void )
{
 int &wherex;
 int &wherey;
}

void talk( void )
{


if (&gobpass == 5)
  {
   if (&mayor == 0)
   {
    say_stop("** CORRIGINDO BUG.. REINICIANDO VILA DOS GOBLINS **",&current_sprite);
   &gobpass = 0;
    return;

   }
  }


 freeze(1);
 freeze(&current_sprite);
 choice_start()
 "Dizer oi"
 "Perguntar o que ela faz"
(&mayor == 0)"Contar sobre o ataque planejado"
(&mayor == 3)"Ver o que aconteceu desde então"
(&mayor == 4)"Mostrar a ela o Pergaminho"
 "Sair"
 choice_end()
  if (&result == 1)
  {
   wait(400);
   say_stop("E aí, tudo bem?", 1);
   wait(250);
   say_stop("`9Ah, oi, tudo ótimo.", &current_sprite);
   wait(1000);
   say_stop("Meu nome é Dink, prazer em te conhecer.", 1);
   wait(250);
   say_stop("`9Só dando um passeio pela cidade?" &current_sprite);
   wait(250);
   say_stop("Eu estava só dando uma olhada na praça.", 1);
   wait(250);
   say_stop("`9Pra quê?", &current_sprite);
   wait(250);
   say_stop("Pro grande desfile que vai rolar logo, o que mais, bobinho?", 1);
   wait(250);
   say_stop("`9Ah, sim... Eu... ouvi falar desse desfile.", &current_sprite);
   wait(250);
   say_stop("Então, o que você faz?", 1);
  }
  if (&result == 2)
  {
   wait(400);
   say_stop("Ah, eu sou pintora.", 1);
   wait(250);
   say_stop("`9Ah, entendo. O que você está pintando aqui?", &current_sprite);
   wait(250);
   say_stop("Espero fazer um retrato do desfile que vai acontecer em breve.", 1);
   wait(250);
   say_stop("`9Hmm", &current_sprite);
   wait(250);
   say_stop("Sabe, eu ouvi uns boatos sobre esse desfile.", 1);
  }
  if (&result == 3)
  {
   &wherex = sp_x(&current_sprite, -1);
   &wherey = sp_y(&current_sprite, -1);
   wait(400);
   say_stop("É, eu também, todo mundo tá feliz pra caramba.", 1);
   wait(250);
   say_stop("`9A música pode ser ouvida em toda a região.", &current_sprite);
   wait(250);
   say_stop("`9É, mas...", &current_sprite);
   wait(250);
   say_stop("Eu ouvi coisas diferentes...", 1);
   wait(250);
   say_stop("Tipo que os Cavaleiros Cast estão planejando vir e matar todo mundo aqui.", 1);
   wait(250);
   say_stop("O quê...?", 1);
   wait(250);
   say_stop("`9Tá de brincadeira, né?", &current_sprite);
   wait(250);
   say_stop("`9Quem dera, mas eu ouvi com meus próprios ouvidos ali fora da cidade.", &current_sprite);
   wait(250);
   say_stop("Nós todos vamos morrer!", 1);
   wait(250);
   say_stop("`9A gente tem que cancelar o desfile.", &current_sprite);
   wait(250);
   say_stop("Espera, não... tem outra solução.", 1);
   wait(250);
   say_stop("`9O Prefeito, ele conhece alguns membros da guarda real da região.", &current_sprite);
   wait(250);
   say_stop("`9Se a gente convencer ele, talvez a gente salve o desfile.", &current_sprite);
   wait(250);
   say_stop("`9Vem comigo.", &current_sprite);
   wait(250);
   say_stop("`9Teve sorte falando com o povo?", &current_sprite);
   &mayor = 1;
   //Move off screen
   if (&wherey < 200)
   {
    move_stop(&current_sprite, 2, 210, 1);
   }
   if (&wherey > 322)
   {
    move_stop(&current_sprite, 6, 660, 1);
   }
   if (&wherex < 500)
   {
   move_stop(&current_sprite, 6, 440, 1);
   }
   if (&wherex > 500)
   {
    move_stop(&current_sprite, 2, 250, 1);
   }
   move_stop(&current_sprite, 6, 660, 1);
   sp_active(&current_sprite, 0);
  }

  if (&result == 4)
  {
   int &woman;
   &woman = &current_sprite;
   //Playmidi("planning.mid");
   wait(400);
   say_stop("Nem, ninguém apareceu por aqui.", 1);
   wait(250);
   say_stop("`9É um evento anual e todo mundo sabe quando é,", &woman);
   wait(250);
   say_stop("`9eles não vêm antes, só aparecem na hora.", &woman);
   wait(250);
   say_stop("`9Isso pode ser ruim.", &woman);
   wait(250);
   say_stop("Mas eu ouvi um boato.", 1);
   wait(250);
   say_stop("`9Um cara disse que tava viajando perto do Santuário dos Goblins e um", &woman);
   wait(250);
   say_stop("`9atacou ele. Bem raro hoje em dia.", &woman);
   wait(250);
   say_stop("`9Pode ser algo, vou dar uma olhada.", &woman);
   wait(250);
   say_stop("Dá uma olhada nisso!", 1);
   wait(250);
  }


  if (&result == 5)
  {
   wait(400);
   say_stop("O plano de batalha dos Cast para a cidade.", 1);
   say_stop("Meu Deus, olha esse plano.", 1);
   wait(250);
   say_stop("`9Eles nem tão focando o ataque nos militares", &current_sprite);
   wait(250);
   say_stop("`9eles vão atacar toda a população daqui.", &current_sprite);
   wait(250);
   say_stop("`9A gente tem que impedir eles!", &current_sprite);
   wait(250);
   say_stop("Rápido, leva essa informação pro meu pai... corre!", 1);
   wait(250);
   say_stop("`9Ei, olha por onde anda, otário!", &current_sprite);
  }
 unfreeze(1);
 wait(500);
 unfreeze(&current_sprite);
}

void hit( void )
{
 int &say;
 playsound(12, 22050, 0, 0, 0);

 &say = random(3,1);
 freeze(&current_sprite);
 if (&say == 1)
 {
  say_stop("`9Socorro, alguém me ajuda!", &current_sprite);
 }
 if (&say == 2)
 {
  say_stop("`9Guardas, guardas, tá um banho de sangue!", &current_sprite);
 }
 if (&say == 3)
 {
  say_stop("`9Guardas, guardas, tá um banho de sangue!", &current_sprite);
 }
 unfreeze(&current_sprite);
}
