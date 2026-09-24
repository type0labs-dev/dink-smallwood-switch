#include "PlatformPrecomp.h"
#include "LanguageSelectMenu.h"
#include "MainMenu.h"
#include "Entity/EntityUtils.h"
#include "dink/dink.h"
#include "App.h"
#include "AutoTester.h"

static int g_currentSelectedLang = 0; // 0 = PT-BR, 1 = EN
static boost::signals2::connection g_langRawInputConn;

static void UpdateSelectionVisuals(Entity *pMenu, int selectedIndex)
{
	if (!pMenu) return;

	Entity *pCard0BG = pMenu->GetEntityByName("card0_bg");
	Entity *pCard0Border = pMenu->GetEntityByName("card0_border");
	Entity *pCard1BG = pMenu->GetEntityByName("card1_bg");
	Entity *pCard1Border = pMenu->GetEntityByName("card1_border");

	if (!pCard0BG || !pCard0Border || !pCard1BG || !pCard1Border) return;

	if (selectedIndex == 0)
	{
		// PT-BR is selected: golden highlight
		pCard0BG->GetVar("color")->Set(MAKE_RGBA(170, 110, 20, 220));
		pCard0Border->GetVar("color")->Set(MAKE_RGBA(255, 230, 90, 255));

		// EN is unselected: dark slate
		pCard1BG->GetVar("color")->Set(MAKE_RGBA(35, 30, 28, 175));
		pCard1Border->GetVar("color")->Set(MAKE_RGBA(90, 85, 75, 130));
	}
	else
	{
		// PT-BR is unselected
		pCard0BG->GetVar("color")->Set(MAKE_RGBA(35, 30, 28, 175));
		pCard0Border->GetVar("color")->Set(MAKE_RGBA(90, 85, 75, 130));

		// EN is selected
		pCard1BG->GetVar("color")->Set(MAKE_RGBA(170, 110, 20, 220));
		pCard1Border->GetVar("color")->Set(MAKE_RGBA(255, 230, 90, 255));
	}
}

static bool g_bLangConfirmed = false;

static void LanguageSelectMenuConfirm(Entity *pMenu, int langChoice)
{
	if (g_bLangConfirmed) return;
	g_bLangConfirmed = true;

	g_langRawInputConn.disconnect();

	// langChoice: 0 = PT, 1 = EN
	uint32 engineLang = (langChoice == 0) ? 1 : 0; // engine: 1 = Portuguese, 0 = English

	GetApp()->GetShared()->GetVar("language")->Set(engineLang);
	GetApp()->GetShared()->GetVar("language_chosen")->Set(uint32(1));
	SyncPersistentData();

	LogMsg("Language selected: %s (engine code %d)", engineLang == 1 ? "Portuguese" : "English", engineLang);

	GetAudioManager()->Play("audio/click.wav");

	DisableAllButtonsEntity(pMenu);
	FadeOutEntity(pMenu, true, 250);
	GetMessageManager()->CallEntityFunction(pMenu, 300, "OnDelete", NULL);

	MainMenuCreate(pMenu->GetParent(), true);
}

void LanguageSelectMenuOnSelect(VariantList *pVList)
{
	Entity *pEntClicked = pVList->m_variant[1].GetEntity();
	Entity *pMenu = GetEntityRoot()->GetEntityByName("LanguageSelectMenu");
	if (!pMenu) return;

	string name = pEntClicked->GetName();

	if (name == "lang_option_0")
	{
		g_currentSelectedLang = 0;
		UpdateSelectionVisuals(pMenu, 0);
		LanguageSelectMenuConfirm(pMenu, 0);
		return;
	}

	if (name == "lang_option_1")
	{
		g_currentSelectedLang = 1;
		UpdateSelectionVisuals(pMenu, 1);
		LanguageSelectMenuConfirm(pMenu, 1);
		return;
	}

	if (name == "btn_confirm")
	{
		LanguageSelectMenuConfirm(pMenu, g_currentSelectedLang);
		return;
	}
}

