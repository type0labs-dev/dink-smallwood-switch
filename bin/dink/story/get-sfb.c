//sack of grain

void main( void )
{
sp_touch_damage(&current_sprite, -1);
}

void talk(void)
{
Say("A lovely scroll.", 1);
}


void touch(void)
{
  //30th: taking loot that came out of a chest opens that chest for good (see make.c)
  int &chest = sp_custom("chest", &current_sprite, -1);
  if (&chest > 0)
  {
    int &cseq = sp_custom("chest_seq", &current_sprite, -1);
    int &cframe = sp_custom("chest_frame", &current_sprite, -1);
    editor_type(&chest, 4);
    editor_seq(&chest, &cseq);
    editor_frame(&chest, &cframe);
  }
//dink touched this sprite
Playsound(10,22050,0,0,0);
sp_brain_parm(&current_sprite, 10);
sp_brain(&current_sprite, 12);
sp_touch_damage(&current_sprite, 0);
sp_timing(&current_sprite, 0);
add_magic("item-sfb",437, 2);
say("I now have the hellfire magic!", 1);
  //kill this item so it doesn't show up again for this player
  int &hold = sp_editor_num(&current_sprite);
  if (&hold != 0)
  editor_type(&hold, 1); 

}
