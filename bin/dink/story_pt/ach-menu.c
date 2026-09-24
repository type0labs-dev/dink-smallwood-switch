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

Demonstre seu desprezo pelas tarefas da mamãe matando os porcos antes de alimentá-los.
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

Mandou bem matando aqueles porcos antes da comida.
Meio bizarro o Milder não ter percebido, né?

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

Mate o pato Quackers.

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

Você matou o pato Quackers! Logo depois que o coitado achou a Noz Dourada...

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

Assassine Chealse, a fofoqueira de Stonebrook.

Na real, eu só queria ver até onde vai sua falta de escrúpulos por uma conquista.

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

Pois é, você matou a Chealse.

Você faz qualquer coisa por 10 míseros pontos, hein? Interessante. Vou anotar no seu dossiê.

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

Abata aquele bicho-de-conta gigante a oeste do Castelo GoodHeart.

Você deveria fazer isso de qualquer jeito; tem uma megapoção te esperando.

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

O bicho-de-conta gigante já era! Pelo menos até renascer.

Mas ei, você sempre terá essa conquista pra provar que deu conta dele.

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

Resgate o homem daqueles 'cavaleiros' malignos perto de Stonebrook.

Ele pode até te recompensar, mas não vá se empolgando muito.

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

Você salvou o ricaço da floresta. Cuidado pra não gastar essa moedinha de ouro toda de uma vez só.

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

Salve a fazenda do Smilestein dos bichos-de-conta.

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

Você derrotou os monstros e salvou a lavoura!

Aquele bicho falante era uma piada pronta. Provavelmente você NUNCA mais vai ver ELE por aí.

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

Venda uma Noz Alknut.

Seu porco capitalista safado.

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

Você vendeu uma Noz Alknut. Grande coisa.

Fique tranquilo, o Karl com certeza tem preocupações maiores no momento. Estar morto, por exemplo.

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

Ajude a cometer um assalto.

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

Você ajudou num assalto.

Não foi lá grande sucesso, mas você se livrou da culpa. Isso sim é uma conquista!

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

Mate o George.

Olha... você tem livre arbítrio. Você não precisa fazer isso de verdade. O George não tá fazendo mal pra ninguém.

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

O George tá morto. Ele só queria ser seu amigo.

Agora sou cúmplice, não sou? Fui eu quem inventou a lista de conquistas. Meu Deus, que poder terrível.

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
(&ccrap == 0) "De Volta às Raízes (Pendente)"
(&ccrap == 1) "De Volta às Raízes (Conquistada!)"
(&dcrap == 0) "Violência Doméstica (Pendente)"
(&dcrap == 1) "Violência Doméstica (Conquistada!)"
(&ecrap == 0) "Andar Sobre as Águas (Pendente)"
(&ecrap == 1) "Andar Sobre as Águas (Conquistada!)"
(&fcrap == 0) "Ponta Solta (Pendente)"
(&fcrap == 1) "Ponta Solta (Conquistada!)"
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

Compre a Doutrina do Arco. Se conseguir encontrar onde vende.

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

Você aprendeu a Doutrina do Arco. Aquele ponto comercial não deve ser nada bom pros negócios.

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

Execute o plano dos Renegados massacrando geral no desfile de KernSin.

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

Você aniquilou os Renegados E o povo de KernSin.

Assim, todo mundo perde e só você ganha.

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
De Volta às Raízes - 10 Pontos (Pendente)

Retorne às suas origens camponesas alimentando um porco numa terra distante.

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
De Volta às Raízes - 10 Pontos (Conquistada!)

Você alimentou o porco das Terras Sombrias. Ele nem deu muita bola, mas sua mãe ficaria orgulhosa de qualquer forma.

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

Elimine o Jack. Só é difícil se você não souber como.

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

Jack bateu as botas. Ninguém ficou dando pulos de alegria, mas ao menos ele não vai mais bater na sua tia.

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

