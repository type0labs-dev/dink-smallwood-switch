void main( void )
{
sp_touch_damage(&current_sprite, -1);

}

void touch( void )
{
int &has_nut = count_item("item-nut");
if (&has_nut > 0)
{
    Playsound(10,22050,0,0,0);
    //DinkC ignores an assignment on the same line as its if (MERROR), so this must be a block
    if (&nuts_total < 1)
    {
        &nuts_total = 1;
    }
    &nuts_total += 1;
    if (&nuttree < 1)
    {
        &nuttree = 1;
        &story = 3;
    }
    say("Picked up another nut! (Total: &nuts_total)", 1);
    draw_status();
    sp_active(&current_sprite, 0);
    return;
}

int &junk = free_items();

if (&junk < 1)
 {
 say("I'm full!  I can't pick up anything else.", 1);
 return;
 }
Playsound(10,22050,0,0,0);
add_item("item-nut",438, 19);
&nuts_total = 1;

        if (&nuttree < 1)
        {
        &nuttree = 1;
        &story = 3;
        }

        say("I picked up a nut!",1);
        draw_status();
        sp_active(&current_sprite, 0);

 }
