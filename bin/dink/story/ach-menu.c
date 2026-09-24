//menu for displaying achievements - for title screen or ingame

void achievement
{
int &acrap
int &bcrap
int &ccrap
int &dcrap
int &ecrap
int &fcrap
int &gcrap
int &hcrap
int &icrap

//check which achievements the player has.
//Only 9 at once because only twenty fit on a choice menu
//and I need options to indicate having/not having the achievement.
list:
&acrap = game_exist(21)
&bcrap = game_exist(22)
&ccrap = game_exist(23)
&dcrap = game_exist(24)
&ecrap = game_exist(25)
&fcrap = game_exist(26)
&gcrap = game_exist(27)
&hcrap = game_exist(28)
&icrap = game_exist(29)

choice_start();
set_y 160
title_start()
Selecione uma conquista para ver detalhes:
title_end()
(&acrap == 0) "Não Sou Criador de Porcos! (Pendente)"
(&acrap == 1) "Não Sou Criador de Porcos! (Conquistada!)"
(&bcrap == 0) "Castigador de Aves (Pendente)"
(&bcrap == 1) "Castigador de Aves (Conquistada!)"
(&ccrap == 0) "Assunto pra Fofoca (Pendente)"
(&ccrap == 1) "Assunto pra Fofoca (Conquistada!)"
(&dcrap == 0) "Anabolizantes São Perigosos (Pendente)"
(&dcrap == 1) "Anabolizantes São Perigosos (Conquistada!)"
(&ecrap == 0) "Herói por Acaso (Pendente)"
(&ecrap == 1) "Herói por Acaso (Conquistada!)"
(&fcrap == 0) "Salvando a Lavoura (Pendente)"
(&fcrap == 1) "Salvando a Lavoura (Conquistada!)"
(&gcrap == 0) "Karl Marx Te Odeia (Pendente)"
(&gcrap == 1) "Karl Marx Te Odeia (Conquistada!)"
(&hcrap == 0) "Trabalho Simples (Pendente)"
(&hcrap == 1) "Trabalho Simples (Conquistada!)"
(&icrap == 0) "Bastardo Sem Coração (Pendente)"
(&icrap == 1) "Bastardo Sem Coração (Conquistada!)"
"Ir para Página 2"
"Fechar"
choice_end();

if (&result == 1)
{
choice_start()
set_y 240
set_title_color 14
title_start()
Não Sou Criador de Porcos! - 10 Pontos (Pendente)

Demonstrate your contempt for mom's chores by killing the pigs before you feed them.
title_end()
"OK"
choice_end()
goto list;
}

if (&result == 2)
{
//Let's try displaying the banner while they view earned achievements
&juggle = create_sprite(370, 50, 0, 99, 1)
sp_que(&juggle, 1000)
choice_start()
set_y 240
set_title_color 14
title_start()
Não Sou Criador de Porcos! - 10 Pontos (Conquistada!)

Good job killing those pigs before you fed them.
It's kind of odd how Milder didn't notice, isn't it?

title_end()
"OK"
choice_end()
sp_active(&juggle, 0)
goto list;
}

if (&result == 3)
{
choice_start()
set_y 240
set_title_color 14
title_start()
Castigador de Aves - 10 Pontos (Pendente)

Kill Quackers the duck.

title_end()
"OK"
choice_end()
goto list;
}

if (&result == 4)
{
&juggle = create_sprite(370, 50, 0, 99, 2)
sp_que(&juggle, 1000)
choice_start()
set_y 240
set_title_color 14
title_start()
Castigador de Aves - 10 Pontos (Conquistada!)

You killed Quackers the duck! After he had just found the Golden Nut, too.

title_end()
"OK"
choice_end()
sp_active(&juggle, 0)
goto list;
}

if (&result == 5)
{
choice_start()
set_y 240
set_title_color 14
title_start()
Assunto pra Fofoca - 10 Pontos (Pendente)

Murder Chealse, that gossipy girl in Stonebrook.

Really, I'm just seeing how low you'll sink for an achievement.

title_end()
"OK"
choice_end()
goto list;
}

if (&result == 6)
{
&juggle = create_sprite(370, 50, 0, 99, 8)
sp_que(&juggle, 1000)
choice_start()
set_y 240
set_title_color 14
title_start()
Assunto pra Fofoca - 10 Pontos (Conquistada!)

Well, you killed Chealse.

You'll do anything for just 10 points, huh? Interesting. I'll file that one away.

title_end()
"OK"
choice_end()
sp_active(&juggle, 0)
goto list;
}

if (&result == 7)
{
choice_start()
set_y 240
set_title_color 14
title_start()
Anabolizantes São Perigosos - 10 Pontos (Pendente)

Slay that giant pillbug west of GoodHeart Castle.

You should anyway; there's a megapotion in it for you.

title_end()
"OK"
choice_end()
goto list;
}

if (&result == 8)
{
&juggle = create_sprite(370, 50, 0, 99, 3)
sp_que(&juggle, 1000)
choice_start()
set_y 240
set_title_color 14
title_start()
Anabolizantes São Perigosos - 10 Pontos (Conquistada!)

The giant pillbug is no more! Until it regenerates, at least.

But hey, you'll always have this achievement to prove you killed it.

title_end()
"OK"
choice_end()
sp_active(&juggle, 0)
goto list;
}

if (&result == 9)
{
choice_start()
set_y 300
set_title_color 14
title_start()
Herói por Acaso - 10 Pontos (Pendente)

Rescue the man from the evil "knights" who sometimes appear near Stonebrook.

He might even reward you, but don't get too excited.

title_end()
"OK"
choice_end()
goto list;
}

if (&result == 10)
{
&juggle = create_sprite(370, 50, 0, 99, 4)
sp_que(&juggle, 1000)
choice_start()
set_y 240
set_title_color 14
title_start()
Herói por Acaso - 10 Pontos (Conquistada!)

You saved Mister Money Bins. Don't spend that gold piece all in one place.

title_end()
"OK"
choice_end()
sp_active(&juggle, 0)
goto list;
}

if (&result == 11)
{
choice_start()
set_y 240
set_title_color 14
title_start()
Salvando a Lavoura - 10 Pontos (Pendente)

Save SmileStein's farm from the pillbugs.

title_end()
"OK"
choice_end()
goto list;
}

if (&result == 12)
{
&juggle = create_sprite(370, 50, 0, 99, 5)
sp_que(&juggle, 1000)
choice_start()
set_y 240
set_title_color 14
title_start()
Salvando a Lavoura - 10 Pontos (Conquistada!)

You beat the pillbug and saved the farm!

That talking pillbug sure was silly. You'll probably never see IT again.

title_end()
"OK"
choice_end()
sp_active(&juggle, 0)
goto list;
}

if (&result == 13)
{
choice_start()
set_y 240
set_title_color 14
title_start()
Karl Marx Te Odeia - 10 Pontos (Pendente)

Sell an Alknut.

You capitalist pig, you.

title_end()
"OK"
choice_end()
goto list;
}

if (&result == 14)
{
&juggle = create_sprite(370, 50, 0, 99, 6)
sp_que(&juggle, 1000)
choice_start()
set_y 240
set_title_color 14
title_start()
Karl Marx Te Odeia - 10 Pontos (Conquistada!)

You sold an Alknut. Whoopee.

Don't worry, I'm sure Karl has bigger things to worry about. Being dead, for one.

title_end()
"OK"
choice_end()
sp_active(&juggle, 0)
goto list;
}

if (&result == 15)
{
choice_start()
set_y 240
set_title_color 14
title_start()
Trabalho Simples - 10 Pontos (Pendente)

Help commit a robbery.

title_end()
"OK"
choice_end()
goto list;
}

if (&result == 16)
{
&juggle = create_sprite(370, 50, 0, 99, 7)
sp_que(&juggle, 1000)
choice_start()
set_y 240
set_title_color 14
title_start()
Trabalho Simples - 10 Pontos (Conquistada!)

You helped commit robbery.

It wasn't terribly successful, but you did avoid the blame. Now that's an achievement!

title_end()
"OK"
choice_end()
sp_active(&juggle, 0)
goto list;
}

if (&result == 17)
{
choice_start()
set_y 240
set_title_color 14
title_start()
Bastardo Sem Coração - 10 Pontos (Pendente)

Kill George.

Listen - you have free will. You don't actually have to do this. George isn't hurting anybody.

title_end()
"OK"
choice_end()
goto list;
}

if (&result == 18)
{
&juggle = create_sprite(370, 50, 0, 99, 9)
sp_que(&juggle, 1000)
choice_start()
set_y 300
set_title_color 14
title_start()
Bastardo Sem Coração - 10 Pontos (Conquistada!)

George is dead. He only wanted to be friends.

I'm complicit, aren't I? I made the achievement list. My God, the terrible power.

title_end()
"OK"
choice_end()
sp_active(&juggle, 0)
goto list;
}

if (&result == 20)
{
return
}

&acrap = game_exist(30)
&bcrap = game_exist(31)
&ccrap = game_exist(32)
&dcrap = game_exist(33)
&ecrap = game_exist(34)
&fcrap = game_exist(35)
&gcrap = game_exist(36)
&hcrap = game_exist(37)
&icrap = game_exist(38)

listb:
choice_start();
set_y 160
title_start()
Selecione uma conquista para ver detalhes:
title_end()
(&acrap == 0) "Curvem-se Perante Mim! (Pendente)"
(&acrap == 1) "Curvem-se Perante Mim! (Conquistada!)"
(&bcrap == 0) "Desfile da Morte(Pendente)"
(&bcrap == 1) "Desfile da Morte (Conquistada!)"
(&ccrap == 0) "Once a Farmer, Always a Farmer (Pendente)"
(&ccrap == 1) "Once a Farmer, Always a Farmer (Conquistada!)"
(&dcrap == 0) "Violência Doméstica (Pendente)"
(&dcrap == 1) "Violência Doméstica (Conquistada!)"
(&ecrap == 0) "Andar Sobre as Águas (Pendente)"
(&ecrap == 1) "Andar Sobre as Águas (Conquistada!)"
(&fcrap == 0) "Loose End (Pendente)"
(&fcrap == 1) "Loose End (Conquistada!)"
(&gcrap == 0) "Porco Lendário (Pendente)"
(&gcrap == 1) "Porco Lendário (Conquistada!)"
(&hcrap == 0) "Lenhador Insistente (Pendente)"
(&hcrap == 1) "Lenhador Insistente (Conquistada!)"
(&icrap == 0) "Caminho das Águas (Pendente)"
(&icrap == 1) "Caminho das Águas (Conquistada!)"
"Ir para Página 3"
"Fechar"
choice_end();

if (&result == 1)
{
choice_start()
set_y 240
set_title_color 14
title_start()
Curvem-se Perante Mim! - 10 Pontos (Pendente)

Purchase Bow Lore. If you can find it.

title_end()
"OK"
choice_end()
goto listb;
}

if (&result == 2)
{
&juggle = create_sprite(370, 50, 0, 99, 10)
sp_que(&juggle, 1000)
choice_start()
set_y 240
set_title_color 14
title_start()
Curvem-se Perante Mim! - 10 Pontos (Conquistada!)

You learned Bow Lore. That location can't be great for business.

title_end()
"OK"
choice_end()
sp_active(&juggle, 0)
goto listb;
}

if (&result == 3)
{
choice_start()
set_y 240
set_title_color 14
title_start()
Desfile da Morte - 10 Pontos (Pendente)

Carry out the Cast's plan by killing everyone at the parade in KernSin.

title_end()
"OK"
choice_end()
goto listb;
}

if (&result == 4)
{
&juggle = create_sprite(370, 50, 0, 99, 11)
sp_que(&juggle, 1000)
choice_start()
set_y 240
set_title_color 14
title_start()
Desfile da Morte - 10 Pontos (Conquistada!)

You did in both the Cast AND the people of KernSin.

This way, everybody loses and you win.

title_end()
"OK"
choice_end()
sp_active(&juggle, 0)
goto listb;
}

if (&result == 5)
{
choice_start()
set_y 240
set_title_color 14
title_start()
Once a Farmer, Always a Farmer - 10 Pontos (Pendente)

Return to your roots by feeding a pig in a distant land.

title_end()
"OK"
choice_end()
goto listb;
}

if (&result == 6)
{
&juggle = create_sprite(370, 50, 0, 99, 12)
sp_que(&juggle, 1000)
choice_start()
set_y 240
set_title_color 14
title_start()
Once a Farmer, Always a Farmer - 10 Pontos (Conquistada!)

You fed the Darklands pig. It didn't seem interested, but Mom would be proud anyway.

title_end()
"OK"
choice_end()
sp_active(&juggle, 0)
goto listb;
}

if (&result == 7)
{
choice_start()
set_y 240
set_title_color 14
title_start()
Violência Doméstica - 20 Pontos (Pendente)

Kill Jack. It's only tough if you don't know how.

title_end()
"OK"
choice_end()
goto listb;
}

if (&result == 8)
{
&juggle = create_sprite(370, 50, 0, 99, 13)
sp_que(&juggle, 1000)
choice_start()
set_y 240
set_title_color 14
title_start()
Violência Doméstica - 20 Pontos (Conquistada!)

Jack is dead. Nobody's thrilled about it, but at least he won't beat your aunt anymore.

title_end()
"OK"
choice_end()
sp_active(&juggle, 0)
goto listb;
}

if (&result == 9)
{
choice_start()
set_y 240
set_title_color 14
title_start()
Andar Sobre as Águas - 20 Pontos (Pendente)

Find the secret Koka Isle.

title_end()
"OK"
choice_end()
goto listb;
}

if (&result == 10)
{
&juggle = create_sprite(370, 50, 0, 99, 14)
sp_que(&juggle, 1000)
choice_start()
set_y 240
set_title_color 14
title_start()
Andar Sobre as Águas - 20 Pontos (Conquistada!)

You found Koka Isle. Have fun gambling with the ducks.

title_end()
"OK"
choice_end()
sp_active(&juggle, 0)
goto listb;
}

if (&result == 11)
{
choice_start()
set_y 240
set_title_color 14
title_start()
Loose End - 20 Pontos (Pendente)

Meet the wizard in the secret ice castle.

title_end()
"OK"
choice_end()
goto listb;
}

if (&result == 12)
{
&juggle = create_sprite(370, 50, 0, 99, 15)
sp_que(&juggle, 1000)
choice_start()
set_y 240
set_title_color 14
title_start()
Loose End - 20 Pontos (Conquistada!)

The "Ice Wizard" had some interesting things to say.
Too bad you'll never know how that storyline pans out.

title_end()
"OK"
choice_end()
sp_active(&juggle, 0)
goto listb;
}

if (&result == 13)
{
choice_start()
set_y 240
set_title_color 14
title_start()
Porco Lendário - 20 Pontos (Pendente)

Conquer your demons. Slay the Darklands pig.

title_end()
"OK"
choice_end()
goto listb;
}

if (&result == 14)
{
&juggle = create_sprite(370, 50, 0, 99, 16)
sp_que(&juggle, 1000)
choice_start()
set_y 240
set_title_color 14
title_start()
Porco Lendário - 20 Pontos (Conquistada!)

You slew the amazingly tough pig!

Nice work. I'd describe your performance as "radiant."

title_end()
"OK"
choice_end()
sp_active(&juggle, 0)
goto listb;
}

if (&result == 15)
{
choice_start()
set_y 240
set_title_color 14
title_start()
Lenhador Insistente - 10 Pontos (Pendente)

Throw a fireball at a tree. Fail to burn it. Get mocked.

title_end()
"OK"
choice_end()
goto listb;
}

if (&result == 16)
{
&juggle = create_sprite(370, 50, 0, 99, 17)
sp_que(&juggle, 1000)
choice_start()
set_y 240
set_title_color 14
title_start()
Lenhador Insistente - 10 Pontos (Conquistada!)

That goddamn tree.

title_end()
"OK"
choice_end()
sp_active(&juggle, 0)
goto listb;
}

if (&result == 17)
{
choice_start()
set_y 240
set_title_color 14
title_start()
Caminho das Águas - 40 Pontos (Pendente)

Exploit the famous hardness error. You know the one. If you don't, ask around.

title_end()
"OK"
choice_end()
goto listb;
}

if (&result == 18)
{
&juggle = create_sprite(370, 50, 0, 99, 18)
sp_que(&juggle, 1000)
choice_start()
set_y 240
set_title_color 14
title_start()
Caminho das Águas - 40 Pontos (Conquistada!)

You stepped into the great unknown. Be careful out there.

title_end()
"OK"
choice_end()
sp_active(&juggle, 0)
goto listb;
}

if (&result == 20)
{
return
}

&acrap = game_exist(39)
&bcrap = game_exist(40)
&ccrap = game_exist(41)
&dcrap = game_exist(42)
&ecrap = game_exist(43)
&fcrap = game_exist(44)
&gcrap = game_exist(45)
&hcrap = game_exist(46)
//&icrap = game_exist(47)

listc:
choice_start();
set_y 160
title_start()
Selecione uma conquista para ver detalhes:
title_end()
(&acrap == 0) "De Camponês a Herói (Pendente)"
(&acrap == 1) "De Camponês a Herói (Conquistada!)"
(&bcrap == 0) "Genocídio Total (Pendente)"
(&bcrap == 1) "Genocídio Total (Conquistada!)"
(&ccrap == 0) "Inimigo da Natureza (Pendente)"
(&ccrap == 1) "Inimigo da Natureza (Conquistada!)"
(&dcrap == 0) "Pugilista Supremo (Pendente)"
(&dcrap == 1) "Pugilista Supremo (Conquistada!)"
(&ecrap == 0) "Armado Até os Dentes (Pendente)"
(&ecrap == 1) "Armado Até os Dentes (Conquistada!)"
(&fcrap == 0) "Caçador de Tesouros (Pendente)"
(&fcrap == 1) "Caçador de Tesouros (Conquistada!)"
(&gcrap == 0) "Vencedor Raquítico (Pendente)"
(&gcrap == 1) "Vencedor Raquítico (Conquistada!)"
(&hcrap == 0) "Senhor do Grind (Pendente)"
(&hcrap == 1) "Senhor do Grind (Conquistada!)"
"Go back to Page 1"
"Fechar"
choice_end();

if (&result == 1)
{
choice_start()
set_y 240
set_title_color 14
title_start()
De Camponês a Herói - 50 Pontos (Pendente)

Defeat Seth, the Ancient.

You get a free achievement just for beating the game! Aren't I nice?

title_end()
"OK"
choice_end()
goto listc;
}

if (&result == 2)
{
&juggle = create_sprite(370, 50, 0, 99, 19)
sp_que(&juggle, 1000)
choice_start()
set_y 300
set_title_color 14
title_start()
De Camponês a Herói - 50 Pontos (Conquistada!)

You brought down Seth, the Programmer Self-insert.

I spared you the other pointless "progress achievements." You're welcome.

title_end()
"OK"
choice_end()
sp_active(&juggle, 0)
goto listc;
}

if (&result == 3)
{
choice_start()
set_y 300
set_title_color 14
title_start()
Genocídio Total - 50 Pontos (Pendente)

Defeat every enemy in the game at least once. Not one of each type; all of them.

If you let an enemy regenerate, it won't count again.

title_end()
"OK"
choice_end()
goto listc;
}

if (&result == 4)
{
&juggle = create_sprite(370, 50, 0, 99, 20)
sp_que(&juggle, 1000)
choice_start()
set_y 240
set_title_color 14
title_start()
Genocídio Total - 50 Pontos (Conquistada!)

You beat all the enemies! Wow, nice going!

If it weren't for spontaneous generation, they'd all be extinct!

title_end()
"OK"
choice_end()
sp_active(&juggle, 0)
goto listc;
}

if (&result == 5)
{
choice_start()
set_y 240
set_title_color 14
title_start()
Inimigo da Natureza - 50 Pontos (Pendente)

Burn down all the trees.

You've always wanted to anyway - now, you have an excuse.

title_end()
"OK"
choice_end()
goto listc;
}

if (&result == 6)
{
&juggle = create_sprite(370, 50, 0, 99, 21)
sp_que(&juggle, 1000)
choice_start()
set_y 300
set_title_color 14
title_start()
Inimigo da Natureza - 50 Pontos (Conquistada!)

You burned every burnable tree in the game!

Even their ability to be two trees across screens didn't stop you. Look at you go.

title_end()
"OK"
choice_end()
sp_active(&juggle, 0)
goto listc;
}

if (&result == 7)
{
choice_start()
set_y 240
set_title_color 14
title_start()
Pugilista Supremo - 80 Pontos (Pendente)

Beat Seth using only your fists.

No herb boots either. I saw you coming, Mr. or Ms. loophole finder.

title_end()
"OK"
choice_end()
goto listc;
}

if (&result == 8)
{
&juggle = create_sprite(370, 50, 0, 99, 22)
sp_que(&juggle, 1000)
choice_start()
set_y 240
set_title_color 14
title_start()
Pugilista Supremo - 80 Pontos (Conquistada!)

You punched Seth to death. Impressive!

As a kid, I thought a great weapon was required. You sure showed me.

title_end()
"OK"
choice_end()
sp_active(&juggle, 0)
goto listc;
}

if (&result == 9)
{
choice_start()
set_y 240
set_title_color 14
title_start()
Armado Até os Dentes - 60 Pontos (Pendente)

Have every weapon in the game at once.

Yes, at once. It's not like you don't have room.

title_end()
"OK"
choice_end()
goto listc;
}

if (&result == 10)
{
&juggle = create_sprite(370, 50, 0, 99, 23)
sp_que(&juggle, 1000)
choice_start()
set_y 240
set_title_color 14
title_start()
Armado Até os Dentes - 60 Pontos (Conquistada!)

You had an inventory full of all the weapons!

Did you have fun grinding up all that gold?

title_end()
"OK"
choice_end()
sp_active(&juggle, 0)
goto listc;
}

if (&result == 11)
{
choice_start()
set_y 240
set_title_color 14
title_start()
Caçador de Tesouros - 60 Pontos (Pendente)

Find all the powerups. That includes gold hearts and stat potions of all sorts.

title_end()
"OK"
choice_end()
goto listc;
}

if (&result == 12)
{
&juggle = create_sprite(370, 50, 0, 99, 24)
sp_que(&juggle, 1000)
choice_start()
set_y 240
set_title_color 14
title_start()
Caçador de Tesouros - 60 Pontos (Conquistada!)

You found all the powerups! Some of them were quite tricky, huh?

title_end()
"OK"
choice_end()
sp_active(&juggle, 0)
goto listc;
}

if (&result == 13)
{
choice_start()
set_y 240
set_title_color 14
title_start()
Vencedor Raquítico - 100 Pontos (Pendente)

Beat Seth while level 4 or lower.

Level 3 is possible, but probably only if you exploit the hardness error.

title_end()
"OK"
choice_end()
goto listc;
}

if (&result == 14)
{
&juggle = create_sprite(370, 50, 0, 99, 28)
sp_que(&juggle, 1000)
choice_start()
set_y 240
set_title_color 14
title_start()
Vencedor Raquítico - 100 Pontos (Conquistada!)

You defeated Seth while level 4 or lower!

You then gained at least three levels at once. What a rush.

title_end()
"OK"
choice_end()
sp_active(&juggle, 0)
goto listc;
}

if (&result == 15)
{
choice_start()
set_y 240
set_title_color 14
title_start()
Senhor do Grind - 100 Pontos (Pendente)

Attain Level 18.

Just keep murdering things. You'll get there.

title_end()
"OK"
choice_end()
goto listc;
}

if (&result == 16)
{
&juggle = create_sprite(370, 50, 0, 99, 25)
sp_que(&juggle, 1000)
choice_start()
set_y 240
set_title_color 14
title_start()
Senhor do Grind - 100 Pontos (Conquistada!)

You attained Level 18!

Are you proud of yourself?

title_end()
"OK"
choice_end()
sp_active(&juggle, 0)
goto listc;
}

//if (&result == 17)
//{
//choice_start()
//set_y 320
//set_title_color 14
//title_start()
//Lord of Dinkers - 200 Pontos (Pendente)

//Win without using an elixir or purchasing the bow lore, light sword or Hellfire.

//Not gender-specific. Female players can be Lord of Dinkers too, if they're crazy enough to want to.

//title_end()
//"OK"
//choice_end()
//goto listc;
//}

//if (&result == 18)
//{
//&juggle = create_sprite(370, 50, 0, 99, 26)
//sp_que(&juggle, 1000)
//choice_start()
//set_y 300
//set_title_color 14
//title_start()
//Lord of Dinkers - 200 Pontos (Pendente)

//You won without using an elixir or purchasing the bow lore, light sword or Hellfire.

//Easier than it sounds, huh?

//title_end()
//"OK"
//choice_end()
//sp_active(&juggle, 0)
//goto listc;
//}

if (&result == 17)
{
goto list;
}

return
}

