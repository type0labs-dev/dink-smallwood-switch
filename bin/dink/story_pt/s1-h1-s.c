void main ( void )
{
if (&story == 3)
{
 freeze(1);
 &vision = 1;
 wait(1000);
 say_stop("Mãe, nãooooo!", 1);
 move_stop(1, 8, 259, 0);
 move_stop(1, 4, 203, 0);
 move_stop(1, 8, 151, 0);
 wait(200);
 say_stop("Mãe, você não pode morrer, nãooo, eu... eu...", 1);
 wait(200);
 say_stop("nunca soube o quanto eu me importava com você", 1);
 say_stop("até agora.", 1);
 wait(250);
 say_stop("Ahh, fumaça demais... tenho que sair daqui...", 1);
 &story = 4;
 move_stop(1, 2, 259, 0);
 move_stop(1, 6, 321, 0);
 move_stop(1, 2, 398, 0);
 return;
}
if (&story > 3)
{
 if (&letter == 1)
  {
  Debug("Why am I here...story is &story and letter is &letter");
  &vision = 2;
  int &thing;
  &thing = create_sprite(404, 220, 0, 422, 5);
  sp_script(&thing,"s1-ltr");
  move_stop(1, 8, 370, 1);
  say("Lá está aquela carta.", 1);
  wait(500);
  move_stop(1, 8, 185, 1);
  move_stop(1, 6, 373, 1);
  return;
  }
 &vision = 2;
 say("Minha antiga casa...", 1);
  return;
}

}
