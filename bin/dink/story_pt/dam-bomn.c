//Bomb noise

void damage ( void )
{
//30th: one noise per bomb; overlapping explosions kept re-hitting each other and filled all 64 sound channels
int &done = sp_custom("noise", &current_sprite, -1);
if (&done == 0)
{
  sp_custom("noise", &current_sprite, 1);
  playsound(6, 32050, 0,0,0);
}
}
