//generic script for killing things so they don't come back

void main( void )
{
sp_exp(&current_sprite, 5000);
}

void die( void )
{
    external("achievement", "award", 16);

  int &hold = sp_editor_num(&current_sprite);
  if (&hold != 0)
  editor_type(&hold, 1); 
say("Uau, que porco daqueles!",1);
}
