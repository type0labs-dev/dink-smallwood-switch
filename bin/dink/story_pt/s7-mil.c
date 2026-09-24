void main( void)
{

int &fighting = 0;
if (&story < 15)
{
        preload_seq(24);
        preload_seq(161);
        init("load_sequence_now graphics\effects\magic\seth1w 581 75 43 133 -19 -16 23 16");
        init("load_sequence_now graphics\effects\magic\seth3w 583 75 44 126 -21 -21 19 16");
        init("load_sequence_now graphics\effects\magic\seth7w 587 75 42 123 -21 -16 18 16");
        init("load_sequence_now graphics\effects\magic\seth9w 589 75 44 125 -20 -16 20 16");
        init("load_sequence_now graphics\effects\magic\pose 580 75 41 129 -30 -16 31 10");
  return;
 }

sp_active(&current_sprite, 0);
}
  void talk (void)
  {

if (&story > 14)
  {
   say("Pobre Milder.",1);
   return;
  }

if (&fighting == 1)
  {
   say("Milder, acorda! Me ajuda a lutar com esse cara!",1);
   return;
  }


    freeze(1);
   say_stop("Milder! Milder!", 1);
   &fighting = 1;
   wait(300);
   say_stop_xy("`6<gemido>", 20, 180);
   wait(300);
   say_stop("Tá me ouvindo?", 1);
   wait(300);
   say_stop_xy("`6..criador de porco..é..você?", 20, 180);
   wait(300);
   say_stop("Sim!", 1);
   wait(300);
   say_stop("Er, não, quero dizer.. me conta o que aconteceu!", 1);
   wait(300);
   say_stop_xy("`6..fui deixado aqui pra morrer por uma monstruosidade..", 20, 180);
   wait(300);
   say_stop("Ah, pelo Cast?", 1);
   wait(300);
   say_stop_xy("`6..não..", 20, 180);
   wait(300);
   say_stop_xy("`6..o Cast era só uma fachada.. ele é o mal puro..", 20, 180);
   wait(300);
   say_stop_xy("`6..corre..corre antes que seja tarde..", 20, 180);
   wait(300);
choice_start();
"Recusar a ir sem ele"
"Seguir o conselho dele"
choice_end();
   wait(300);

if (&result == 1)
  {
   say_stop("Não vou te deixar pra trás, Milder.", 1);
   wait(300);
   say_stop_xy("`6..mas por quê? eu fui tão cuzão com você quando criança...", 20, 180);
   wait(300);
   say_stop("É a coisa honrosa a se fazer.", 1);
   wait(300);
   say_stop_xy("`6..você é mais cavaleiro do que eu nunca fui, dink...", 20, 180);
   wait(300);
   say_stop("Besteira. Consegue andar?", 1);
   wait(300);
   say_stop_xy("`6..acho que sim..pega minha..", 20, 180);
  }


if (&result == 2)
  {
   say_stop("Beleza, falou.", 1);
   wait(300);
   say_stop_xy("`6..eu..entendo...diz pra Lyna que eu amo ela...", 20, 180);
   wait(300);
   say_stop("Dizer? Eu vou MOSTRAR amor pra ela... moohahahha!", 1);
   wait(300);
   say_stop_xy("`6..seu filho da puta...se eu tivesse forças pra...", 20, 180);
  }

wait(1000);
playsound(24, 22052, 0, 0, 0);
int &mcrap = create_sprite(320, 100, 7, 167, 1);
sp_seq(&mcrap, 167);
wait(200);
&temp1hold = create_sprite(320, 150,0, 580, 1);


int &crap = get_burn();

if (&crap == 0)
playmidi("1004");
if (&crap > 0)
playmidi("1015");

wait(1000);
 say_stop_xy("`6NAOOO! É ELE!", 20, 180);
 wait(300);
say_stop("Que porra é essa?! Quem diabos é você?", 1);
wait(300);
say_stop("`%Eu sou o princípio e o fim.", &temp1hold);
wait(300);
 say_stop_xy("`6..mata ele, dink..mata ele...", 20, 180);
wait(300);
say_stop("`%Eu sou tudo que você ama.", &temp1hold);
wait(300);
say_stop("`%Eu sou tudo que você odeia.", &temp1hold);
wait(300);
say_stop("Você é doente e perturbado, isso sim.", 1);
wait(300);
say_stop_xy("`6..o nome dele é Seth.. ele é um ancião...ele matou os outros..", 20, 180);
wait(300);
say("`4<lança explosão>", &temp1hold);
int &bomb = create_sprite(329, 256, 7,161,1);
sp_seq(&bomb, 161);
playsound(6, 22050, 0,0,0);

say_stop_xy("`6aaargh..", 20, 180);
wait(300);
say_stop("Milder?", 1);
wait(300);
say_stop("`4<abre um sorriso maligno pra você>", &temp1hold);
wait(300);
say_stop("POR DEUS, PELA COROA E POR TUDO QUE É SAGRADO, EU VOU TE DESTRUIR, SETH!", 1);

sp_script(&temp1hold, "s7-boss");
unfreeze(1);

  }
