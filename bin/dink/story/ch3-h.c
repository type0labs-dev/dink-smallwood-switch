//script for chest with heart in it

void main( void)
{
preload_seq(175);
sp_brain(&current_sprite, 0);
sp_hitpoints(&current_sprite, 0);
}

void hit ( void )
 {
  //play noise
  int &hold = sp_editor_num(&current_sprite);

  //30th: the chest stays open for good only once its loot is taken (make.c hands &hold to the loot)
  &save_x = sp_x(&current_sprite, -1);
  &save_y = sp_y(&current_sprite, -1);
  external("make", "heart", &hold, 175, 6);

  sp_seq(&current_sprite, 175);
  sp_script(&current_sprite, "");
  sp_notouch(&current_sprite, 1);
  sp_nohit(&current_sprite, 1);
  kill_this_task();
 }
