void main( void )
{
 //setup daugher

 sp_base_walk(&current_sprite, 220);
 sp_speed(&current_sprite, 1);
 sp_brain(&current_sprite, 16);
 sp_hitpoints(&current_sprite, 50);
 preload_seq(221);
 preload_seq(223);
 preload_seq(225);
 preload_seq(227);
 preload_seq(229);
 sp_pseq(&temp3hold, 223);
 sp_pframe(&temp3hold, 1);

}

void hit (void)
{
playsound(12, 22050, 0, &temp3hold, 0);
}

void die( void )
{
 //dink fails
if (&life > 0)
{
 say("Nããão! A garota morreu! EU FALHEI!!!!!!!", 1);
 &life = 0;
 }
}

void talk( void )
{
if (&story > 11)
  say("`#Onde cê aprendeu a brigar desse jeito?",&current_sprite);
}
