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
    say("Peguei outra noz! (Total: &nuts_total)", 1);
    draw_status();
    sp_active(&current_sprite, 0);
    return;
}

int &junk = free_items();

if (&junk < 1)
 {
 say("Tô cheio! Não dá pra carregar mais nada.", 1);
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

        say("Peguei uma noz!",1);
        draw_status();
        sp_active(&current_sprite, 0);

 }
