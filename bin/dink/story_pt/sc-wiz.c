void main( void )
{
 int &pap;
 int &wherex;
 int &wherey;
}

void talk( void )
{
    external("achievement", "award", 15);

 &wherex = sp_x(&current_sprite, -1);
 &wherey = sp_y(&current_sprite, -1);
 freeze(1);
 freeze(&current_sprite);
 if (&story > 14)
 {
  say_stop("`6Mandou bem, hein!", &current_sprite);
  wait(250);
  say_stop("`6Falou.", &current_sprite);
  int &mcrap = create_sprite(&wherex, &wherey, 7, 167, 1);
  sp_seq(&mcrap, 167);
  playsound(24, 22052, 0, 0, 0);
  unfreeze(1);
  unfreeze(&current_sprite);
  &snowc = 1;
  sp_active(&current_sprite, 0);  
  return;
 }
 say_stop("Quem... quem é você?", 1);
 wait(250);
 say_stop("`6Eu? Quem é você, que não é um goblin por essas bandas?!?", &current_sprite);
 wait(250);                           
 say_stop("Do que você tá falando?", 1);
 wait(250);
 say_stop("`6Da guerra, a guerra dos goblins!", &current_sprite);
 wait(250);
 say_stop("`6Eu tenho que defender este castelo, não posso deixar eles tomarem de volta.", &current_sprite);
 wait(250);
 say_stop("As... as guerras dos goblins, terminaram há muito, muito tempo!!", 1);
 wait(250);
 say_stop("Eles não lutam há mais de 100 anos!", 1);
 wait(250);
 say_stop("`6O quê?!?", &current_sprite);
 wait(250);
 say_stop("`6Isso é verdade?", &current_sprite);
 wait(250);
 say_stop("Infelizmente é...", 1);
 wait(250);
 say_stop("`6E... e a cidade de KernSin?", &current_sprite);
 wait(250);
 say_stop("Oooolha, bem, tanto a cidade quanto o castelo foram destruídos", 1);
 wait(250);
 say_stop("durante a última parte da guerra, há 100 anos.", 1);
 wait(250);
 say_stop("Depois foi parcialmente reconstruída e agora é a cidadezinha de KernSin.", 1);
 wait(250);
 say_stop("`6Isso... isso é demais. A gente venceu a guerra?", &current_sprite);
 wait(250);
 say_stop("Sim.", 1);
 wait(1000);
 say_stop("`6Eu... eu preciso ir a algum lugar, pensar sobre o que aconteceu.", &current_sprite);
 wait(250);
 say_stop("`6Obrigado... qual é o seu nome, amigo?", &current_sprite);
 wait(250);
 say_stop("Dink Smallwood, senhor.", 1);
 wait(250);
 say_stop("`6SMALLWOOD?!?", &current_sprite);
 wait(250);
 say_stop("`6Pensei que você tinha sido exilado.", &current_sprite);
 wait(250);
 say_stop("O quê??", 1);
 wait(250);
 say_stop("`6Claro, há 100 anos, ele já teria filhos agora.", &current_sprite);
 wait(250);
 say_stop("Ei, você quer me contar do que está falando?", 1);
 wait(250);
 say_stop("`6Sua família tem uma linhagem interessante.", &current_sprite);
 wait(250);
 say_stop("`6Os anciões são atraídos por você,", &current_sprite);
 wait(250);
 say_stop("`6eles podem extrair e se alimentar da magia da sua família.", &current_sprite);
 wait(250);
 say_stop("`6E se alguém destruísse você, ganharia um poder imenso.", &current_sprite);
 wait(250);
 say_stop("Há um caos se formando nesta terra agora.", 1);
 wait(250);
 say_stop("Não sabemos quem está por trás disso também. Eu estava a caminho", 1);
 wait(250);
 say_stop("das Terras Sombrias quando vim aqui, tenho que resgatar um amigo.", 1);
 wait(250);
 say_stop("`6Cuidado, Dink, quem estiver por trás disso provavelmente é um ancião,", &current_sprite);
 wait(250);
 say_stop("`6fazendo tudo parecer culpa de outra pessoa.", &current_sprite);
 wait(500);
 say_stop("`6Preciso ir, cuidado, Dink, e boa sorte.", &current_sprite);
 int &mcrap = create_sprite(&wherex, &wherey, 7, 167, 1);
 sp_seq(&mcrap, 167);
 playsound(24, 22052, 0, 0, 0);
 unfreeze(1);
 unfreeze(&current_sprite);
 &snowc = 1;
 sp_active(&current_sprite, 0);
}

void hit( void )
{
 &wherex = sp_x(&current_sprite, -1);
 &wherey = sp_y(&current_sprite, -1);
 say("`6Má ideia...", &current_sprite);
 &pap = random(3, 1);
 if (&pap == 1)
 {
  int &mcrap = create_sprite(&wherex, &wherey, 7, 167, 1);
  sp_seq(&mcrap, 167);
  playsound(24, 22052, 0, 0, 0);
  int &mcrap2 = create_sprite(100, 143, 7, 167, 1);
  sp_seq(&mcrap2, 167);
  sp_x(&current_sprite, 100);
  sp_y(&current_sprite, 143);
 }
 if (&pap == 2)
 {
  int &mcrap = create_sprite(&wherex, &wherey, 7, 167, 1);
  sp_seq(&mcrap, 167);
  playsound(24, 22052, 0, 0, 0);
  int &mcrap2 = create_sprite(429, 151, 7, 167, 1);
  sp_seq(&mcrap2, 167);
  sp_x(&current_sprite, 429);
  sp_y(&current_sprite, 151);
 }
 if (&pap == 3)
 {
  int &mcrap = create_sprite(&wherex, &wherey, 7, 167, 1);
  sp_seq(&mcrap, 167);
  playsound(24, 22052, 0, 0, 0);
  int &mcrap2 = create_sprite(288, 301, 7, 167, 1);
  sp_seq(&mcrap2, 167);  
  sp_x(&current_sprite, 288);
  sp_y(&current_sprite, 301);  
 }
}
