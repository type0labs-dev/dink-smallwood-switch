import json, os

html_path = "complete_edition.html"

html_content = """<!DOCTYPE html>
<html lang="pt-BR">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Dink Smallwood HD: Complete Edition — Planejamento & Arquitetura</title>
    <style>
        :root {
            --bg-main: #0e1117;
            --bg-card: #161b22;
            --bg-card-hover: #1f2632;
            --gold: #d4af37;
            --gold-bright: #ffd700;
            --crimson: #990000;
            --crimson-light: #e63946;
            --blue: #457b9d;
            --green: #2a9d8f;
            --purple: #7209b7;
            --text-main: #e0e6ed;
            --text-muted: #8b949e;
            --border: #30363d;
            --font-display: 'Georgia', 'Cinzel', serif;
        }

        * { box-sizing: border-box; margin: 0; padding: 0; }

        body {
            background-color: var(--bg-main);
            color: var(--text-main);
            font-family: -apple-system, BlinkMacSystemFont, "Segoe UI", Roboto, Helvetica, Arial, sans-serif;
            line-height: 1.6;
            padding-bottom: 60px;
        }

        header {
            background: linear-gradient(180deg, #1c0f0f 0%, #0e1117 100%);
            border-bottom: 2px solid var(--gold);
            padding: 40px 20px 25px;
            text-align: center;
            position: relative;
        }

        .header-badge {
            display: inline-block;
            background: var(--crimson);
            color: #fff;
            padding: 4px 14px;
            border-radius: 20px;
            font-size: 0.85rem;
            font-weight: bold;
            letter-spacing: 1px;
            text-transform: uppercase;
            margin-bottom: 15px;
            border: 1px solid rgba(255,255,255,0.2);
        }

        h1 {
            font-family: var(--font-display);
            color: var(--gold-bright);
            font-size: 2.6rem;
            text-shadow: 0 2px 10px rgba(0,0,0,0.8);
            margin-bottom: 10px;
        }

        .subtitle {
            color: var(--text-muted);
            max-width: 800px;
            margin: 0 auto;
            font-size: 1.1rem;
        }

        /* Nav Tabs */
        nav {
            display: flex;
            justify-content: center;
            gap: 10px;
            background: #12161f;
            padding: 12px;
            border-bottom: 1px solid var(--border);
            position: sticky;
            top: 0;
            z-index: 100;
            backdrop-filter: blur(8px);
            flex-wrap: wrap;
        }

        .nav-btn {
            background: transparent;
            border: 1px solid var(--border);
            color: var(--text-muted);
            padding: 8px 18px;
            border-radius: 6px;
            cursor: pointer;
            font-weight: 600;
            font-size: 0.95rem;
            transition: all 0.2s ease;
        }

        .nav-btn:hover {
            color: var(--text-main);
            border-color: var(--gold);
            background: rgba(212, 175, 55, 0.05);
        }

        .nav-btn.active {
            background: var(--gold);
            color: #000;
            border-color: var(--gold);
            box-shadow: 0 0 15px rgba(212, 175, 55, 0.4);
        }

        /* Container */
        .container {
            max-width: 1280px;
            margin: 30px auto;
            padding: 0 20px;
        }

        /* Tab Contents */
        .tab-pane {
            display: none;
            animation: fadeIn 0.3s ease forwards;
        }

        .tab-pane.active {
            display: block;
        }

        @keyframes fadeIn {
            from { opacity: 0; transform: translateY(8px); }
            to { opacity: 1; transform: translateY(0); }
        }

        /* Hero Highlights / Stat Cards */
        .stat-grid {
            display: grid;
            grid-template-columns: repeat(auto-fit, minmax(220px, 1fr));
            gap: 15px;
            margin-bottom: 30px;
        }

        .stat-card {
            background: var(--bg-card);
            border: 1px solid var(--border);
            border-radius: 8px;
            padding: 20px;
            text-align: center;
            border-top: 3px solid var(--gold);
        }

        .stat-number {
            font-size: 2.2rem;
            font-weight: bold;
            color: var(--gold-bright);
            font-family: var(--font-display);
        }

        .stat-label {
            color: var(--text-muted);
            font-size: 0.9rem;
            margin-top: 5px;
            text-transform: uppercase;
            letter-spacing: 0.5px;
        }

        /* Section Titles */
        .section-header {
            margin-bottom: 25px;
            border-bottom: 1px solid var(--border);
            padding-bottom: 10px;
            display: flex;
            align-items: center;
            justify-content: space-between;
        }

        .section-header h2 {
            font-family: var(--font-display);
            color: var(--gold-bright);
            font-size: 1.8rem;
        }

        /* Cards Grid */
        .card-grid {
            display: grid;
            grid-template-columns: repeat(auto-fit, minmax(350px, 1fr));
            gap: 20px;
            margin-bottom: 30px;
        }

        .card {
            background: var(--bg-card);
            border: 1px solid var(--border);
            border-radius: 10px;
            padding: 22px;
            transition: transform 0.2s ease, border-color 0.2s ease;
            position: relative;
            display: flex;
            flex-direction: column;
        }

        .card:hover {
            transform: translateY(-4px);
            border-color: var(--gold);
            background: var(--bg-card-hover);
        }

        .card-tag {
            align-self: flex-start;
            padding: 3px 10px;
            border-radius: 4px;
            font-size: 0.75rem;
            font-weight: bold;
            text-transform: uppercase;
            margin-bottom: 12px;
        }

        .tag-qol { background: rgba(42, 157, 143, 0.2); color: #2a9d8f; border: 1px solid #2a9d8f; }
        .tag-combat { background: rgba(230, 57, 70, 0.2); color: #e63946; border: 1px solid #e63946; }
        .tag-story { background: rgba(212, 175, 55, 0.2); color: #d4af37; border: 1px solid #d4af37; }
        .tag-magic { background: rgba(114, 9, 183, 0.2); color: #b5179e; border: 1px solid #b5179e; }
        .tag-world { background: rgba(69, 123, 157, 0.2); color: #457b9d; border: 1px solid #457b9d; }

        .card-title {
            font-size: 1.3rem;
            font-weight: bold;
            color: #fff;
            margin-bottom: 8px;
            font-family: var(--font-display);
        }

        .card-origin {
            font-size: 0.85rem;
            color: var(--gold);
            margin-bottom: 12px;
        }

        .card-desc {
            color: var(--text-main);
            font-size: 0.95rem;
            flex-grow: 1;
            margin-bottom: 15px;
        }

        .card-footer {
            border-top: 1px solid rgba(255,255,255,0.08);
            padding-top: 12px;
            font-size: 0.85rem;
            color: var(--text-muted);
            display: flex;
            justify-content: space-between;
        }

        /* Flow Architecture Diagram */
        .flow-diagram {
            background: #11141c;
            border: 1px solid var(--border);
            border-radius: 12px;
            padding: 30px;
            margin-bottom: 30px;
        }

        .flow-node {
            background: var(--bg-card);
            border: 2px solid var(--gold);
            border-radius: 8px;
            padding: 15px 25px;
            text-align: center;
            font-weight: bold;
            color: var(--gold-bright);
            box-shadow: 0 4px 15px rgba(0,0,0,0.5);
        }

        /* Interactive Filters */
        .filter-bar {
            display: flex;
            gap: 10px;
            margin-bottom: 20px;
            flex-wrap: wrap;
        }

        .filter-chip {
            background: var(--bg-card);
            border: 1px solid var(--border);
            color: var(--text-muted);
            padding: 5px 12px;
            border-radius: 20px;
            cursor: pointer;
            font-size: 0.85rem;
        }

        .filter-chip.active {
            background: var(--gold);
            color: #000;
            font-weight: bold;
            border-color: var(--gold);
        }

        /* Tables */
        table {
            width: 100%;
            border-collapse: collapse;
            background: var(--bg-card);
            border-radius: 8px;
            overflow: hidden;
            border: 1px solid var(--border);
            margin-bottom: 25px;
        }

        th, td {
            padding: 14px 18px;
            text-align: left;
            border-bottom: 1px solid var(--border);
        }

        th {
            background: #121720;
            color: var(--gold);
            font-weight: 600;
            text-transform: uppercase;
            font-size: 0.85rem;
            letter-spacing: 0.5px;
        }

        tr:hover {
            background: var(--bg-card-hover);
        }

        /* Checklist Roadmap */
        .roadmap-timeline {
            position: relative;
            padding-left: 30px;
            border-left: 3px solid var(--gold);
            margin: 20px 0;
        }

        .timeline-item {
            position: relative;
            margin-bottom: 35px;
        }

        .timeline-dot {
            position: absolute;
            left: -38px;
            top: 4px;
            width: 16px;
            height: 16px;
            border-radius: 50%;
            background: var(--gold-bright);
            border: 3px solid var(--bg-main);
            box-shadow: 0 0 10px var(--gold);
        }

        .timeline-title {
            font-size: 1.25rem;
            font-weight: bold;
            color: var(--gold-bright);
            font-family: var(--font-display);
        }

        .timeline-body {
            background: var(--bg-card);
            border: 1px solid var(--border);
            border-radius: 8px;
            padding: 15px;
            margin-top: 10px;
        }
    </style>
</head>
<body>

    <header>
        <div class="header-badge">Nintendo Switch & Personal Archive</div>
        <h1>Dink Smallwood HD: Complete Edition</h1>
        <p class="subtitle">Planejamento visual e decomposição de 25 anos de desenvolvimento da comunidade (393 DMODs, 360 ferramentas e expansões) integrados em uma obra definitiva.</p>
    </header>

    <nav>
        <button class="nav-btn active" onclick="showTab('visao-geral')">🏛️ Visão Geral & Arquitetura</button>
        <button class="nav-btn" onclick="showTab('mecanicas-qol')">⚙️ Mecânicas & Sistemas</button>
        <button class="nav-btn" onclick="showTab('bestiario-chefes')">🐉 Monstros, Bestiário & Chefes</button>
        <button class="nav-btn" onclick="showTab('arsenal-magias')">🗡️ Armas, Magias & Itens</button>
        <button class="nav-btn" onclick="showTab('biomas-mapas')">🗺️ Mapas, Biomas & Náutica</button>
        <button class="nav-btn" onclick="showTab('dlcs-campanhas')">👑 Grandes DLCs & Histórias</button>
        <button class="nav-btn" onclick="showTab('roadmap')">🚀 Roadmap de Implementação</button>
    </nav>

    <div class="container">

        <!-- TAB 1: VISÃO GERAL -->
        <div id="visao-geral" class="tab-pane active">
            <div class="stat-grid">
                <div class="stat-card">
                    <div class="stat-number">393</div>
                    <div class="stat-label">DMODs Analisados</div>
                </div>
                <div class="stat-card">
                    <div class="stat-number">25 Anos</div>
                    <div class="stat-label">Criações da Comunidade</div>
                </div>
                <div class="stat-card">
                    <div class="stat-number">6 Pilares</div>
                    <div class="stat-label">Sistemas Reestruturados</div>
                </div>
                <div class="stat-card">
                    <div class="stat-number">100% PT-BR</div>
                    <div class="stat-label">Dublagem Clássica BR</div>
                </div>
            </div>

            <div class="section-header">
                <h2>Como Conectar a Campanha Base às Expansões</h2>
            </div>

            <div class="flow-diagram">
                <div style="display: flex; justify-content: space-around; align-items: center; flex-wrap: wrap; gap: 20px;">
                    <div class="flow-node" style="border-color: #2a9d8f;">
                        🎮 Menu Principal<br><small>Seleção de Idioma PT-BR/EN</small>
                    </div>
                    <div style="font-size: 2rem; color: var(--gold);">➔</div>
                    <div class="flow-node" style="border-color: var(--gold);">
                        📖 Campanha Base com QoL<br><small>Quest Log + Itens Empilháveis + Escudo</small>
                    </div>
                    <div style="font-size: 2rem; color: var(--gold);">➔</div>
                    <div class="flow-node" style="border-color: var(--crimson-light);">
                        ⛵ O Barqueiro de KernSin<br><small>Viagem In-Game para Outras Terras</small>
                    </div>
                    <div style="font-size: 2rem; color: var(--gold);">➔</div>
                    <div class="flow-node" style="border-color: var(--purple);">
                        🏆 Expansões & DLCs<br><small>Pilgrim's Quest / Cast Awakening</small>
                    </div>
                </div>
                <p style="margin-top: 25px; text-align: center; color: var(--text-muted); font-size: 0.95rem;">
                    O jogador não precisa mais navegar por telas de arquivos confusas: o jogo pode ser jogado como uma jornada contínua e rica, com o novo menu moderno de DLCs atuando como seletor de campanhas!
                </p>
            </div>

            <div class="section-header">
                <h2>Os 3 Pilares da Complete Edition</h2>
            </div>

            <div class="card-grid">
                <div class="card">
                    <div class="card-tag tag-qol">Pilar 1: Modernização</div>
                    <div class="card-title">Campanha Base Enriquecida</div>
                    <div class="card-desc">
                        A campanha clássica de 1997 recebe injeção de qualidade de vida: Diário de Quests para não se perder, itens empilháveis no inventário, barra de vida nos inimigos e dublagem BR personalizada.
                    </div>
                    <div class="card-footer">
                        <span>Origem: Questlog Edition & DSIP</span>
                        <span>Status: Pronto para fusão</span>
                    </div>
                </div>

                <div class="card">
                    <div class="card-tag tag-combat">Pilar 2: Combate & Arsenal</div>
                    <div class="card-title">Mão Secundária & 4 Novos Atributos</div>
                    <div class="card-desc">
                        Dink passa a poder equipar escudos com bloqueio ativo (424 sprites novos), além de evoluir em Honra (moralidade), Agilidade, Malandragem e Sorte.
                    </div>
                    <div class="card-footer">
                        <span>Origem: Off-Handed Shield & Pilgrim's Quest</span>
                        <span>Status: Em mapeamento</span>
                    </div>
                </div>

                <div class="card">
                    <div class="card-tag tag-story">Pilar 3: Universo Conectado</div>
                    <div class="card-title">Hub de DLCs & Viagens Marítimas</div>
                    <div class="card-desc">
                        As maiores expansões já feitas (Pilgrim's Quest, Cast Awakening, Stone of Balance) integradas através de um Barqueiro no porto e uma interface nativa no Switch.
                    </div>
                    <div class="card-footer">
                        <span>Origem: Top DMODs da História</span>
                        <span>Status: 100% Disponíveis</span>
                    </div>
                </div>
            </div>
        </div>

        <!-- TAB 2: MECÂNICAS & SISTEMAS -->
        <div id="mecanicas-qol" class="tab-pane">
            <div class="section-header">
                <h2>Sistemas de Jogabilidade Desenvolvidos pela Comunidade</h2>
            </div>

            <div class="card-grid">
                <div class="card">
                    <div class="card-tag tag-qol">Inventário</div>
                    <div class="card-title">Itens Empilháveis (Stacking)</div>
                    <div class="card-origin">Origem: Questlog Edition (Seseler & Elpo)</div>
                    <div class="card-desc">
                        Consumíveis idênticos (elixires, poções, nozes de cura, bombas) agrupam-se no mesmo slot com contador numérico (ex: <code>Nozes x15</code>). Libera o jogador do limite de 16 slots entulhados.
                    </div>
                    <div class="card-footer"><span>Tipo: Script DinkC</span><span>Impacto: Crítico</span></div>
                </div>

                <div class="card">
                    <div class="card-tag tag-combat">Defesa</div>
                    <div class="card-title">Escudo na Mão Secundária</div>
                    <div class="card-origin">Origem: Off-Handed Shield (Robj & ExDeathevn)</div>
                    <div class="card-desc">
                        Dink segura um escudo na mão esquerda (424 sprites dedicados). Permite bloquear flechas, magias e golpes corporais com botão dedicado em tempo real.
                    </div>
                    <div class="card-footer"><span>Tipo: Sprites + Scripts</span><span>Impacto: Revolucionário</span></div>
                </div>

                <div class="card">
                    <div class="card-tag tag-story">Navegação</div>
                    <div class="card-title">Diário de Missões (Quest Log)</div>
                    <div class="card-origin">Origem: Questlog Edition / Item Quest Log</div>
                    <div class="card-desc">
                        Menu acessível por botão dedicado que lista missões ativas, objetivos atuais, pistas e missões concluídas. Nunca mais fique sem saber onde ir.
                    </div>
                    <div class="card-footer"><span>Tipo: Interface UI</span><span>Impacto: Alto</span></div>
                </div>

                <div class="card">
                    <div class="card-tag tag-qol">Combate</div>
                    <div class="card-title">Barra de Vida dos Inimigos</div>
                    <div class="card-origin">Origem: Enemy Healthbar (Development)</div>
                    <div class="card-desc">
                        Exibe um mini-medidor acima de monstros atingidos. Permite calcular dano e saber a resistência de chefes e criaturas de elite.
                    </div>
                    <div class="card-footer"><span>Tipo: Overlay HUD</span><span>Impacto: Alto</span></div>
                </div>

                <div class="card">
                    <div class="card-tag tag-magic">RPG</div>
                    <div class="card-title">4 Atributos Secundários de RPG</div>
                    <div class="card-origin">Origem: Pilgrim's Quest (Simon Klaebe)</div>
                    <div class="card-desc">
                        <b>Honra (&ahonour)</b>: Moralidade e reações de NPCs.<br>
                        <b>Agilidade (&bagility)</b>: Velocidade de corrida e esquiva.<br>
                        <b>Malandragem (&ribald)</b>: Lábia social em tavernas.<br>
                        <b>Sorte (&cluck)</b>: Críticos e chance de drops raros.
                    </div>
                    <div class="card-footer"><span>Tipo: Variáveis Globais</span><span>Impacto: Profundidade</span></div>
                </div>

                <div class="card">
                    <div class="card-tag tag-qol">Progresso</div>
                    <div class="card-title">Sistema de Conquistas (Achievements)</div>
                    <div class="card-origin">Origem: Achievement Unlocked (CocoMonkey)</div>
                    <div class="card-desc">
                        Mais de 40 troféus e proezas com notificações visuais na tela (alimentar porcos, matar o primeiro monstro, segredos descobertos, matar o pato da Rita).
                    </div>
                    <div class="card-footer"><span>Tipo: Sistema Meta</span><span>Impacto: Rejogabilidade</span></div>
                </div>
            </div>
        </div>

        <!-- TAB 3: BESTIÁRIO & CHEFES -->
        <div id="bestiario-chefes" class="tab-pane">
            <div class="section-header">
                <h2>Bestiário Expandido: Novos Monstros & Chefes da Comunidade</h2>
            </div>
            <p style="color: var(--text-muted); margin-bottom: 20px;">
                Ao longo dos anos, autores da comunidade modelaram e desenharam dezenas de novos monstros com comportamentos únicos de inteligência artificial (IA) que superam os monstros básicos do jogo de 1997.
            </p>

            <table>
                <thead>
                    <tr>
                        <th>Criatura / Chefe</th>
                        <th>Mod / Pack de Origem</th>
                        <th>Comportamento & Habilidades</th>
                        <th>Papel na Complete Edition</th>
                    </tr>
                </thead>
                <tbody>
                    <tr>
                        <td><strong>🐍 O Basilisco Real</strong></td>
                        <td><em>Pilgrim's Quest</em></td>
                        <td>Serpente colossal subaquática; ataca com veneno mortal e só poupa heróis de alta Honra.</td>
                        <td>Chefe marítimo nas viagens de barco.</td>
                    </tr>
                    <tr>
                        <td><strong>🌊 Demônios da Água (Water Demons)</strong></td>
                        <td><em>Pilgrim's Quest</em></td>
                        <td>Criaturas anfíbias que emergem de rios e lagos; imunes a flechas comuns, vulneráveis a magias.</td>
                        <td>Inimigos de rios e pântanos em Terris.</td>
                    </tr>
                    <tr>
                        <td><strong>🦂 Escorpiões Negros do Deserto</strong></td>
                        <td><em>Stone of Balance</em></td>
                        <td>Atacam com investidas rápidas em bando e aplicam veneno paralisante contínuo.</td>
                        <td>Inimigos das regiões áridas e cavernas.</td>
                    </tr>
                    <tr>
                        <td><strong>👁️ O Olho Flutuante (Beholder)</strong></td>
                        <td><em>Eyeball Enemy Pack</em></td>
                        <td>Flutua sobre obstáculos; dispara raios de energia telecinética que empurram o Dink.</td>
                        <td>Monstro de elite nas masmorras do Cast.</td>
                    </tr>
                    <tr>
                        <td><strong>🐝 Vespas Gigantes Assassinas</strong></td>
                        <td><em>Wasp Enemy Pack</em></td>
                        <td>Voam em padrão errático e atacam em mergulho com ferroadas venenosas.</td>
                        <td>Inimigos das copas de árvores em florestas.</td>
                    </tr>
                    <tr>
                        <td><strong>🐉 Dragão Alado Ancião</strong></td>
                        <td><em>Legend's Tale Dragon Pack</em></td>
                        <td>Dragão completo com animações de voo, sopro de fogo contínuo e rabo esmagador.</td>
                        <td>Grande Chefe opcional de cavernas vulcânicas.</td>
                    </tr>
                    <tr>
                        <td><strong>💀 O Necromante Supremo</strong></td>
                        <td><em>Necromancer (SimonK)</em></td>
                        <td>Conjura hordas de esqueletos e zumbis continuamente enquanto se teleporta pelo mapa.</td>
                        <td>Chefe de criptas e cemitérios.</td>
                    </tr>
                    <tr>
                        <td><strong>🐗 O Blonca Blindado</strong></td>
                        <td><em>The Blonca Pack</em></td>
                        <td>Variação acouraçada do clássico Bonca; pele dura imune a espadas de baixo nível.</td>
                        <td>Exige bombas ou martelos pesados para derrotar.</td>
                    </tr>
                </tbody>
            </table>
        </div>

        <!-- TAB 4: ARSENAL & MAGIAS -->
        <div id="arsenal-magias" class="tab-pane">
            <div class="section-header">
                <h2>Arsenal Expandido: Novas Armas, Magias & Equipamentos</h2>
            </div>

            <div class="card-grid">
                <div class="card">
                    <div class="card-tag tag-combat">Arma Branca</div>
                    <div class="card-title">Espadas Elementais</div>
                    <div class="card-origin">Origem: Elemental Swords Pack</div>
                    <div class="card-desc">
                        Lâminas imbuídas com dano elemental:<br>
                        • <b>Espada de Chamas</b>: Causa combustão nos monstros.<br>
                        • <b>Lâmina Congelante</b>: Reduz velocidade de ataque inimiga.<br>
                        • <b>Espada Elétrica</b>: Conduz choque entre inimigos próximos.
                    </div>
                </div>

                <div class="card">
                    <div class="card-tag tag-combat">Arma de Arremesso</div>
                    <div class="card-title">Martelo de Arremesso Pesado</div>
                    <div class="card-origin">Origem: Questlog Edition</div>
                    <div class="card-desc">
                        Causa dano de impacto esmagador em alvo único. Ideal contra inimigos blindados (como o Blonca e Golens) onde flechas ricocheteiam sem efeito.
                    </div>
                </div>

                <div class="card">
                    <div class="card-tag tag-magic">Escola Elemental</div>
                    <div class="card-title">Magia de Água & Torrente</div>
                    <div class="card-origin">Origem: Pilgrim's Quest</div>
                    <div class="card-desc">
                        Pode ser usada tanto em combate quanto na exploração: apaga labaredas no cenário, congela a superfície de rios para atravessar e aniquila demônios de lava.
                    </div>
                </div>

                <div class="card">
                    <div class="card-tag tag-magic">Furtividade</div>
                    <div class="card-title">Manto de Invisibilidade</div>
                    <div class="card-origin">Origem: Questlog Edition</div>
                    <div class="card-desc">
                        Consome MP por segundo mantendo Dink translúcido. Monstros não detectam o herói e guardas de fortalezas não atacam.
                    </div>
                </div>

                <div class="card">
                    <div class="card-tag tag-magic">Invocação</div>
                    <div class="card-title">Feitiço de Invocação: Bonca Aliado</div>
                    <div class="card-origin">Origem: Questlog Edition (Summon Bonca)</div>
                    <div class="card-desc">
                        Invoca um monstro Bonca domado que segue Dink pelo mapa, ataca qualquer criatura hostil e serve como distração contra chefes.
                    </div>
                </div>

                <div class="card">
                    <div class="card-tag tag-combat">Disparo Longo</div>
                    <div class="card-title">Arcos & Aljavas Elementais</div>
                    <div class="card-origin">Origem: Quest for Dorinthia</div>
                    <div class="card-desc">
                        Sistema avançado de tiro com arco: permite alternar entre flechas comuns, flechas incendiárias e flechas envenenadas com mira direcional.
                    </div>
                </div>
            </div>
        </div>

        <!-- TAB 5: BIOMAS & MAPAS -->
        <div id="biomas-mapas" class="tab-pane">
            <div class="section-header">
                <h2>Expansão de Cenários, Biomas & Navegação Náutica</h2>
            </div>
            <p style="color: var(--text-muted); margin-bottom: 20px;">
                O mapa original de Dink é limitado a 768 telas terrestres (muitas vazias). A comunidade criou tilesets completos para biomas totalmente novos:
            </p>

            <div class="card-grid">
                <div class="card">
                    <div class="card-tag tag-world">Bioma</div>
                    <div class="card-title">Tundras & Montanhas de Gelo</div>
                    <div class="card-origin">Origem: IceWorld & Snow Mountain Tiles</div>
                    <div class="card-desc">
                        Camadas de neve espessas, cavernas de gelo cristalino, pingentes pontiagudos que caem do teto e superfícies escorregadias.
                    </div>
                </div>

                <div class="card">
                    <div class="card-tag tag-world">Bioma</div>
                    <div class="card-title">Desertos & Ruínas Antigas</div>
                    <div class="card-origin">Origem: Stone of Balance Desert Tiles</div>
                    <div class="card-desc">
                        Dunas de areia fina, cactos, ruínas de civilizações perdidas com templos subterrâneos e tempestades de areia.
                    </div>
                </div>

                <div class="card">
                    <div class="card-tag tag-world">Bioma</div>
                    <div class="card-title">Mares Abertos & Arquipélagos</div>
                    <div class="card-origin">Origem: Pilgrim's Quest Náutica</div>
                    <div class="card-desc">
                        Telas marítimas navegáveis com barco a remo ou veleiro. Correntezas marítimas, redemoinhos misteriosos e ilhas secretas para atracar.
                    </div>
                </div>

                <div class="card">
                    <div class="card-tag tag-world">Bioma</div>
                    <div class="card-title">Cidades nas Nuvens</div>
                    <div class="card-origin">Origem: Cloud Castle Pack</div>
                    <div class="card-desc">
                        Plataformas flutuantes sobre o céu azul, pontes de corda entre nuvens e mecanismos de escaravelhos mágicos.
                    </div>
                </div>
            </div>
        </div>

        <!-- TAB 6: DLCS & CAMPANHAS -->
        <div id="dlcs-campanhas" class="tab-pane">
            <div class="section-header">
                <h2>As Grandes Campanhas (DLCs de Alto Nível)</h2>
            </div>

            <table>
                <thead>
                    <tr>
                        <th>Título da Expansão</th>
                        <th>Autor</th>
                        <th>Nota</th>
                        <th>Tamanho</th>
                        <th>Duração</th>
                        <th>Proposta de Papel na Complete Edition</th>
                    </tr>
                </thead>
                <tbody>
                    <tr>
                        <td><strong>🏆 Pilgrim's Quest (Redux)</strong></td>
                        <td>Simon Klaebe</td>
                        <td>⭐ 9.7</td>
                        <td>34.5 MB</td>
                        <td>~12-15 Horas</td>
                        <td><strong>A Grande Expansão Marítima</strong>: Acessível pelo porto de KernSin através de um Barqueiro.</td>
                    </tr>
                    <tr>
                        <td><strong>⚔️ Cast Awakening 1: Initiation</strong></td>
                        <td>Dan Walma</td>
                        <td>⭐ 9.5</td>
                        <td>8.6 MB</td>
                        <td>~3-4 Horas</td>
                        <td><strong>O Epílogo Canônico</strong>: Continuação direta da derrota do Cast com o Hall dos Heróis.</td>
                    </tr>
                    <tr>
                        <td><strong>📜 Stone of Balance (Redux)</strong></td>
                        <td>Simon Klaebe</td>
                        <td>⭐ 9.5</td>
                        <td>35.7 MB</td>
                        <td>~10-12 Horas</td>
                        <td><strong>Aventura Épica Continental</strong>: Outro grande continente explorável.</td>
                    </tr>
                    <tr>
                        <td><strong>💖 Lyna's Story</strong></td>
                        <td>Paul Pliska</td>
                        <td>⭐ 9.6</td>
                        <td>0.4 MB</td>
                        <td>~2 Horas</td>
                        <td><strong>Spin-off Cômico</strong>: Jogando com Lyna pelo vilarejo com diálogos hilários.</td>
                    </tr>
                    <tr>
                        <td><strong>⏳ Before...</strong></td>
                        <td>SlipDink</td>
                        <td>⭐ 8.5</td>
                        <td>82.8 MB</td>
                        <td>~6-8 Horas</td>
                        <td><strong>Préquel de Origem</strong>: A infância de Dink e a busca por seu pai.</td>
                    </tr>
                </tbody>
            </table>
        </div>

        <!-- TAB 7: ROADMAP -->
        <div id="roadmap" class="tab-pane">
            <div class="section-header">
                <h2>Roadmap de Construção da Complete Edition</h2>
            </div>

            <div class="roadmap-timeline">
                <div class="timeline-item">
                    <div class="timeline-dot"></div>
                    <div class="timeline-title">Fase 1: A Campanha Base Definitiva (Concluída ✅)</div>
                    <div class="timeline-body">
                        • Tradução completa dos 380 scripts com dublagem brasileira e sátira.<br>
                        • Tela inicial de seleção de idioma (PT-BR / EN) com persistência em settings.dat.<br>
                        • NRO e ELF compilados e validados no Switch com preservação total de saves pessoais.
                    </div>
                </div>

                <div class="timeline-item">
                    <div class="timeline-dot"></div>
                    <div class="timeline-title">Fase 2: Fusão das Mecânicas de QoL na Campanha Base</div>
                    <div class="timeline-body">
                        • Integrar o <b>Inventário com Itens Empilháveis</b> (Questlog Edition) para acabar com a bagunça dos 16 slots.<br>
                        • Incorporar a <b>Barra de Vida dos Inimigos</b> sobre os monstros atingidos.<br>
                        • Adicionar o <b>Diário de Missões (Quest Log)</b> na tecla dedicada ou menu de pausa.
                    </div>
                </div>

                <div class="timeline-item">
                    <div class="timeline-dot"></div>
                    <div class="timeline-title">Fase 3: O Novo Menu Nativo de "Expansões & DLCs" no Switch</div>
                    <div class="timeline-body">
                        • Reformular a antiga e feia tela cinza de "Browse Addons" em uma interface moderna em tela cheia.<br>
                        • Cards elegantes navegáveis no D-Pad/Analógico com títulos, banners e sinopses em português.<br>
                        • Botão direto <code>[ Jogar Campanha ]</code> ou <code>[ Continuar ]</code> com gerenciamento de saves isolado.
                    </div>
                </div>

                <div class="timeline-item">
                    <div class="timeline-dot"></div>
                    <div class="timeline-title">Fase 4: Integração In-Game & Expansão de Arsenal</div>
                    <div class="timeline-body">
                        • Adicionar o NPC Barqueiro no porto de KernSin para viagens náuticas diretas às expansões.<br>
                        • Importar o <b>Escudo na Mão Secundária (Off-Handed Shield)</b> e as <b>Espadas Elementais</b> para lojas do jogo base.
                    </div>
                </div>
            </div>
        </div>

    </div>

    <script>
        function showTab(tabId) {
            document.querySelectorAll('.tab-pane').forEach(el => el.classList.remove('active'));
            document.querySelectorAll('.nav-btn').forEach(el => el.classList.remove('active'));
            
            const target = document.getElementById(tabId);
            if (target) target.classList.add('active');
            
            event.target.classList.add('active');
            window.scrollTo({ top: 120, behavior: 'smooth' });
        }
    </script>
</body>
</html>
"""

with open(html_path, "w", encoding="utf-8") as f:
    f.write(html_content)

print(f"Página HTML gerada com sucesso em: {html_path}")
