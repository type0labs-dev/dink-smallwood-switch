//script for tree

//fixing bad script for V1.03

void main( void )
{
preload_seq(167);
sp_hard(&current_sprite, 0);
draw_hard_sprite(&current_sprite);

}

void talk(void)
{
 say_stop("`0Eu tenho treezentos anos... HAW HAW HAW!", &current_sprite);
 wait(400);
 say_stop("Essa também é a coisa mais sem graça que eu já ouvi na vida.", 1);
}

void die(void)
{
 say("`0Sua mágica é treeinútil contra mim... HAW HAW HAW!", &current_sprite);
 sp_hard(&current_sprite, 0);
 draw_hard_sprite(&current_sprite);
}
