void main( void )
{
 int &call;
 &call = random(3,1);
 if (&call == 1)
 {
  freeze(&current_sprite);
  say_stop("`3Bem-vindo à nossa livraria, senhor.", &current_sprite);
  unfreeze(&current_sprite);
 }
}

void talk( void )
{
 freeze(1);
 freeze(&current_sprite);
 say_stop("`3Como posso ajudar o senhor hoje?", &current_sprite);
 choice_start()
 "Perguntar sobre a livraria"
 "Perguntar sobre magia"
 "Descobrir sobre a próxima cidade"
 "Ver as novidades"
 "Sair"
 choice_end()
  if (&result == 1)
  {
   say_stop("Então, o que você tem aí?", 1);
   wait(250);
   say_stop("`3A gente vende livros, o que você achou?", &current_sprite);
   wait(250);
   say_stop("Hmmmm.", 1);
   say_stop("Anotado.", 1);
  }
  if (&result == 2)
  {
   say_stop("Você tem alguma coisa sobre magia aqui?", 1);
   wait(250);
   say_stop("`3Magia? Isso não existe.", &current_sprite);
   wait(250);
   say_stop("Entendi... obrigado.", 1);
  }
  if (&result == 3)
  {
   if (&mayor >= 6)
   {
    say_stop("Ouviu alguma coisa sobre aquela outra cidade?", 1);
    wait(250);
    say_stop("`3É, na real, um cara passou por aqui de manhã,", &current_sprite);
    say_stop("`3ele disse que a ponte tinha voltado, então com certeza você pode", &current_sprite);
    say_stop("`3ir até lá e dar uma conferida.", &current_sprite);
    wait(250);
    say_stop("Beleza, valeu.", 1);
    unfreeze(1);
    wait(1000);
    unfreeze(&current_sprite);
    return;
   }
   say_stop("Pode me falar de outras cidades legais?", 1);
   wait(250);
   say_stop("`3Tem um lugar maneiro a leste de Terris.", &current_sprite);
   wait(250);
   say_stop("`3Mas pelo que soube, a ponte lá caiu.", &current_sprite);
   wait(250);
   say_stop("`3Te aviso se eu ouvir qualquer coisa.", &current_sprite);
  }
  if (&result == 4)
  {
   say_stop("E o que anda rolando por aqui ultimamente?", 1);
   wait(250);
   if (&mayor >= 6)
   {
    say_stop("`3Bem, você devia saber, herói! Valeu pelo que você fez,", &current_sprite);
    wait(250);
    say_stop("`3o prefeito me contou que você salvou todo mundo.", &current_sprite);
    wait(250);
    say_stop("Ah, bom... o prefeito exagera um pouco,", 1);
    wait(250);
    say_stop("mas sim, fui eu mesmo.", 1);
    wait(250);
    say_stop("`3Você é bem popular,", &current_sprite);
    wait(250);
    say_stop("`3até ouvi a filha do prefeito falando de você.", &current_sprite);
    wait(250);
    say_stop("Christina, sério?! O que ela disse?", 1);
    wait(250);
    say_stop("`3Ah, eu não estava prestando tanta atenção,", &current_sprite);
    wait(250);
    say_stop("`3só ouvi seu nome uma ou duas vezes.", &current_sprite);
    wait(250);
    say_stop("Cara!!", 1);
    sp_dir(1, 2);
    say_stop("Caraca, eu sou foda!", 1);
    unfreeze(1);
    unfreeze(&current_sprite);
    return;
   }
    say_stop("`3Nada demais, tá tudo bem calmo,", &current_sprite);
    wait(250);
    say_stop("`3o povo tá esperando o desfile que vai ter logo.", &current_sprite);
    wait(250);
    say_stop("Ah.", 1);
    unfreeze(1);
    unfreeze(&current_sprite);
    return;


  }
 unfreeze(1);
 unfreeze(&current_sprite);
}

void hit( void )
{
 freeze(&current_sprite);
 say_stop("`3Ai meu Deus, por favor não me machuca, moço...", &current_sprite);
 unfreeze(&current_sprite);
}
