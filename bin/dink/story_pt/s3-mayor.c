void main( void )
{
}

void hit( void )
{
 say("Deixa eu te mostrar MINHA versão de política, amigão!", 1);
}

void talk( void )
{
 if (&mayor == 2)
 {
 freeze(1);
 freeze(&current_sprite);
 choice_start()
 "Dizer oi"
 "Contar sobre o ataque planejado"
 "Sair"
 choice_end()
  if (&result == 1)
  {
   wait(400);
   say_stop("Olá, Prefeito, que cidade bonita a sua.", 1);
   wait(250);
   say_stop("`5Obrigado, nobre cidadão.", &current_sprite);
   wait(250);
   say_stop("É, já percebi.", 1);
  }
  if (&result == 2)
  {
   //Playmidi("Urgent.mid");
   wait(400);
   say_stop("Prefeito, tenho notícias urgentes, sua cidade vai ser atacada!", 1);
   wait(250);
   say_stop("`5O quê?!? Isso é um absurdo, você só pode estar de brincadeira!", &current_sprite);
   wait(250);
   say_stop("Não, tô falando sério! São os Cavaleiros de Cast.", 1);
   wait(250);
   say_stop("Eles planejam atacar durante o desfile.", 1);
   wait(250);
   say_stop("`5Isso é loucura!! ... muita gente ia se machucar.", &current_sprite);
   wait(250);
   say_stop("Mais um motivo pra você acreditar em mim.", 1);
   wait(250);
   say_stop("Agora, a garota perto da fonte disse que você conhecia uns guardas reais.", 1);
   wait(250);
   say_stop("`5Você falou com a minha filha?", &current_sprite);
   wait(250);
   say_stop("Ela é sua filha?? Ela tá solteira?",1);
   wait(250);
   say_stop("`5O quê?", &current_sprite);
   wait(250);
   say_stop("Deixa pra lá, então você tem uns contatos, né?", 1);
   wait(250);
   say_stop("`5Sim, eles podem ajudar.", &current_sprite);
   wait(250);
   say_stop("`5Mas preciso de provas antes de chamá-los.", &current_sprite);
   wait(250);
   say_stop("Ok, então se eu conseguir provas você ajuda?", 1);
   wait(250);
   say_stop("`5Sim, sem elas estou de mãos atadas.", &current_sprite);
   wait(250);
   &mayor = 3;
   say_stop("Beleza, então vou nessa.", 1);
  }
 unfreeze(1);
 unfreeze(&current_sprite);
 return;
 }
 if (&mayor == 3)
 {
 freeze(1);
 freeze(&current_sprite);
 choice_start()
 "Dizer oi"
 "Mostrar a prova pra ele"
 "Sair"
 choice_end()
  if (&result == 1)
  {
   wait(400);
   say_stop("Olá, Prefeito, que cidade bonita a sua.", 1);
   wait(250);
   say_stop("`5Obrigado, nobre cidadão.", &current_sprite);
   wait(250);
   say_stop("É, já percebi.", 1);
  }
  if (&result == 2)
  {
   wait(400);
   say_stop("Finalmente consegui a prova que precisamos.", 1);
   wait(250);
   //Check to see if he did
   say_stop("`5Não conseguiu não, seu mentiroso!", &current_sprite);
   wait(250);
   say_stop("Ops, foi mal.", 1);
  }
 unfreeze(1);
 unfreeze(&current_sprite);
 }
 if (&mayor == 4)
 {
 freeze(1);
 freeze(&current_sprite);
 choice_start()
 "Dizer oi"
 "Mostrar o pergaminho com os planos"
 "Sair"
 choice_end()
  if (&result == 1)
  {
   wait(400);
   say_stop("Olá, Prefeito, como vai?", 1);
   wait(250);
   say_stop("`5Tudo bem, nobre cidadão.", &current_sprite);
   wait(250);
   say_stop("Ei, que ótimo.", 1);
  }
  if (&result == 2)
  {
   wait(400);
   say_stop("Trouxe sua prova, Prefeito.", 1);
   wait(250);
   say_stop("Eles planejam chacinar a cidade inteira.", 1);
   wait(250);
   say_stop("`5Meu Deus, esse ataque destruiria nossas defesas!", &current_sprite);
   wait(250);
   say_stop("`5Não acredito que eles fariam isso com a gente.", &current_sprite);
   wait(250);
   say_stop("Agora você vai chamar a Guarda?", 1);
   wait(250);
   say_stop("`5Sim, só espero que cheguem a tempo...", &current_sprite);
   &mayor = 5;
   wait(500);
   script_attach(1000);
   //fadeout & cutscene?
   fade_down();
   //change maps and stuff ...
   &player_map = 586;
   sp_x(1, 266);
   sp_y(1, 80);
   load_screen();
   draw_screen();
   draw_status();
   fade_up();
   kill_this_task();
   //Done
  }
 unfreeze(1);
 unfreeze(&current_sprite);
 }
}
