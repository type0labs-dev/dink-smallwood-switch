void main( void )
{

//playsound(43, 22050,0,0,0);

&s4-duck = 2;
&story = 11;
freeze(1);
//cutscene

//create man
int &man = create_sprite(290, 460, 0, 0, 0);
sp_base_walk(&man, 380);
sp_speed(&man, 1);
sp_timing(&man, 33);
preload_seq(381);
preload_seq(383);
preload_seq(387);
preload_seq(389);

//create little girl
int &girl = create_sprite(290, 460, 0, 0, 0);
sp_base_walk(&girl, 250);
sp_speed(&girl, 1);
sp_timing(&girl, 33);
preload_seq(251);
preload_seq(253);
preload_seq(257);
preload_seq(259);

int &junk = sp_y(1, -1);
if (&junk < 220)
   sp_dir(1, 2);

say("`0Anda logo, Kelly!", &man);
move_stop(&man, 8, 430, 1);
move_stop(&man, 9, 380, 1);
say_stop("`0Isso vai ser tão legal e...", &man);
wait(250);
say_stop("`0MAS QUE PORRA!?!?!", &man);
sp_pseq(&man,387);
sp_pframe(&man,1);
sp_seq(&man,0);
wait(250);
sp_pseq(&man,381);
sp_pframe(&man,1);
sp_seq(&man,0);
say_stop("Eita.", 1);
wait(250);
sp_pseq(&man,383);
sp_pframe(&man,1);
sp_seq(&man,0);

wait(250);
sp_pseq(&man,389);
sp_pframe(&man,1);
sp_seq(&man,0);
say_stop("`0NÃOOOO!!!!!", &man);
move_stop(&girl, 9, 350, 1);
move_stop(&girl, 7, 280, 1);
say_stop("`#Pai, o que aconteceu?", &girl);
wait(250);
say_stop("`0GUARDAS!!!!!!!", &man);
wait(250);
say_stop("`0SOCORRO!", &man);
wait(250);
say_stop("`0ESSE CARA MATOU A SANTA GALINHA!", &man);
wait(250);


int &guard = create_sprite(290, 460, 0, 0, 0);
sp_base_walk(&guard, 290);
sp_speed(&guard, 1);
sp_timing(&guard, 33);
preload_seq(291);
preload_seq(293);
preload_seq(297);
preload_seq(299);

move_stop(&guard, 8, 380, 1);
say_stop("`5EU PRECISO VINGAR A DEUSA ALADA!", &guard);
wait(300);
say_stop("`0Kelly, que que você tá fazendo?", &man);
wait(300);
say_stop("`#Tô comendo.", &girl);
wait(300);
move_stop(&guard, 9, 330, 1);
say_stop("`5Seu guarda, sua filha tá comendo o nosso deus.", &guard);
wait(300);
say_stop("`5Acho que a gente vai ter que matar ela também.", &guard);
wait(300);
say_stop("`#Essa carne... tá uma delícia!", &girl);
wait(300);
say_stop("`0Perai... não era pra tá crua e tal?", &man);
wait(300);
say_stop("`5Acho que um pedacinho não vai fazer mal...", &guard);
wait(1000);
say_stop("`5TÁ UMA DELÍCIA!", &guard);
say_stop("`0E NÃO ENCHI TANTO!", &man);
wait(300);
say_stop("`5Dink, você magicamente transformou nossos seres supremos em comida!", &guard);
wait(300);
say_stop("Não... tem uma explicação perfeita, veja, o atrito cozinhou e...", 1);

wait(300);
say_stop("`0Quem liga pra isso!", &man);
wait(300);
say_stop("`5Dink é um herói! A GENTE PRECISA CONTAR PROS OUTROS!", &guard);
unfreeze(1);
move(&guard, 1, 300, 1);
move_stop(&man, 4, 300, 1);
move(&guard, 2, 480, 1);
move_stop(&man, 2, 480, 1);
move_stop(&girl, 3, 310, 1);
say_stop("`#Falou, Dink.", &girl);
move_stop(&girl, 2, 470, 1);

}






