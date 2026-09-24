//this script is for the red potion

void main( )
{
sp_touch_damage(&current_sprite, -1);
sp_seq(&current_sprite, 56);
sp_brain(&current_sprite, 6);

}

void touch( void )
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
  int &hold = sp_editor_num(&current_sprite);
  if (&hold != 0)
    {
     //this was placed by the editor, lets make it not come back
     editor_type(&hold, 1); 
     //kill food forever
    }

&strength += 1;
Playsound(10,22050,0,0,0);
//shrink to this percent then die
sp_brain_parm(&current_sprite, 5);
sp_brain(&current_sprite, 12);
sp_touch_damage(&current_sprite, 0);
sp_timing(&current_sprite, 0);
}