Descubra a ilha secreta de Koka.

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

Você encontrou a Ilha Koka. Divirta-se apostando tudo contra os patos.

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
Ponta Solta - 20 Pontos (Pendente)

Encontre o mago no castelo secreto de gelo.

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
Ponta Solta - 20 Pontos (Conquistada!)

O 'Mago do Gelo' tinha umas coisas bem curiosas pra falar.
Pena que você nunca vai saber como essa trama se desenrola.

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

Supere seus traumas. Derrote o lendário porco das Terras Sombrias.

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

Você aniquilou o porco cascudo apelão!

Belíssimo trabalho. Eu diria que sua atuação foi simplesmente 'radiante'.

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

Atire uma bola de fogo numa árvore. Falhe em queimá-la. Seja ridicularizado pelo jogo.

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

Maldita árvore indestrutível.

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

Tire proveito do lendário bug de colisão na água. Você sabe qual é. Se não sabe, pergunte por aí.

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

Você pisou no grande desconhecido além do mapa. Tome cuidado por aí.

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

Derrote Seth, o Ancião.

Você ganha uma conquista de graça só por zerar o jogo! Não sou um amor de pessoa?

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

Você derrotou Seth, o criador inserido no próprio jogo.

Te poupei daquelas outras conquistas inúteis de 'progresso'. De nada.

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

Derrote todos os inimigos do jogo pelo menos uma vez. Não um de cada tipo: literalmente TODOS.

Se deixar renascer, não conta duas vezes.

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

Você exterminou todos os monstros! Caramba, mandou muito bem!

Se não fosse a geração espontânea de inimigos, estariam extintos!

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

Queime todas as árvores do reino.

Você sempre quis fazer isso mesmo — agora tem uma desculpa oficial.

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

Você queimou todas as árvores incendiáveis do mapa!

Nem mesmo o truque delas serem duas árvores em telas diferentes te impediu. Olha que orgulho.

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

Derrote Seth usando apenas os próprios punhos.

E nada de Botas de Velocidade. Eu já previa seu truque, espertinho(a).

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

Você encheu o Seth de porrada até a morte. Impressionante!

Quando eu era moleque, achava que precisava de arma apelona. Você calou minha boca.

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

Tenha todas as armas do jogo no inventário ao mesmo tempo.

Sim, todas de uma vez. Espaço você tem de sobra.

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

Inventário lotado com todas as armas do reino!

Curtiu ficar farmando todo aquele ouro?

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

Encontre todos os itens de melhoria. Isso inclui Corações Dourados e todas as poções de atributo.

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

Você achou todos os itens de atributos! Alguns estavam bem escondidos, fala a verdade?

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

Vença o Seth estando no nível 4 ou inferior.

Nível 3 até é possível, mas provavelmente só abusando de bugs no mapa.

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

Você derrotou o Seth no nível 4 ou menos!

E subiu uns três níveis de uma lapada só na sequência. Que adrenalina!

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

Atinja o Nível 18.

Continue assassinando criaturas sem parar. Uma hora você chega lá.

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

Você alcançou o Nível 18!

Tá orgulhoso de você mesmo agora?

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
Extras Desbloqueáveis
title_end()
"150 Pontos - Seleção de Músicas"
"300 Pontos - Sangue Colorido"
"450 Pontos - Dinksaber (Sabre de Luz)"
"600 Pontos - Redistribuir Atributos"
"800 Pontos - Bônus Secreto"
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
Seth é Demais - Conquista Secreta (Conquistada!)

Olha só você, achou um easter egg secreto! Mandou muito bem.

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
Árvore 143 - Conquista Secreta (Conquistada!)

Eu adicionei uma árvore na tela 143 e deixei ela acessível.

Ela realmente deu um charme especial pro cenário, não acha?

title_end()
"OK"
choice_end()
sp_active(&juggle, 0)
}

}