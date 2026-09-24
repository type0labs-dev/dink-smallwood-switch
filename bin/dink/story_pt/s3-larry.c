void main( void )
{
 int &girl;
 &girl = 0;
 int &mom;
 &mom = random(3, 1);
 if (&mom == 1)
 {
  freeze(&current_sprite);
  say_stop("`4Olá, senhor.", &current_sprite);
  unfreeze(&current_sprite);
 }
}

void talk( void )
{
 freeze(1);
 freeze(&current_sprite);
 choice_start()
 "Perguntar sobre a loja"
 "Ver o que está à venda"
 "Sair"
 choice_end()
  if (&result == 1)
  {
   say_stop("Ei, que tipo de loja você tem aqui?", 1);
   wait(250);
   say_stop("`4Somos a Robinson Cabinets.", &current_sprite);
   wait(250);
   say_stop("`4Podemos fornecer todas as suas necessidades de móveis de madeira.", &current_sprite);
   wait(250);
   say_stop("Ah, então não é pra mim. Já tive experiências ruins com móveis no passado.", 1);
   wait(250);
   say_stop("As coisas tendem a pegar fogo, e pessoas que eu conheço morrem. :'(", 1);
   wait(250);
   say_stop("`4Tudo bem então, se precisar de algo, eu estarei... ali... ó.", &current_sprite);
  }
  if (&result == 2)
  {
   if (&girl == 1)
   {
    say_stop("Então, tem algum outro negócio?", 1);
    wait(250);
    say_stop("`4Por favor, senhor, chega, eu preciso cuidar da minha filha.", &current_sprite);
    wait(250);
    say_stop("`6PAPAI!!!!!!!!!", &prom);
    wait(250);
    say_stop("`4Tá vendo o que eu quero dizer..", &current_sprite);
    unfreeze(1);
    unfreeze(&current_sprite);
    return;
   }
   int &prom;
   &prom = create_sprite(310, 460, 0, 0, 0);
   sp_brain(&prom, 16);
   sp_base_walk(&prom, 330);
   sp_speed(&prom, 1);
   sp_timing(&prom, 0);
   //set starting pic
   sp_pseq(&prom, 339);
   sp_pframe(&prom, 1);
   freeze(&prom);
   &girl = 1;
   say_stop("Tem alguma promoção doida esse mês?", 1);
   wait(250);
   say_stop("`4Não, desculpa. A gente praticamente trabalha por contrato", &current_sprite);
   wait(250);
   say_stop("`4em casas individuais. Também fazemos bancadas e coisas do tipo.", &current_sprite);
   wait(250);
   say_stop("Entendo, bem, eu não tenho casa, mas valeu pela informação.", 1);
   wait(250);
   say_stop("`4É, sem problema...", &current_sprite);
   say("`6PAPAI!!!!!!!!!", &prom);
   say_stop("`4Ah não...", &current_sprite);
   say("`6PAPAI!!!!!!!!!", &prom);
   move_stop(&prom, 8, 250, 1);
   say_stop("`4Sim, querida, o que foi?", &current_sprite);
   wait(250);
   say_stop("`6Eu preciso de um vestido novo.", &prom);
   wait(250);
   say_stop("`4Mas querida, a gente já te deu um semana passada.", &current_sprite);
   wait(250);
   say_stop("`6Bom, aquele não fica tão bem na luz do sol,", &prom);
   wait(250);
   say_stop("`6vamos devolver e comprar um novo.", &prom);
   wait(250);
   say_stop("`4Prometo, eu só não sei....", &current_sprite);
   wait(250);
   say_stop("`6EU DISSE AGORA!!", &prom);
   wait(250);
   say_stop("`4Tá bom, tá bom.", &current_sprite);
   unfreeze(&prom);
  }
 unfreeze(1);
 unfreeze(&current_sprite);
}

void hit( void )
{
 freeze(&current_sprite);
 say("`4Ei, para com isso, você vai machucar a madeira.", &current_sprite);
 unfreeze(&current_sprite);
}
