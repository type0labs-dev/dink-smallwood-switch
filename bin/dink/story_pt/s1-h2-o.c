//old woman who has a pet duck
void main( void )
{
 if (&old_womans_duck == 5)
 {
  say("`3Olá, seu assassino!!", &current_sprite);
 
 }

 if (&old_womans_duck == 0)
 {
  say("`3Ué, oi, Dink.", &current_sprite);
 
 }

 if (&old_womans_duck == 1)
 {
  say("`3Ah, Dink, tô tão preocupada - você achou ele?", &current_sprite);
 }

 if (&old_womans_duck == 2)
 {
  &old_womans_duck = 4;
  say_stop("`3Ah, Dink, olha quem tá aqui!", &current_sprite);
  wait(200);
  say("`3Ah, Dink, sua mãe tava te procurando.", &current_sprite);
 }
}

void talk( void )
{

if (&old_womans_duck == 5)
  {
   say("`3Sai de perto de mim!", &current_sprite);
   return;
  }




if (&story > 3)
  {
  say_stop("`3Sinto muito pela sua mãe, Dink,", &current_sprite);
  wait(200);
  say_stop("`3ela era uma boa mulher.", &current_sprite);
  if (&old_womans_duck == 3)
   {
   say_stop("`3Meio engraçado, meu pato sumiu e sua mãe morreu.", &current_sprite);
   }
  if (&old_womans_duck == 5)
   {
   say_stop("`3Meio engraçado, meu pato e sua mãe morta.", &current_sprite);
   }
 // goto talk;
  unfreeze(&current_sprite);
  unfreeze(1);

  return;
  }

if (&old_womans_duck == 2)
  {
  say_stop("`3Sou muito grata a você, Dink! Você é um querido!", &current_sprite);
  unfreeze(&current_sprite);
  unfreeze(1);
  return;
  }

if (&old_womans_duck == 4)
  {
  say_stop("`3Sou muito grata a você, Dink! Você é maravilhoso!", &current_sprite);
  unfreeze(&current_sprite);
  unfreeze(1);
  return;

  }


if (&old_womans_duck == 3)
  {
  say_stop("`3Será onde está meu patinho?", &current_sprite);

  unfreeze(&current_sprite);
  unfreeze(1);
 say("<risadinhas>", 1);
  return;
  }



if (&old_womans_duck == 1)
  {
  say_stop("`3Você tem que continuar procurando o Quaquá! Eu amava ele!", &current_sprite);
  unfreeze(&current_sprite);
  unfreeze(1);
  return;
  }

talk:
freeze(1);
freeze(&current_sprite);
choice_start()
"Perguntar como ela está"
(&old_womans_duck == 0)"Perguntar pelo bichinho dela"
"Perguntar sobre todas as garrafas dela"
"Sair"
choice_end()

if (&result == 4)
  {

  unfreeze(&current_sprite);
  unfreeze(1);

  }

wait(300);
if (&result == 1)
 {
  say_stop("Como você tá hoje, Rita?", 1); 
  wait(500);
  if (&old_womans_duck == 0)
  {
  say_stop("`3Não muito bem, Dink. O Quaquá sumiu!", &current_sprite);
  unfreeze(&current_sprite);
  unfreeze(1);
  return;
  }
  say_stop("`3Tô bem, Dink, obrigada por perguntar.", &current_sprite);
 }

if (&result == 2)
 {
  say_stop("Cadê o pequenino hoje?", 1); 
  wait(500);
  say_stop("`3O Quaquá sumiu! Você me ajuda a achar ele?", &current_sprite);
  wait(500);
  choice_start()
  "Concordar de todo coração"
  "Concordar meio sem vontade"
  "Dizer onde ela pode enfiar o 'Quaquá'"
  choice_end()
  wait(300);

  if (&result == 1)
   {
  say_stop("Vou achar ele já já, Rita, pode confiar!", 1); 
  wait(500);
  say_stop("`3Obrigada, Dink!", &current_sprite);
  wait(500);
  &old_womans_duck = 1;
  }

  if (&result == 2)
   {
  say_stop("É, acho que se eu ver ele, mando pra casa. Talvez.", 1); 
  wait(500);
  say_stop("`3Entendo... obriga.. da... acho.", &current_sprite);
  wait(500);
  &old_womans_duck = 1;
  }
  if (&result == 3)
   {
  say_stop("Você é patética. Acha seu próprio pato.", 1); 
  wait(500);
  say_stop("`3Eu... eu... não sabia... <começa a chorar>", &current_sprite);
  wait(500);
  unfreeze(1);
  unfreeze(&current_sprite);
  return;
  }
}
if (&result == 3)
 { 
  say_stop("Ei, Rita, que história é essa de todas essas bebidas na parede?", 1);
  say_stop("Você curte uma festa, hein?", 1);
  wait(200);
  say_stop("`3Que isso, Dink?", &current_sprite);
  wait(200);
  say_stop("Sabe, afogando as mágoas no fim de semana", 1);
  say_stop("acordando com caras que você nem conhece.", 1);
  say_stop("Ah, os arrependimentos, né Rita?", 1);
  wait(200);
  say_stop("`3Dink...", &current_sprite);
  say_stop("`3Cê tem é problema.", &current_sprite);
 }


}

  unfreeze(&current_sprite);
  unfreeze(1);
}

