void main( void )
{
if (&nuttree == 1)
{
int &who = sp(6);
freeze(1);
freeze(&who);
freeze(&current_sprite);
wait(1000);
say_stop("Ei, essa é a Lyna com o Milder Flatstomp!", 1);
wait(500);
say_stop("`6Cê sabe que eu te amo, gata... então qual é o problema?", &current_sprite);
wait(250);
say_stop("`4Milder... quero te conhecer melhor primeiro.", &who);
wait(250);
say_stop("`4Eu também tenho conteúdo, sabia?", &who);
wait(250);
say_stop("`6Você fala demais, saca?", &current_sprite);
wait(250);
say_stop("`4Seu babaca!", &who);
wait(250);
unfreeze(&who);
move_stop(&who, 2, 334, 1);
move_stop(&who, 4, -10, 1);
sp_active(&who,0);
say_stop("`6Ihh ficou pistola!", &current_sprite);
unfreeze(&current_sprite);
move_stop(&current_sprite, 4, 84, 1);
move_stop(&current_sprite, 8, -10, 1);
sp_active(&current_sprite,0);
unfreeze(1);
&nuttree = 2;
}
}
