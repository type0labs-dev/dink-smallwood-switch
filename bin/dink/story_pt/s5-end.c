void main (void)
{
 //end sequence for s5
 freeze(1);
 freeze(&temp1hold);
 freeze(&temp2hold);
 freeze(&temp3hold);
wait(500);
screenlock(0);
say_stop("`2Conseguiu! Conseguiu, Smallwood!", &temp1hold);
wait(500);
say_stop("`#Dink, você me salvou! Você é um herói!", &temp3hold);
wait(500);
//choice statement just for fun
choice_start();
"Poxa, não foi nada!"
"Na verdade, eu salvei todos vocês."
choice_end();
wait(500);
say_stop("`#De qualquer forma, somos muito gratos.", &temp2hold);
wait(500);
say_stop("`2Esses dois dragões estão aterrorizando tudo há um mês.", &temp1hold);
wait(500);
say_stop("`2Tudo começou quando construímos esta vila em cima do ninho deles.", &temp1hold);
wait(500);
say_stop("Então, basicamente, eu matei dois dragões inocentes que só estavam protegendo a própria casa?", 1);
wait(500);
say_stop("`2Hã... tenho que voltar pra loja, falou!", &temp1hold);
move_stop(&temp1hold, 6, 670,1);
sp_active(&temp1hold, 0);

 int &door = sp(2);
 sp_prop(&door, 1);


&story = 12;
&s5-jop = 4;
 unfreeze(1);
 unfreeze(&temp1hold);
 unfreeze(&temp2hold);
 unfreeze(&temp3hold);
 kill_this_task();
}