//unlockable extras menu

void extra
{
choice_start()
title_start()
Unlockable Extras
title_end()
"150 Pontos - Music Select"
"300 Pontos - Colored Blood"
"450 Pontos - Dinksaber"
"600 Pontos - Respec System"
"800 Pontos - Secret Bonus"
"Fechar"
choice_end()

if (&result == 1)
{

	if (&cheevo < 150)
	{
	goto nope;
	}
music:
choice_start
set_y 140
title_start
Music Select
title_end
"Ave Maria (Terris)"
"Serenade (Stonebrook)"
"Reverie"
"Mendelssohn (Windermere)"
"Blue Danube"
"Lovin' (Parade)"
"Calbee's Dream (Bar)"
"Suite: Incomplete (Darklands)"
"In my dream (End of game)"
"winter...from? (GoodHeart Castle)"
"Dreaming Dwarf (Church)"
"End Boss"
"Battle"
"Midboss"
"Cave Exploration"
"Favorite (Koka Isle)"
"Wanderjam"
"Wander 3"
"Ir para Página 2"
"Exit"
choice_end

if (&result == 1)
{
playmidi("1.mid")
}

if (&result == 2)
{
playmidi("104.mid")
}

if (&result == 3)
{
playmidi("105.mid")
}

if (&result == 4)
{
playmidi("106.mid")
}

if (&result == 5)
{
playmidi("denube.mid")
}

if (&result == 6)
{
playmidi("lovin.mid")
}

if (&result == 7)
{
playmidi("5.mid")
}

if (&result == 8)
{
playmidi("7.mid")
}

if (&result == 9)
{
playmidi("11.mid")
}

if (&result == 10)
{
playmidi("12.mid")
}

if (&result == 11)
{
playmidi("13.mid")
}

if (&result == 12)
{
playmidi("18.mid")
}

if (&result == 13)
{
playmidi("4.mid")
}

if (&result == 14)
{
playmidi("9.mid")
}

if (&result == 15)
{
playmidi("10.mid")
}

if (&result == 16)
{
playmidi("16.mid")
}

if (&result == 17)
{
playmidi("100.mid")
}

if (&result == 18)
{
playmidi("101.mid")
}

if (&result == 19)
{
goto pageb;
}

return

pageb:
choice_start
set_y 140
title_start
Music Select Page 2
title_end
"Tavern 2 (Aunt's house)"
"Neighbor (SmileStein's)"
"Bully Theme"
"Wanderer (Martridge)"
"Title Screen"
"Intro"
"Fire"
"Love"
"Untitled"
"Lively (unused)"
"Return to Page 1"
"Exit"
choice_end

if (&result == 1)
{
playmidi("102.mid")
}

if (&result == 2)
{
playmidi("103.mid")
}

if (&result == 3)
{
playmidi("Bullythe.mid")
}

if (&result == 4)
{
playmidi("Wanderer.mid")
}

if (&result == 5)
{
playmidi("1003.mid")
}

if (&result == 6)
{
playmidi("dance.mid")
}

if (&result == 7)
{
playmidi("insper.mid")
}

if (&result == 8)
{
playmidi("love.mid")
}

if (&result == 9)
{
playmidi("2.mid")
}

if (&result == 10)
{
playmidi("lively.mid")
}

if (&result == 11)
{
goto music;
}
return
}

if (&result == 2)
{
//in case you've lost track, this is the Colored Blood option
//Colored blood by Simon Klaebe

//Check to see if they're on the title screen
&juggle = sp_brain(1, -1)

if (&juggle != 1)
{
	choice_start
	title_start
	Colored Blood
	
	This option is only available ingame.
	title_end
	"OK"
	choice_end
	return
}

	if (&cheevo < 300)
	{
	goto nope;
	}

choice_start
title_start
Select Blood Color
title_end
"Red (default)"
"Black"
"Blue"
"Green"
"White"
"Yellow"
choice_end

if (&result == 1)
{
//default red blood
//set var to remember blood color setting
&bloody = 0
init("load_sequence_now graphics\effects\spurt\spurt- 187 100 16 9 -8 -1 8 1")
init("load_sequence_now graphics\effects\spurt\sprtl- 188 100 50 20 -12 -2 12 2")
init("load_sequence_now graphics\effects\spurt\sprtr- 189 100 0 20 -5 -2 5 2")
}

if (&result == 2)
{
//Blackish blood
&bloody = 1
init("load_sequence_now graphics\spurts\blackish\bkspt- 187 100 16 9 -8 -1 8 1")
init("load_sequence_now graphics\spurts\blackish\bkspl- 188 100 50 20 -12 -2 12 2")
init("load_sequence_now graphics\spurts\blackish\bkspr- 189 100 0 20 -5 -2 5 2")
}

if (&result == 3)
{
//Blue blood (I say!)
&bloody = 2
init("load_sequence_now graphics\spurts\blue\blusp- 187 100 16 9 -8 -1 8 1")
init("load_sequence_now graphics\spurts\blue\blspl- 188 100 50 20 -12 -2 12 2")
init("load_sequence_now graphics\spurts\blue\blspr- 189 100 0 20 -5 -2 5 2")
}

if (&result == 4)
{
//Green blood
&bloody = 3
init("load_sequence_now graphics\spurts\green\gsprt- 187 100 16 9 -8 -1 8 1")
init("load_sequence_now graphics\spurts\green\gsptl- 188 100 50 20 -12 -2 12 2")
init("load_sequence_now graphics\spurts\green\gsptr- 189 100 0 20 -5 -2 5 2")
}

if (&result == 5)
{
//White Blood
&bloody = 4
init("load_sequence_now graphics\spurts\white\wsprt- 187 100 16 9 -8 -1 8 1")
init("load_sequence_now graphics\spurts\white\wsptl- 188 100 50 20 -12 -2 12 2")
init("load_sequence_now graphics\spurts\white\wsptr- 189 100 0 20 -5 -2 5 2")
}

if (&result == 6)
{
//Yellow blood
&bloody = 5
init("load_sequence_now graphics\spurts\yellow\ysprt- 912 100 16 9 -8 -1 8 1")
init("load_sequence_now graphics\spurts\yellow\ysptl- 913 100 50 20 -12 -2 12 2")
init("load_sequence_now graphics\spurts\yellow\ysptr- 914 100 0 20 -5 -2 5 2")
}
return
}

if (&result == 3)
{
//Dinksaber. This option doesn't actually do anything, you can buy the saber ingame
//when you have enough points


if (&cheevo < 450)
{
goto nope;
}

choice_start
set_y 240
set_title_color 14
title_start
Now that you have enough points, the Dinksaber may be purchased.

You'll find it in the same shop as the Light Sword.
title_end
"OK"
choice_end
return
}

if (&result == 4)
{
//Turn my fabulous respec option on

//Check to see if they're on the title screen
&juggle = sp_brain(1, -1)

if (&juggle != 1)
{
	choice_start
	title_start
	Colored Blood
	
	This option is only available ingame.
	title_end
	"OK"
	choice_end
	return
}

if (&cheevo < 600)
{
goto nope;
}

choice_start
set_y 240
title_start
Respec System

This feature allows you to reassign the attributes you've been assigning at level up.

You can do this once per level.
title_end

 (&respecon == 0) "Turn Respec System On"
 (&respecon == 1) "Turn Respec System Off"
 "Never Mind"
choice_end

if (&result == 1)
{
&respecon = 1
}

if (&result == 2)
{
&respecon = 0
}
}

if (&result == 5)
{
//info on super bonus

if (&cheevo < 800)
{
goto nope;
}

choice_start
set_y 240
set_title_color 14
title_start
Congrats on getting all the achievements!

Talk to the King after beating the game to see the secret bonus.
title_end
"OK"
choice_end

}

return
nope:
	choice_start
	title_start
	Sorry, you haven't got enough points for that.
	title_end
	"Whoops"
	choice_end
return
}

void secret
{

int &one = game_exist(48)
int &two = game_exist(49)

choice_start
title_start
Secret Achievements!
title_end
(&one == 1) "Seth Rules (Conquistada!)"
(&two == 1) "One Forty-Tree (Conquistada!)"
"Fechar"
choice_end

if (&result == 1)
{
&juggle = create_sprite(370, 50, 0, 99, 26)
sp_que(&juggle, 1000)
choice_start()
set_y 240
set_title_color 14
title_start()
Seth Rules - Secret Achievement (Conquistada!)

Look at you, you found an easter egg! Nice going.

title_end()
"OK"
choice_end()
sp_active(&juggle, 0)
}

if (&result == 2)
{
&juggle = create_sprite(370, 50, 0, 99, 27)
sp_que(&juggle, 1000)
choice_start()
set_y 240
set_title_color 14
title_start()
One Forty-Tree - Secret Achievement (Conquistada!)

I added a tree to screen 143 and made it accessible.

It really ties the screen together, don't you think?

title_end()
"OK"
choice_end()
sp_active(&juggle, 0)
}

}