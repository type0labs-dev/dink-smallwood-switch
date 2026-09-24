import re

html_path = "complete_edition.html"
html = open(html_path, "r", encoding="utf-8").read()

# We will add a dedicated new Tab for "🎭 Assets de Personagens & Criaturas"
# and update "🐉 Monstros, Bestiário & Chefes" to include Spiders, Pillbug variations, Robots, Cows, and Marine beasts!

# Update Nav buttons
nav_old = '<button class="nav-btn" onclick="showTab(\'bestiario-chefes\')">🐉 Monstros, Bestiário & Chefes</button>'
nav_new = '<button class="nav-btn" onclick="showTab(\'bestiario-chefes\')">🐉 Monstros, Bestiário & Criaturas</button>\n        <button class="nav-btn" onclick="showTab(\'personagens-assets\')">🎭 Personagens & Sprites do Dink</button>'

html = html.replace(nav_old, nav_new)

# Now replace the content of tab "bestiario-chefes" with the full detailed classification:
bestiario_section = """
        <!-- TAB 3: BESTIÁRIO, CRIATURAS & CHEFES -->
        <div id="bestiario-chefes" class="tab-pane">
            <div class="section-header">
                <h2>Bestiário Completo: Aranhas, Robôs, Insetos, Fauna & Chefes</h2>
            </div>
            <p style="color: var(--text-muted); margin-bottom: 25px;">
                Mapeamento das criaturas criadas pela comunidade: desde as icônicas <b>Aranhas Gigantes</b> e <b>Robôs Mecanóides</b> até as <b>Mutações de Piolhos</b> e a <b>Fauna Rural (Vacas, Tubarões e Coelhos)</b>.
            </p>

            <div class="filter-bar">
                <span class="filter-chip active" onclick="filterCreatures('all')">Todos</span>
                <span class="filter-chip" onclick="filterCreatures('aracnideos')">🕷️ Aranhas & Insetos</span>
                <span class="filter-chip" onclick="filterCreatures('robos')">🤖 Robôs & Mecanóides</span>
                <span class="filter-chip" onclick="filterCreatures('piolhos')">🐛 Mutações de Piolhos</span>
                <span class="filter-chip" onclick="filterCreatures('fauna')">🐄 Fauna & Animais (Vacas)</span>
                <span class="filter-chip" onclick="filterCreatures('marinhos')">🌊 Feras Marinhas</span>
                <span class="filter-chip" onclick="filterCreatures('chefes')">👑 Grandes Chefes</span>
            </div>

            <div class="card-grid" id="creatures-grid">
                <!-- ARANHAS -->
                <div class="card creature-card" data-cat="aracnideos">
                    <div class="card-tag tag-combat">Aracnídeo</div>
                    <div class="card-title">🕷️ Aranha Vermelha Gigante (Red Spider)</div>
                    <div class="card-origin">Origem: Once a Hero (OAH) / Red Spider Pack (Reiner)</div>
                    <div class="card-desc">
                        Aranhas colossais com animações completas de 8 direções, ataque em salto rápido e teia que prende o Dink no chão temporariamente. Causam envenenamento por mordida.
                    </div>
                    <div class="card-footer"><span>Comportamento: Salto + Teia</span><span>Habitat: Cavernas & Criptas</span></div>
                </div>

                <div class="card creature-card" data-cat="aracnideos">
                    <div class="card-tag tag-combat">Inseto Voador</div>
                    <div class="card-title">🐝 Vespas Gigantes Assassinas (Wasp)</div>
                    <div class="card-origin">Origem: Wasp Enemy Pack</div>
                    <div class="card-desc">
                        Insetos alados de voo errático e rápido; atacam em mergulho veloz e ferroam repetidamente aplicando veneno de perda gradual de vida.
                    </div>
                    <div class="card-footer"><span>Comportamento: Voo Errático</span><span>Habitat: Florestas Densas</span></div>
                </div>

                <!-- ROBÔS -->
                <div class="card creature-card" data-cat="robos">
                    <div class="card-tag tag-combat">Mecanóide</div>
                    <div class="card-title">🤖 Necro-Bot (Esqueleto Mecânico a Vapor)</div>
                    <div class="card-origin">Origem: Pilgrim's Quest & Cast Awakening</div>
                    <div class="card-desc">
                        Andróides blindados movidos a vapor e engrenagens criados por magos hereges. Disparam projéteis de choque, possuem armadura que ricocheteia flechas e explodem ao serem destruídos.
                    </div>
                    <div class="card-footer"><span>Comportamento: Disparo + Explosão</span><span>Fraqueza: Magia de Água</span></div>
                </div>

                <div class="card creature-card" data-cat="robos">
                    <div class="card-tag tag-combat">Mecanóide</div>
                    <div class="card-title">🐸 Frog-Bot (Rã Guerreira Mecanizada)</div>
                    <div class="card-origin">Origem: Pilgrim's Quest (Simon Klaebe)</div>
                    <div class="card-desc">
                        Rãs cibernéticas equipadas com serras circulares e canhões de alta pressão. Pulam rapidamente evitando ataques do jogador e exigem timing de bloqueio com escudo.
                    </div>
                    <div class="card-footer"><span>Comportamento: Pulo Tático</span><span>Mecânica: Desarme com Skard</span></div>
                </div>

                <div class="card creature-card" data-cat="robos">
                    <div class="card-tag tag-combat">Mecanóide</div>
                    <div class="card-title">🥷 Ninja-Bot & Cabeça Voadora</div>
                    <div class="card-origin">Origem: Ninja-Bot Pack / Flying Head</div>
                    <div class="card-desc">
                        Robôs assassinos com katanas que arremessam shurikens; ao serem derrotados, a cabeça se desprende e continua voando atacando como kamikaze!
                    </div>
                    <div class="card-footer"><span>Comportamento: 2 Fases (Corpo/Cabeça)</span><span>Dificuldade: Alta</span></div>
                </div>

                <!-- PIOLHOS -->
                <div class="card creature-card" data-cat="piolhos">
                    <div class="card-tag tag-combat">Mutação</div>
                    <div class="card-title">🐛 Piolho Esfolado (Flayed Pillbug)</div>
                    <div class="card-origin">Origem: Things from my Backyard / One Screen DMOD</div>
                    <div class="card-desc">
                        Variação aterrorizante do piolho clássico sem carapaça protetora; muito mais rápido e agressivo, solta gosma ácida no chão que causa dano se pisada.
                    </div>
                    <div class="card-footer"><span>Comportamento: Rápido + Ácido</span><span>Habitat: Pântanos</span></div>
                </div>

                <div class="card creature-card" data-cat="piolhos">
                    <div class="card-tag tag-combat">Mutação</div>
                    <div class="card-title">🛡️ Piolho Espinhoso Blindado (Spiked Pillbug)</div>
                    <div class="card-origin">Origem: One Screen DMOD Compilation</div>
                    <div class="card-desc">
                        Piolho com carapaça reforçada de espinhos negros. Espinhos causam dano por reflexão (o jogador toma dano se acertar com soco desarmado). Exige espada longa ou martelo.
                    </div>
                    <div class="card-footer"><span>Comportamento: Reflexão de Dano</span><span>Resistência: Extrema</span></div>
                </div>

                <!-- FAUNA & VACAS -->
                <div class="card creature-card" data-cat="fauna">
                    <div class="card-tag tag-world">Fauna Rural</div>
                    <div class="card-title">🐄 Vacas Leiteiras & "Tombamento de Vacas"</div>
                    <div class="card-origin">Origem: Cast Awakening: Initiation (Dan Walma)</div>
                    <div class="card-desc">
                        Vacas pacíficas com animação de pastar e mugir. No mod <i>Cast Awakening</i>, incluem a famosa mecânica humorística de <i>'Cow Tipping'</i> (empurrar e tombar a vaca escondido do fazendeiro na calada da noite!).
                    </div>
                    <div class="card-footer"><span>Interação: Empurrão / Humor</span><span>Local: Fazendas do Reino</span></div>
                </div>

                <div class="card creature-card" data-cat="fauna">
                    <div class="card-tag tag-world">Fauna Selvagem</div>
                    <div class="card-title">🦈 Tubarões Saltadores (Jumping Sharks)</div>
                    <div class="card-origin">Origem: Dink's 1st Mod (Animals Pack)</div>
                    <div class="card-desc">
                        Animação completa de tubarões que emergem da água em salto mortal para abocanhar Dink caso ele chegue perto demais de píers ou nade sem barco.
                    </div>
                    <div class="card-footer"><span>Comportamento: Emboscada Aquática</span><span>Habitat: Costas e Rios</span></div>
                </div>

                <div class="card creature-card" data-cat="fauna">
                    <div class="card-tag tag-world">Fauna Selvagem</div>
                    <div class="card-title">🐰 Coelhos Assassinos (Killer Rabbits)</div>
                    <div class="card-origin">Origem: Pilgrim's Quest (rabbatck)</div>
                    <div class="card-desc">
                        Parecem coelhinhos brancos fofos inofensivos... até Dink se aproximar! Eles se transformam em feras vorazes com dentes afiados que pulam no pescoço do herói (homenagem a <i>Monty Python</i>).
                    </div>
                    <div class="card-footer"><span>Comportamento: Falso Inofensivo</span><span>Perigo: Surpresa</span></div>
                </div>

                <!-- FERAS MARINHAS -->
                <div class="card creature-card" data-cat="marinhos">
                    <div class="card-tag tag-combat">Monstro Marinho</div>
                    <div class="card-title">🐍 O Basilisco dos Mares (Basilik)</div>
                    <div class="card-origin">Origem: Pilgrim's Quest</div>
                    <div class="card-desc">
                        Serpente colossal subaquática com centenas de escamas. Guarda o santuário das águas e destrói barcos. Possui inteligência ancestral e dialoga com o jogador se ele tiver Honra alta.
                    </div>
                    <div class="card-footer"><span>Comportamento: Chefe / Guardião</span><span>Requisito: Honra > 12</span></div>
                </div>

                <div class="card creature-card" data-cat="marinhos">
                    <div class="card-tag tag-combat">Monstro Marinho</div>
                    <div class="card-title">🐙 Polvo Kraken das Profundezas</div>
                    <div class="card-origin">Origem: Pilgrim's Quest (octoswim / octoattk)</div>
                    <div class="card-desc">
                        Monstro de múltiplos tentáculos que emergem do oceano tentando afundar a embarcação de Dink durante a navegação. Exige cortar os tentáculos com espada ou magia de fogo.
                    </div>
                    <div class="card-footer"><span>Comportamento: Tentáculos Múltiplos</span><span>Mecânica: Combate Náutico</span></div>
                </div>

                <!-- GRANDES CHEFES -->
                <div class="card creature-card" data-cat="chefes">
                    <div class="card-tag tag-story">Grande Chefe</div>
                    <div class="card-title">👑 Decretius (O Mago Herege)</div>
                    <div class="card-origin">Origem: Pilgrim's Quest (End World)</div>
                    <div class="card-desc">
                        Conjurador supremo que comanda tempestades de pedras, teleporta-se entre plataformas e invoca Necro-bots. A batalha exige alternar entre escudo e magia de água.
                    </div>
                    <div class="card-footer"><span>Batalha: 3 Fases com Arena</span><span>Duração: Épica</span></div>
                </div>

                <div class="card creature-card" data-cat="chefes">
                    <div class="card-tag tag-story">Grande Chefe</div>
                    <div class="card-title">❄️ A Rainha do Gelo (Ice Queen)</div>
                    <div class="card-origin">Origem: Pilgrim's Quest (icequeen)</div>
                    <div class="card-desc">
                        Soberana das montanhas congeladas; congela o chão fazendo Dink escorregar e dispara lanças de gelo teleguiadas que perfuram escudos comuns.
                    </div>
                    <div class="card-footer"><span>Batalha: Controle de Terreno</span><span>Fraqueza: Bola de Fogo Tripla</span></div>
                </div>
            </div>
        </div>

        <!-- TAB NOVO: PERSONAGENS & ASSETS -->
        <div id="personagens-assets" class="tab-pane">
            <div class="section-header">
                <h2>Assets de Personagens: Novos Protagonistas & Sprites do Dink</h2>
            </div>
            <p style="color: var(--text-muted); margin-bottom: 25px;">
                A comunidade não se limitou ao visual básico do camponês de 1997: criaram animações completas de equipamentos no corpo do Dink, novas ações físicas e até novos protagonistas jogáveis.
            </p>

            <div class="card-grid">
                <div class="card">
                    <div class="card-tag tag-combat">Visual do Herói</div>
                    <div class="card-title">🛡️ Dink com Escudo (Off-Hand Dink)</div>
                    <div class="card-origin">Origem: Off-Handed Shield Pack (424 Sprites)</div>
                    <div class="card-desc">
                        Conjunto visual monumental que desenha o escudo (Kiteshield ou Buckler) no braço esquerdo do Dink em todas as direções de caminhada, soco, ataque de espada e reação de golpe.
                    </div>
                    <div class="card-footer"><span>Sprites: 424 frames BMP</span><span>Integração: Pronta</span></div>
                </div>

                <div class="card">
                    <div class="card-tag tag-qol">Ação Física</div>
                    <div class="card-title">🔦 Dink com Lanterna / Tocha Dinâmica</div>
                    <div class="card-origin">Origem: Dink Lantern Graphics</div>
                    <div class="card-desc">
                        Dink segura uma lanterna acesa em masmorras e florestas escuras. Cria um raio de iluminação 360° dinâmico ao redor do personagem, transformando cavernas em experiências atmosféricas.
                    </div>
                    <div class="card-footer"><span>Mecânica: Iluminação Noturna</span><span>Uso: Cavernas & Noite</span></div>
                </div>

                <div class="card">
                    <div class="card-tag tag-qol">Ação Física</div>
                    <div class="card-title">⛏️ Dink com Pá (Escavação de Tesouros)</div>
                    <div class="card-origin">Origem: Dink with Shovel Pack</div>
                    <div class="card-desc">
                        Animação completa de Dink cravando uma pá na terra e cavando buracos. Permite criar mecânicas de caça ao tesouro com mapas piratas e desenterrar segredos enterrados.
                    </div>
                    <div class="card-footer"><span>Ação: Cavar / Interação</span><span>Utilidade: Quests de Tesouro</span></div>
                </div>

                <div class="card">
                    <div class="card-tag tag-story">Alter-Ego</div>
                    <div class="card-title">🌑 Dink Sombrio (Dark Dink / Corrupted)</div>
                    <div class="card-origin">Origem: Dark Dink Pack</div>
                    <div class="card-desc">
                        Versão sombria e corrompida do herói: roupas pretas, olhos vermelhos brilhantes e fumaça escura. Excelente para sequências de pesadelo, possessão pelo Cast ou clones malignos.
                    </div>
                    <div class="card-footer"><span>Visual: Sombrio / Vilão</span><span>Papel: Clone / Pesadelo</span></div>
                </div>

                <div class="card">
                    <div class="card-tag tag-story">Novo Protagonista</div>
                    <div class="card-title">⚔️ Alex (Guerreiro Completo)</div>
                    <div class="card-origin">Origem: Alex (New Character) Pack (Iplaydink)</div>
                    <div class="card-desc">
                        Um protagonista alternativo totalmente novo criado em 3D pré-renderizado, com conjunto completo de caminhada, golpes, morte e uso de armas.
                    </div>
                    <div class="card-footer"><span>Uso: Seleção de Personagem</span><span>Estilo: Herói Alternativo</span></div>
                </div>

                <div class="card">
                    <div class="card-tag tag-story">Protagonista Canônica</div>
                    <div class="card-title">💖 Lyna (A Donzela de Stonebrook)</div>
                    <div class="card-origin">Origem: Lyna's Story (Paul Pliska)</div>
                    <div class="card-desc">
                        Sprites completos da garota Lyna caminhando, atacando e interagindo. Permite campanhas ou prólogos jogados 100% sob a ótica feminina da vila.
                    </div>
                    <div class="card-footer"><span>Uso: Campanha Dedicada</span><span>Nota: 9.6 na Comunidade</span></div>
                </div>

                <div class="card">
                    <div class="card-tag tag-world">NPCs da Comunidade</div>
                    <div class="card-title">🍻 População Expandida (Fatties, Bar & Mulheres)</div>
                    <div class="card-origin">Origem: MsDink's Graphics Pack 3 & Goblin Female Pack</div>
                    <div class="card-desc">
                        Variedade massiva de novos NPCs: homens corpulentos para tavernas, mulheres camponesas com vestidos de época, goblins fêmeas e nobres em tronos reais.
                    </div>
                    <div class="card-footer"><span>Variedade: Aldeões & Cidades</span><span>Imersão: Cidades Vivas</span></div>
                </div>

                <div class="card">
                    <div class="card-tag tag-qol">Acrobacia</div>
                    <div class="card-title">🦘 Dink Pula (Dink Jumps Animation)</div>
                    <div class="card-origin">Origem: Dink Jumps Pack</div>
                    <div class="card-desc">
                        Animação de salto vertical e horizontal do herói, permitindo transpor pequenos vãos, riachos e obstáculos que antes bloqueavam o caminho no mapa.
                    </div>
                    <div class="card-footer"><span>Mecânica: Salto / Puzzles</span><span>Uso: Plataforma Leve</span></div>
                </div>
            </div>
        </div>
"""

# Replace the old bestiario section with the new bestiario + personagens section
pattern = r'<!-- TAB 3: BESTIÁRIO & CHEFES -->.*?(?=<!-- TAB 4: ARSENAL & MAGIAS -->)'
html = re.sub(pattern, bestiario_section, html, flags=re.S)

# Add Javascript for creature filtering
js_filter = """
        function filterCreatures(category) {
            document.querySelectorAll('.filter-chip').forEach(el => el.classList.remove('active'));
            event.target.classList.add('active');

            const cards = document.querySelectorAll('.creature-card');
            cards.forEach(card => {
                if (category === 'all' || card.getAttribute('data-cat') === category) {
                    card.style.display = 'flex';
                } else {
                    card.style.display = 'none';
                }
            });
        }
"""

html = html.replace('function showTab(tabId) {', js_filter + '\n        function showTab(tabId) {')

with open(html_path, "w", encoding="utf-8") as f:
    f.write(html)

print("Dashboard HTML atualizado com sucesso em:", html_path)