void LanguageSelectMenuOnInputRaw(VariantList *pVList)
{
	Entity *pMenu = GetEntityRoot()->GetEntityByName("LanguageSelectMenu");
	if (!pMenu) return;

	bool bDown = pVList->Get(1).GetUINT32() != 0;
	if (!bDown) return;

	uint32 key = pVList->Get(0).GetUINT32();

	// Up / Previous
	if (key == VIRTUAL_KEY_DIR_UP || key == VIRTUAL_DPAD_HAT_UP || key == 'w' || key == 'W' || key == '1' || key == VIRTUAL_KEY_DIR_LEFT)
	{
		g_currentSelectedLang = 0;
		UpdateSelectionVisuals(pMenu, 0);
		GetAudioManager()->Play("audio/click.wav");
		if (key == '1')
		{
			LanguageSelectMenuConfirm(pMenu, 0);
		}
		return;
	}

	// Down / Next
	if (key == VIRTUAL_KEY_DIR_DOWN || key == VIRTUAL_DPAD_HAT_DOWN || key == 's' || key == 'S' || key == '2' || key == VIRTUAL_KEY_DIR_RIGHT)
	{
		g_currentSelectedLang = 1;
		UpdateSelectionVisuals(pMenu, 1);
		GetAudioManager()->Play("audio/click.wav");
		if (key == '2')
		{
			LanguageSelectMenuConfirm(pMenu, 1);
		}
		return;
	}

	// Confirm on Enter, Space, Gamepad A/B/Fire
	if (key == 13 || key == ' ' || key == VIRTUAL_DPAD_BUTTON_DOWN || key == VIRTUAL_DPAD_BUTTON_RIGHT ||
	    key == VIRTUAL_KEY_GAME_FIRE || key == VIRTUAL_KEY_GAME_TALK)
	{
		LanguageSelectMenuConfirm(pMenu, g_currentSelectedLang);
		return;
	}
}

