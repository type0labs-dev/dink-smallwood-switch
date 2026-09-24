void main( void )
{
 //The furers ..
 say_stop("`4Bom dia, seu moço.", &current_sprite);
}

void talk( void )
{
 freeze(1);
 freeze(&current_sprite);
 choice_start()
(&story < 11)"Perguntar sobre a loja"
(&story > 10)"Ver o que tá pegando"
 "Ver o que tem pra vender"
 "Sair"
 choice_end()
  if (&result == 1)
  {        
   say_stop("E aí, como tá o mercado de peles?", 1);
   wait(250);
   say_stop("`4Vai bem, mas não é muita gente daqui que compra as peles.", &current_sprite);
   wait(250);
   say_stop("`4Só os viajantes que vão pras terras do norte.", &current_sprite);
   wait(250);
   say_stop("Você adora os patos daqui?", 1);
   wait(250);
   say_stop("`4Sim, mas só por causa da comunidade.", &current_sprite);
   wait(250);
   say_stop("`4É um ritual bem estranho o que eles têm, eu me pergunto", &current_sprite);
   wait(250);
   say_stop("`4como alguns conseguem aguentar a pressão de ficar sem comer", &current_sprite);
   wait(250);
   say_stop("`4por tanto tempo.", &current_sprite);
   wait(250);
   say_stop("É, é bem doido.", 1);
   wait(250);
   say_stop("E o que você faz pra comer?", 1);
   wait(250);
   say_stop("`4Ah, eu? Bem, eu não sou daqui e sei fazer", &current_sprite);
   wait(250);
   say_stop("`4comida com outras coisas. Eu vivo de sopas e ervas,", &current_sprite);
   wait(250);
   say_stop("`4não dessa carne e ovos que eles tão acostumados.", &current_sprite);
  }
  if (&result == 2)
  {
   say_stop("Oi, cara, como tá o movimento na loja?", 1);
   wait(250);
   say_stop("`4Ah, graças a Deus, tá indo muito bem, seu Dink.", &current_sprite);
   wait(250);
   say_stop("`4Eu te devo uma por ter salvo minha humilde loja.", &current_sprite);
   wait(250);
   say_stop("Ah, qual é, eu não fiz nada demais.", 1);
   wait(250);
   say_stop("Só mostrei pro povo daqui o que comer.", 1);
   wait(250);
   say_stop("`4Talvez, seu Dink, mas de qualquer forma meu negócio lucrou.", &current_sprite);
   wait(250);
   say_stop("`4Acho que os viajantes finalmente ficaram sabendo que", &current_sprite);
   wait(250);
   say_stop("`4não tem mais fome aqui.", &current_sprite);
   wait(250);
   say_stop("`4Obrigado, Dink, e se precisar de qualquer coisa, é só pedir.", &current_sprite);
  }
  if (&result == 3)
  {
   say_stop("O que você tem pra vender, exatamente?", 1);
   wait(250);
   say_stop("`4Peles de bichos mortos.", &current_sprite);
   wait(250);
   say_stop("Ah. Valeu.", 1);
   //Let Dink buy stuff ...
  }
 unfreeze(1);
 unfreeze(&current_sprite);
}

void hit( void )
{
 if (&story > 10)
 {
  say_stop("`3Então é essa a sua jogada, primeiro salva a gente, depois mata!", &current_sprite);
  return;
 }
 say_stop("`3Por favor, não, seu moço, eu sou só um humilde mercador.", &current_sprite);
}
