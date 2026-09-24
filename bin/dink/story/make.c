//make, contains info on making items, use EXTERNAL to call what you need.

void sheart( void )
{
&save_y += 1;
int &crap = create_sprite(&save_x, &save_y, 6, 54, 1);
sp_script(&crap, "sheart");
}

void mgold( void )
{
&save_y += 1;
int &crap = create_sprite(&save_x, &save_y, 6, 178, 4);
sp_script(&crap, "mgold");
//30th: loot out of a chest remembers it (external args: chest editor number, open seq, frame)
int &chest = &arg1;
sp_custom("chest", &crap, &chest);
&chest = &arg2;
sp_custom("chest_seq", &crap, &chest);
&chest = &arg3;
sp_custom("chest_frame", &crap, &chest);
}

void lgold( void )
{
&save_y += 1;
int &crap = create_sprite(&save_x, &save_y, 6, 178, 4);
sp_script(&crap, "lgold");

}


void mpotion( void )
{
&save_y += 1;
int &crap = create_sprite(&save_x, &save_y, 6, 178, 4);
sp_script(&crap, "ppotion");
//30th: loot out of a chest remembers it (external args: chest editor number, open seq, frame)
int &chest = &arg1;
sp_custom("chest", &crap, &chest);
&chest = &arg2;
sp_custom("chest_seq", &crap, &chest);
&chest = &arg3;
sp_custom("chest_frame", &crap, &chest);
}

void rpotion( void )
{
//strength potion
&save_y += 1;
int &crap = create_sprite(&save_x, &save_y, 6, 178, 4);
sp_script(&crap, "rpotion");
//30th: loot out of a chest remembers it (external args: chest editor number, open seq, frame)
int &chest = &arg1;
sp_custom("chest", &crap, &chest);
&chest = &arg2;
sp_custom("chest_seq", &crap, &chest);
&chest = &arg3;
sp_custom("chest_frame", &crap, &chest);
}

void spotion( void )
{
//strength potion
&save_y += 1;
int &crap = create_sprite(&save_x, &save_y, 6, 178, 4);
sp_script(&crap, "rpotion");
}


void dpotion( void )
{
//strength potion
&save_y += 1;
int &crap = create_sprite(&save_x, &save_y, 6, 178, 4);
sp_script(&crap, "bpotion");
}



void apotion( void )
{
int &crap = create_sprite(&save_x, &save_y, 6, 178, 4);
sp_script(&crap, "apotion");
//30th: loot out of a chest remembers it (external args: chest editor number, open seq, frame)
int &chest = &arg1;
sp_custom("chest", &crap, &chest);
&chest = &arg2;
sp_custom("chest_seq", &crap, &chest);
&chest = &arg3;
sp_custom("chest_frame", &crap, &chest);
}


void papgold( void )
{
int &crap = create_sprite(&save_x, &save_y, 6, 178, 4);
sp_script(&crap, "papgold");
//30th: loot out of a chest remembers it (external args: chest editor number, open seq, frame)
int &chest = &arg1;
sp_custom("chest", &crap, &chest);
&chest = &arg2;
sp_custom("chest_seq", &crap, &chest);
&chest = &arg3;
sp_custom("chest_frame", &crap, &chest);

}

void gold500( void )
{
int &crap = create_sprite(&save_x, &save_y, 6, 178, 4);
sp_script(&crap, "gold500");
//30th: loot out of a chest remembers it (external args: chest editor number, open seq, frame)
int &chest = &arg1;
sp_custom("chest", &crap, &chest);
&chest = &arg2;
sp_custom("chest_seq", &crap, &chest);
&chest = &arg3;
sp_custom("chest_frame", &crap, &chest);

}


void sfb( void )
{
int &crap = create_sprite(&save_x, &save_y, 6, 422, 7);
sp_script(&crap, "get-sfb");
//30th: loot out of a chest remembers it (external args: chest editor number, open seq, frame)
int &chest = &arg1;
sp_custom("chest", &crap, &chest);
&chest = &arg2;
sp_custom("chest_seq", &crap, &chest);
&chest = &arg3;
sp_custom("chest_frame", &crap, &chest);
}

void lheart( void )
{
int &crap = create_sprite(&save_x, &save_y, 6, 54, 1);
sp_script(&crap, "sheart");
}

void gheart( void )
{
int &crap = create_sprite(&save_x, &save_y, 6, 53, 1);
sp_script(&crap, "gheart");
//30th: loot out of a chest remembers it (external args: chest editor number, open seq, frame)
int &chest = &arg1;
sp_custom("chest", &crap, &chest);
&chest = &arg2;
sp_custom("chest_seq", &crap, &chest);
&chest = &arg3;
sp_custom("chest_frame", &crap, &chest);
}

void heart( void )
{
int &crap = create_sprite(&save_x, &save_y, 6, 52, 1);
sp_script(&crap, "heart");
//30th: loot out of a chest remembers it (external args: chest editor number, open seq, frame)
int &chest = &arg1;
sp_custom("chest", &crap, &chest);
&chest = &arg2;
sp_custom("chest_seq", &crap, &chest);
&chest = &arg3;
sp_custom("chest_frame", &crap, &chest);
}

void food1( void )
{
int &crap = create_sprite(&save_x, &save_y, 6, 421, 1);
sp_script(&crap, "sfood");
}

void food2( void )
{
int &crap = create_sprite(&save_x, &save_y, 6, 421, 2);
sp_script(&crap, "sfood");
}

void food7( void )
{
int &crap = create_sprite(&save_x, &save_y, 6, 421, 7);
sp_script(&crap, "sfood");
}

void food8( void )
{
int &crap = create_sprite(&save_x, &save_y, 6, 421, 8);
sp_script(&crap, "sfood");
}
void foodduck( void )
{

int &rrand = random(2, 1);
if (&rrand == 1)
int &crap = create_sprite(&save_x, &save_y, 6, 421, 5);

if (&rrand == 2)
int &crap = create_sprite(&save_x, &save_y, 6, 421, 6);

//sp_script(&crap, "sfood");

}