Entity * LanguageSelectMenuCreate(Entity *pParentEnt, bool bFadeIn)
{
	// If running automated test, immediately skip to MainMenu
	if (AutoTesterIsActive())
	{
		return MainMenuCreate(pParentEnt, bFadeIn);
	}

	// If language was already chosen, skip directly to MainMenu
	if (GetApp()->GetVarWithDefault("language_chosen", uint32(0))->GetUINT32() != 0)
	{
		return MainMenuCreate(pParentEnt, bFadeIn);
	}

	g_bLangConfirmed = false;

	GetBaseApp()->ClearError();

	Entity *pBG = CreateOverlayEntity(pParentEnt, "LanguageSelectMenu", ReplaceWithDeviceNameInFileName("interface/iphone/bkgd_stone.rttex"), 0, 0);
	AddFocusIfNeeded(pBG, true, 100);
	pBG->AddComponent(new FocusRenderComponent);

	// Screen dimensions (1024x768 virtual coordinate system)
	const float screenW = 1024.0f;
	const float screenH = 768.0f;

	// Center dialog panel dimensions
	const float panelW = 720.0f;
	const float panelH = 540.0f;
	const float panelX = (screenW - panelW) * 0.5f; // 152
	const float panelY = (screenH - panelH) * 0.5f; // 114

	// Panel background and border
	CreateOverlayRectEntity(pBG, CL_Rectf(panelX, panelY, panelX + panelW, panelY + panelH), MAKE_RGBA(18, 14, 12, 225));
	CreateOverlayRectEntity(pBG, CL_Rectf(panelX - 2, panelY - 2, panelX + panelW + 2, panelY + panelH + 2), MAKE_RGBA(190, 150, 75, 210), RectRenderComponent::STYLE_BORDER_ONLY);
	CreateOverlayRectEntity(pBG, CL_Rectf(panelX + 4, panelY + 4, panelX + panelW - 4, panelY + panelH - 4), MAKE_RGBA(100, 80, 45, 110), RectRenderComponent::STYLE_BORDER_ONLY);

	// Main Title (centered in panel)
	CreateTextBoxEntity(pBG, "title", CL_Vec2f(panelX, panelY + 25.0f), CL_Vec2f(panelW, 45.0f), "`wSELECIONE O IDIOMA / SELECT LANGUAGE``", 1.15f, ALIGNMENT_CENTER);

	// Subtitle hint
	CreateTextBoxEntity(pBG, "subtitle", CL_Vec2f(panelX, panelY + 68.0f), CL_Vec2f(panelW, 30.0f), "`8(Voce podera alterar mais tarde no menu Opcoes)``", 0.70f, ALIGNMENT_CENTER);

	// Determine starting selection from saved setting
	uint32 savedLang = GetApp()->GetVarWithDefault("language", uint32(1))->GetUINT32();
	g_currentSelectedLang = (savedLang == 1) ? 0 : 1; // 0 is PT, 1 is EN

	// Card dimensions
	const float cardW = 620.0f;
	const float cardH = 115.0f;
	const float cardX = (screenW - cardW) * 0.5f; // 202

	// Card 0: Português (Brasil)
	const float card0Y = panelY + 115.0f; // 229
	Entity *pCard0BG = CreateOverlayRectEntity(pBG, CL_Rectf(cardX, card0Y, cardX + cardW, card0Y + cardH), MAKE_RGBA(35, 30, 28, 175));
	pCard0BG->SetName("card0_bg");
	Entity *pCard0Border = CreateOverlayRectEntity(pBG, CL_Rectf(cardX - 2, card0Y - 2, cardX + cardW + 2, card0Y + cardH + 2), MAKE_RGBA(90, 85, 75, 130), RectRenderComponent::STYLE_BORDER_ONLY);
	pCard0Border->SetName("card0_border");

	CreateTextBoxEntity(pBG, "txt_title_0", CL_Vec2f(cardX, card0Y + 16.0f), CL_Vec2f(cardW, 38.0f), "`wPORTUGUES (BRASIL)``", 1.05f, ALIGNMENT_CENTER);
	CreateTextBoxEntity(pBG, "txt_desc_0", CL_Vec2f(cardX, card0Y + 54.0f), CL_Vec2f(cardW, 45.0f), "`3Edicao Brasileira com satira e girias BR``", 0.75f, ALIGNMENT_CENTER);

	Entity *pHotspot0 = CreateButtonHotspot(pBG, "lang_option_0", CL_Vec2f(cardX, card0Y), CL_Vec2f(cardW, cardH), Button2DComponent::BUTTON_STYLE_CLICK_ON_TOUCH_RELEASE);
	pHotspot0->GetFunction("OnButtonSelected")->sig_function.connect(&LanguageSelectMenuOnSelect);

	// Card 1: English (Original)
	const float card1Y = panelY + 260.0f; // 374
	Entity *pCard1BG = CreateOverlayRectEntity(pBG, CL_Rectf(cardX, card1Y, cardX + cardW, card1Y + cardH), MAKE_RGBA(35, 30, 28, 175));
	pCard1BG->SetName("card1_bg");
	Entity *pCard1Border = CreateOverlayRectEntity(pBG, CL_Rectf(cardX - 2, card1Y - 2, cardX + cardW + 2, card1Y + cardH + 2), MAKE_RGBA(90, 85, 75, 130), RectRenderComponent::STYLE_BORDER_ONLY);
	pCard1Border->SetName("card1_border");

	CreateTextBoxEntity(pBG, "txt_title_1", CL_Vec2f(cardX, card1Y + 16.0f), CL_Vec2f(cardW, 38.0f), "`wENGLISH (ORIGINAL)``", 1.05f, ALIGNMENT_CENTER);
	CreateTextBoxEntity(pBG, "txt_desc_1", CL_Vec2f(cardX, card1Y + 54.0f), CL_Vec2f(cardW, 45.0f), "`3Original 1997 classic text by Seth Robinson``", 0.75f, ALIGNMENT_CENTER);

	Entity *pHotspot1 = CreateButtonHotspot(pBG, "lang_option_1", CL_Vec2f(cardX, card1Y), CL_Vec2f(cardW, cardH), Button2DComponent::BUTTON_STYLE_CLICK_ON_TOUCH_RELEASE);
	pHotspot1->GetFunction("OnButtonSelected")->sig_function.connect(&LanguageSelectMenuOnSelect);

	// Update colors based on current selection
	UpdateSelectionVisuals(pBG, g_currentSelectedLang);

	// Bottom navigation hint
	CreateTextBoxEntity(pBG, "hints", CL_Vec2f(panelX, panelY + panelH - 45.0f), CL_Vec2f(panelW, 35.0f), "`8(D-Pad / Analogico) Escolher   |   (A / Espaco / Toque) Confirmar``", 0.75f, ALIGNMENT_CENTER);

	// Raw input listener for D-Pad, gamepad buttons and keyboard
	g_langRawInputConn.disconnect();
	g_langRawInputConn = GetBaseApp()->m_sig_raw_keyboard.connect(1, boost::bind(&LanguageSelectMenuOnInputRaw, _1));

	FadeInEntity(pBG, true, 350);

	return pBG;
}
