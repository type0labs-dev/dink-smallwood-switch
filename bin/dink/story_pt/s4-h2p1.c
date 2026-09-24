//House 2 script for the mom person
void main( void )
{
 int &bad;
preload_seq(331);
preload_seq(221);
}

void talk( void )
{
 if (&story > 10)
 {
  freeze(1);
  say_stop("`5Ahh Dink, como podemos te pagar?", &current_sprite);
  say_stop("`5Tô tão feliz de ver meu filho comendo de novo graças a você.", &current_sprite);
  wait(250);
 unfreeze(1);
  return;
 }
 freeze(1);
 choice_start()
 "Ver como a família tá"
 "Deixa pra lá"
 choice_end()
  if (&result == 1)
  {
   say_stop("E aí, como vai a loja?", 1);
   wait(250);
   say_stop("`5Nós... nós não temos loja, moço.", &current_sprite);
   wait(250);
   say_stop("E como vocês tão indo? Essa cidade parece que tá na pior.", 1);
   wait(250);
   say_stop("`5É... a gente dá muita coisa pros patos.", &current_sprite);
   wait(250);
   say_stop("É, é, os patos eu conheço...", 1);
   say_stop("e o que eles já te deram em troca?", 1);
  }
 unfreeze(1);
 //unfreeze(&current_sprite);
}

void hit( void )
{
 &bad = random(3, 1);
 if (&story > 10)
 {
  say_stop("`5Mas depois de nos salvar?? Nãão!", &current_sprite);
  return;
 }
 if (&bad == 1)
 {
  say_stop("`5Ahhh, Não!", &current_sprite);
  say_stop("`5A gente precisa de comida, não de ódio.", &current_sprite);
 }
 if (&bad == 2)
 {
  say_stop("`5Não os punhos, não os punhos!!", &current_sprite);
 }
 if (&bad == 3)
 {
  say_stop("`5Por favor, não bata numa mulher faminta!", &current_sprite);
 }
}
