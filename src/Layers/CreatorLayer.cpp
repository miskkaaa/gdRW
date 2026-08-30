#include "../includes/CreatorLayer.hpp"
// #include "Geode/cocos/CCDirector.h"
// #include "Geode/cocos/cocoa/CCObject.h"
// #include "Geode/cocos/sprite_nodes/CCSpriteFrameCache.h"
// #include <Geode/Enums.hpp>
// #include <Geode/binding/CCMenuItemSpriteExtra.hpp>
// #include <Geode/binding/ChallengesPage.hpp>
// #include <Geode/binding/CreatorLayer.hpp>
// #include <Geode/binding/GJPromoPopup.hpp>
// #include <Geode/binding/GameStatsManager.hpp>

// #include <Geode/binding/PlatformToolbox.hpp>

#include "../Helpers.hpp"
#include "Geode/cocos/CCDirector.h"
#include <Geode/Enums.hpp>
#include <Geode/binding/GJPathsLayer.hpp>
#include <Geode/binding/GJSearchObject.hpp>
#include <Geode/binding/LevelBrowserLayer.hpp>

void RECreatorLayer::checkQuestsStatus() {
    if (!Helper::s("CLcheckQuestsStatus")) {
        CreatorLayer::checkQuestsStatus();
        return;
    }
    if (!m_questsSprite) return;
    auto gsm = GameStatsManager::get();
    bool canClaim = false;
    auto size = m_questsSprite->getScaledContentSize();

    m_questsSprite->removeAllChildren();
    for (int i = 1; i <= 3; i++) {
        auto chal = gsm->getChallenge(i);
        if (chal && chal->m_canClaim) {
            canClaim = true;
            break;
        };
    }

    if (!canClaim) return;

    auto spr = CCSprite::createWithSpriteFrameName("exMark_001.png");
    if (!spr) return;

    m_questsSprite->addChild(spr, 10); // a1->m_questsSprite->addChild_0(a1->m_questsSprite, v6, 10);
    // ((void (__fastcall *)(struct cocos2d::CCSprite *))v6->setScale_0)(v6);
    // so i would have done m_questsSprite->setScale() but idk what the args are
    spr->setScale(0.8f);
    spr->setPosition({20.0f, size.height});
};

void RECreatorLayer::dialogClosed(DialogLayer* layer) {
    if (!Helper::s("CLdialogClosed")) {
        CreatorLayer::dialogClosed(layer);
        return;
    }
    if (!layer) return;
    auto tag = layer->getTag();

    if (tag == 1) CreatorLayer::onAdventureMap(this);
    else if (tag == 0) {
        auto gm = GameManager::sharedState();
        gm->setUGV("1", true);

        auto frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("secretDoorBtn_open_001.png");
        if (m_secretDoorSprite && frame) {
            m_secretDoorSprite->setDisplayFrame(frame);
        }

        /*
            GameManager::setUGV(v4, (const char *)&word_140531E90, 1);
            v5 = **(_QWORD **)&a1->m_uID;
            v6 = (cocos2d::CCSpriteFrameCache *)cocos2d::CCSpriteFrameCache::sharedSpriteFrameCache();
            v7 = cocos2d::CCSpriteFrameCache::spriteFrameByName(v6, "secretDoorBtn_open_001.png");
            (*(void (__fastcall **)(_QWORD, struct cocos2d::CCSpriteFrame *))(v5 + 992))(*(_QWORD *)&a1->m_uID, v7);
        */
    }
}

void RECreatorLayer::keyBackClicked() {
    if (!Helper::s("CLkeyBackClicked")) {
        CreatorLayer::keyBackClicked();
        return;
    }
    auto scene = MenuLayer::scene(false);
    if (!scene) return;

    auto trans = CCTransitionFade::create(0.5f, scene);
    CCDirector::sharedDirector()->replaceScene(trans);
    GameManager::sharedState()->fadeInMenuMusic();
    // (*(void (__fastcall **)(char *, _QWORD))(*(_QWORD *)p_height + 976LL))(p_height, 0);
    // im actually not sure if its fadeInMenuMusic(); but eh
    log::info("gay");
}

void RECreatorLayer::onBack(CCObject* sender) {
    if (!Helper::s("CLonBack")) {
        CreatorLayer::onBack(sender);
        return;
    }
    auto scene = MenuLayer::scene(false);
    if (!scene) return;

    auto trans = CCTransitionFade::create(0.5f, scene);

    CCDirector::sharedDirector()->replaceScene(trans);
    this->setKeypadEnabled(false);

    log::info("gay 2");
}

void RECreatorLayer::onAdventureMap(CCObject* sender) {
    if (!Helper::s("CLonAdventureMap")) {
        CreatorLayer::onAdventureMap(sender);
        return;
    }
    auto page = GJPromoPopup::create("mapPromo.png");
    // i should remember that i should use
    // "mapPromo.png"
    // instead of "promo_boom.png" lmfao
    if (page) page->show();
}

void RECreatorLayer::onChallenge(CCObject* sender) {
    if (!Helper::s("CLonChallenge")) {
        CreatorLayer::onChallenge(sender);
        return;
    }
    auto item = static_cast<CCMenuItemSpriteExtra*>(sender);
    auto normal = item->getNormalImage();
    if (normal) normal->removeAllChildren();

    auto page = ChallengesPage::create();
    if (page) page->show();
}

void RECreatorLayer::onDailyLevel(CCObject* sender) {
    if (!Helper::s("CLonDailyLevel")) {
        CreatorLayer::onChallenge(sender);
        return;
    }
    auto page = DailyLevelPage::create(GJTimedLevelType::Daily);
    /*
    enum class GJTimedLevelType {
        Daily = 0,
        Weekly = 1,
        Event = 2
    };
    */
    if (page) page->show();
    log::info("gay 3");
}

void RECreatorLayer::onEventLevel(CCObject* sender) {
    if (!Helper::s("CLonEventLevel")) {
        CreatorLayer::onEventLevel(sender);
        return;
    }
    auto page = DailyLevelPage::create(GJTimedLevelType::Event);
    if (page) page->show();
}

void RECreatorLayer::onWeeklyLevel(CCObject* sender) {
    if (!Helper::s("CLonWeeklyLevel")) {
        CreatorLayer::onWeeklyLevel(sender);
        return;
    }
    auto page = DailyLevelPage::create(GJTimedLevelType::Weekly);
    if (page) page->show();
}

void RECreatorLayer::onTreasureRoom(CCObject* sender) {
    if (!Helper::s("CLonTreasureRoom")) {
        CreatorLayer::onTreasureRoom(sender);
        return;
    }

    auto stats = GameStatsManager::sharedState();
    auto ws = CCDirector::sharedDirector()->getWinSize();
    auto key = GameStatsManager::sharedState()->getStat("21");

    if (GameManager::sharedState()->getUGV("5")) {
        auto scene = SecretRewardsLayer::scene(false);
        auto transition = CCTransitionFade::create(0.5f, scene);
        CCDirector::sharedDirector()->replaceScene(transition);
        return;
    }

    if (key < 5) {
        std::string msg = "";
        if (key <= 0) {
            msg = "Bring me <cy>5</c> <cg>keys</c>,<d020>\n"
            "and I will let you pass.";
        } else {
            auto rem = 5 - key;
            auto text = fmt::format("Collect <cy>{}</c> more <cg>key{}</c>,<d020>\n"
            "and I will let you pass.", rem, rem > 1 ? "s" : "");

            msg = text;
        }

        auto dialobj = DialogObject::create(
            "The Keymaster",
            msg,
            2,
            1.0f,
            false,
            {255,255,255}
        );

        auto dial = DialogLayer::create(dialobj, 2);
        this->addChild(dial, 100);
        if (dial->m_mainLayer) dial->m_mainLayer->setPosition(ws * 0.5f);

        dial->animateInRandomSide();
        return;
    }

    auto objs = CCArray::create();

    objs->addObject(DialogObject::create(
        "The Keymaster",
        "Well, well, well.<d035>\nLook who it is.",
        2,
        1.0f,
        false,
        {255, 255, 255}
    ));

    objs->addObject(DialogObject::create(
        "The Keymaster",
        "I see you have the <cg>keys</c>.<d040>\nBut what comes next?",
        2,
        1.0f,
        false,
        {255, 255, 255}
    ));

    objs->addObject(DialogObject::create(
        "The Keymaster",
        "The <co>door</c> is open.<d040>\n"
        "Time to find out<d010>.<d010>.<d010>.",
        2,
        1.0f,
        false,
        {255, 255, 255}
    ));

    auto dialog = DialogLayer::createWithObjects(objs, 2);
    dialog->setTag(0);
    this->addChild(dialog, 100);

    dialog->updateChatPlacement(DialogChatPlacement::Center);
    dialog->animateIn(DialogAnimationType::FromLeft);

    GameManager::sharedState()->setGameVariable("5", true);
}

void RECreatorLayer::onSecretVault(CCObject* sender) {
    if (!Helper::s("CLonSecretVault")) {
        CreatorLayer::onSecretVault(sender);
        return;
    }
    auto gsm = GameStatsManager::sharedState();

    if (gsm->getStat("13") < 50) {
        auto index = m_vaultDialogIndex;
        if (index >= 0) {
            index++;
        } else {
            index = geode::utils::random::generate<int>(0,11);
        }
        m_vaultDialogIndex = index;

        auto title = "The Keymaster";
        auto text = "You are not ready...";

        switch (index) {
            case 1:
                text = "I can't let you in.";
                break;
            case 2:
                text = "Player used knock.<d040>\nIt's not very effective.";
                break;
            case 3:
                text = "Don't you have something better to do?";
                break;
            case 4:
                text = "That is a bad idea...";
                break;
            case 5:
                text = ".<d030>.<d030>.";
                break;
            case 6:
                text = "I guess you don't like rules...";
                break;
            case 7:
                text = "RubRub told me not to let anyone in.";
                break;
            case 8:
                text = "This is not the door you are looking for.";
                break;
            case 9:
                text = "I don't understand why you keep clicking...";
                break;
            case 10:
                text = "Trust me,<d030> you don't want to come in here.";
                break;
            default:
                m_vaultDialogIndex = 0;
                break;
        }

        auto layerObj = DialogObject::create(title, text, 2, 1.0f, true, {255, 255, 255});
        auto layer = DialogLayer::create(layerObj, 2);
        this->addChild(layer, 100);

        auto ws = CCDirector::sharedDirector()->getWinSize();
        if (layer->m_mainLayer) layer->m_mainLayer->setPosition(ws * 0.5f);

        layer->animateInRandomSide();
    } else {
        auto scene = SecretLayer2::scene();
        auto trans = CCTransitionFade::create(0.5f, scene);
        CCDirector::sharedDirector()->replaceScene(trans);
    }
}

void RECreatorLayer::onFeaturedLevels(CCObject* sender) {
    if (!Helper::s("CLonFeaturedLevels")) {
        CreatorLayer::onFeaturedLevels(sender);
        return;
    }
    log::info("gay sex");
    auto searchObj = GJSearchObject::create(SearchType::Featured);
    auto scene = LevelBrowserLayer::scene(searchObj);
    auto trans = CCTransitionFade::create(0.5f, scene);
    CCDirector::sharedDirector()->pushScene(trans);
}

void RECreatorLayer::onGauntlets(CCObject* sender) {
    if (!Helper::s("CLonGauntlets")) {
        CreatorLayer::onGauntlets(sender);
        return;
    }
    log::info("sesbian lex");
    auto scene = GauntletSelectLayer::scene(1);
    auto trans = CCTransitionFade::create(0.5f, scene);
    CCDirector::sharedDirector()->pushScene(trans);
}

void RECreatorLayer::onMultiplayer(CCObject* sender) {
    if (!Helper::s("CLonMultiplayer")) {
        CreatorLayer::onMultiplayer(sender);
        return;
    }
    auto title = "The Keymaster";
    auto text = "Versus mode has been <co>delayed</c>,\nbut it's in the works!";
    // REMINDER: rename title's and fix case 5 :3
    // fixed
    int bullshit = 2;

    switch (m_versusDialogIndex) {
        case 1:
            text = "Yea<d010>.<d010>.<d010>. It's still <cl>delayed</c>.";
            bullshit = 2;
            break;
        case 2:
            text = "I blame <cg>RobTop</c>.";
            title = "Scratch";
            bullshit = 10;
            break;
        case 3:
            text = "Who else could we <cr>blame</c>?\nWe're not even real.";
            bullshit = 2;
            break;
        case 4:
            text = "Speak for yourself <co>I'm real!</c>";
            title = "Scratch";
            bullshit = 14;
            break;
        case 5:
            text = "<cl>Yea, a real pain in the<d010>.<d010>.<d010>.</c>";
            bullshit = 2;
            break;
        case 6:
            text = "You're just <cr>mad</c> because you don't have a <cy>shop</c>.";
            title = "Scratch";
            bullshit = 26;
            break;
        case 7:
            text = "You have a <cy>shop</c>?";
            bullshit = 4;
            break;
        case 8:
            text = "<co>I HAVE SAID TOO MUCH!\nQUICKLY TO THE <i050><s260>CHOPPER!</s></i></c>";
            title = "Scratch";
            bullshit = 10;
            break;
        case 9:
            text = "You don't have a chop<d010>.<d010>.<d010>.";
            bullshit = 2;
            break;
        case 10:
            text = ".<d010>.<d010>.";
            title = "Scratch";
            bullshit = 52;
            break;
        case 11:
            text = ".<d010>.<d010>.<d010>.<d010>.";
            bullshit = 17;
            break;
        default:
            break;
    }

    auto layerObj = DialogObject::create(title, text, bullshit, 1.0f, false, {255, 255, 255});
    auto layer = DialogLayer::create(layerObj, 2);
    this->addChild(layer, 100);

    auto ws = CCDirector::sharedDirector()->getWinSize();
    if (layer->m_mainLayer) layer->m_mainLayer->setPosition(ws * 0.5f);

    layer->animateInRandomSide();

    m_versusDialogIndex++;
    if (m_versusDialogIndex > 11) m_versusDialogIndex = 0;
}

void RECreatorLayer::onMyLevels(CCObject* sender) {
    if (!Helper::s("CLonMyLevels")) {
        CreatorLayer::onMyLevels(sender);
        return;
    }
    auto gm = GameManager::sharedState();
    auto st = gm->m_localSearchType;
    log::info("onmylevels fuck");
    auto search = GJSearchObject::create(st == SearchType::MyLists ? SearchType::MyLists : SearchType::MyLevels);
    if (st != SearchType::MyLists) {
        auto folder = gm->getIntGameVariable("0091");
        if (folder > 999) {
            folder = 999;
        } else if (folder < 0){
            folder = 0;
        }

        search->m_folder = folder;
    }

    auto scene = LevelBrowserLayer::scene(search);
    auto trans = CCTransitionFade::create(0.5f, scene);

    CCDirector::sharedDirector()->pushScene(trans);
}

void RECreatorLayer::onSavedLevels(CCObject* sender) {
    if (!Helper::s("CLonSavedLevels")) {
        CreatorLayer::onSavedLevels(sender);
        return;
    }

    auto gm = GameManager::sharedState();
    auto st = gm->m_savedSearchType;

    auto search = GJSearchObject::create(st == SearchType::FavouriteLists ? SearchType::FavouriteLists : SearchType::SavedLevels);

    auto folder = gm->getIntGameVariable("0092");
    search->m_folder = std::clamp(folder, 0, 999);

    auto scene = LevelBrowserLayer::scene(search);
    auto trans = CCTransitionFade::create(0.5f, scene);

    CCDirector::sharedDirector()->pushScene(trans);
}

void RECreatorLayer::onLeaderboards(CCObject* sender) {
    if (!Helper::s("CLonLeaderboards")) {
        CreatorLayer::onLeaderboards(sender);
        return;
    }

    auto glm = GameLevelManager::sharedState();

    auto scene = LeaderboardsLayer::scene(
        glm->m_leaderboardType,
        glm->m_leaderboardStat
    );

    auto trans = CCTransitionFade::create(0.5f, scene);
    CCDirector::sharedDirector()->pushScene(trans);
}

void RECreatorLayer::onTopLists(CCObject* sender) {
    if (!Helper::s("CLonTopLists")) {
        CreatorLayer::onTopLists(sender);
        return;
    }

    auto search = GJSearchObject::create(
    static_cast<SearchType>(static_cast<int>(SearchType::Recent) |static_cast<int>(SearchType::MostLiked))
    );
    search->m_searchMode = 1;
    auto scene = LevelBrowserLayer::scene(search);
    auto trans = CCTransitionFade::create(0.5f, scene);

    CCDirector::sharedDirector()->pushScene(trans);
    GameManager::sharedState()->m_sceneEnum = 1;
}

void RECreatorLayer::onOnlineLevels(CCObject* sender) {
    if (!Helper::s("CLonOnlineLevels")) {
        CreatorLayer::onOnlineLevels(sender);
        return;
    }

    auto searchType = GameManager::sharedState()->m_levelSearchType;
    auto scene = LevelSearchLayer::scene(searchType);
    auto trans = CCTransitionFade::create(0.5f, scene);

    CCDirector::sharedDirector()->pushScene(trans);
}

void RECreatorLayer::onPaths(CCObject* sender) {
    if (!Helper::s("CLonPaths")) {
        CreatorLayer::onPaths(sender);
        return;
    }
    auto page = GJPathsLayer::create();
    if (page) page->show();
}

void RECreatorLayer::onMapPacks(CCObject* sender) {
    if (!Helper::s("CLonMapPacks")) {
        CreatorLayer::onMapPacks(sender);
        return;
    }
    auto obj = GJSearchObject::create(
        static_cast<SearchType>(
            static_cast<int>(SearchType::Sends) |
            static_cast<int>(SearchType::Downloaded)
        )
    );

    auto scene = LevelBrowserLayer::scene(obj);
    auto trans = CCTransitionFade::create(0.5f, scene);

    CCDirector::sharedDirector()->pushScene(trans);
    GameManager::sharedState()->m_sceneEnum = 1;
}

CCScene* RECreatorLayer::scene() {
    if (!Helper::s("CLscene")) {
        CreatorLayer::scene();
        return nullptr;
    }
    auto scene = CCScene::create();
    if (!scene) return nullptr;

    auto layer = RECreatorLayer::create();
    //layer->setID("CreatorLayer");
    if (!layer) return nullptr;

    scene->addChild(layer);
    return scene;
}

CreatorLayer* RECreatorLayer::create() {
    if (!Helper::s("CLcreate")) {
        CreatorLayer::create();
        return nullptr;
    }
    auto ret = new RECreatorLayer();
    log::info("test");
    if (ret && ret->init()) {
        ret->autorelease();
        return ret;
    }
    delete ret;
    return nullptr;
}

bool RECreatorLayer::init() {
    // non win: https://gd-src-raw.undefined0.dev/Geometry%20Dash/CreatorLayer__init.cpp
    // win: https://gd-src-raw.undefined0.dev/GeometryDash.exe/CreatorLayer__init.cpp
    if (!Helper::s("CLinit")) {
        CreatorLayer::init();
        return true;
    }
    if (!CCLayer::init()) return false;
    this->setKeypadEnabled(true);
    this->setID("CreatorLayer");
    this->setKeyboardEnabled(true);

    auto dir = CCDirector::sharedDirector();
    auto ws = dir->getWinSize();

    auto bg = CCSprite::create("GJ_gradientBG.png");
    bg->setAnchorPoint({0.0f, 0.0f});
    bg->setPosition({-5.0f, -5.0f}); // cocos2d::CCPoint::CCPoint(&v116, -5.0, -5.0);
    // im so fucking confused???????????

    // ccColor3B v113 which and v113 is 26112
    // eh i can use devtools
    // 0, 102, 255
    bg->setScaleX((ws.width + 10.f) / bg->getContentSize().width);
    bg->setScaleY((ws.height + 10.f) / bg->getContentSize().height);
    bg->setColor({0, 102, 255});
    bg->setID("background");
    this->addChild(bg, -2);

    auto menu = CCMenu::create();
    menu->setID("creator-buttons-menu");
    this->addChild(menu);

    auto searchTemp = CCSprite::createWithSpriteFrameName("GJ_searchBtn_001.png");
    if (!searchTemp) return false;

    // float searchWidth = searchTemp ? searchTemp->getContentSize().width : 120.0f;
    float searchWidth = searchTemp->getContentSize().width;
    /*
        v11->setPosition_0(v8, v12);
        v113 = 26112;
        v114 = -1;
        v8->setColor(&v8->cocos2d::CCRGBAProtocol, (const cocos2d::ccColor3B *)&v113);
        v14 = (cocos2d::CCMenu::create(v13);
        a1->addChild_1(a1, v14);
        v15 = cocos2d::CCSprite::createWithSpriteFrameName("GJ_searchBtn_001.png");
        v16 = fmaxf(0.89999998, (float)(v118 - 100.0) / (float)((float)(v15->m_obRect.size.width * 0.80000001) + 360.0));
        if ( v16 > 1.0 )
            v16 = 1.0;
        v17 = v16 * 90.0;
        cocos2d::CCPoint::CCPoint(&v116, v118 * 0.5, v119 * 0.5);
        cocos2d::CCNode::convertToNodeSpace(v14, &v121);
    */
    float scaleF = fmaxf(
        0.89999998f,
        (ws.width - 100.f) / (searchWidth * 0.80000001f + 360.0f)
    );
    log::info("{}", scaleF);
    // v16 = fmaxf(0.89999998, (float)(v118 - 100.0) / (float)((float)(v15->m_obRect.size.width * 0.80000001) + 360.0));
    // like what the actual fuck
    scaleF = std::min(scaleF, 1.0f) - 0.006725f;

    float buttonScale = 0.8f * scaleF;
    float spacing = scaleF * 90.f;

    log::info(
        "width={} searchWidth={} scaleF={} buttonScale={} spacing={}",
        ws.width,
        searchWidth,
        scaleF,
        buttonScale,
        spacing
    );

    // now its time to add my own additions
    struct bi {
        const char* frame;
        SEL_MenuHandler sel; // selector
        const char* nodeid = nullptr; // node id
        bool gs = false; // grayscale
        bool iQ = false; // isQuests
        bool iS = false; // isSearch
    };

    bi buttons[15] = {
        {"GJ_createBtn_001.png",        menu_selector(RECreatorLayer::onMyLevels), "create-button"},
        {"GJ_savedBtn_001.png",         menu_selector(RECreatorLayer::onSavedLevels), "saved-button"},
        {"GJ_highscoreBtn_001.png",     menu_selector(RECreatorLayer::onLeaderboards), "scores-button"},
        {"GJ_challengeBtn_001.png",     menu_selector(RECreatorLayer::onChallenge), "quests-button", false, true},
        {"GJ_versusBtn_001.png",        menu_selector(RECreatorLayer::onMultiplayer), "versus-button", true},
        {"GJ_mapBtn_001.png",           menu_selector(RECreatorLayer::onAdventureMap), "map-button", true},
        {"GJ_dailyBtn_001.png",         menu_selector(RECreatorLayer::onDailyLevel), "daily-button"},
        {"GJ_weeklyBtn_001.png",        menu_selector(RECreatorLayer::onWeeklyLevel), "weekly-button"},
        {"GJ_eventBtn_001.png",         menu_selector(RECreatorLayer::onEventLevel), "event-button"},
        {"GJ_gauntletsBtn_001.png",     menu_selector(RECreatorLayer::onGauntlets), "gauntlet-button"},
        {"GJ_featuredBtn_001.png",     menu_selector(RECreatorLayer::onFeaturedLevels), "featured-button"},
        {"GJ_listsBtn_001.png",        menu_selector(RECreatorLayer::onTopLists), "lists-button"},
        {"GJ_pathsBtn_001.png",        menu_selector(RECreatorLayer::onPaths), "paths-button"},
        {"GJ_mapPacksBtn_001.png",     menu_selector(RECreatorLayer::onMapPacks), "map-packs-button"},
        {"GJ_searchBtn_001.png",       menu_selector(RECreatorLayer::onOnlineLevels), "search-button", false, false, true}
    };

    for (int i = 0; i < 15; ++i) {
        // auto spr = CCSprite::createWithSpriteFrameName(buttons[i].frame);
        CCSprite* spr;
        if (buttons[i].gs) {
            auto gray = CCSpriteGrayscale::createWithSpriteFrameName(
                buttons[i].frame
            );

            #ifdef GEODE_IS_WINDOWS
            gray->m_luminance._Elems[0] = 0.33f;
            gray->m_luminance._Elems[1] = 0.33f;
            gray->m_luminance._Elems[2] = 0.33f;
            #else
            gray->setEvenLuminance(1.0f);
            #endif

            gray->setColor({175, 175, 175});

            spr = gray;
        } else {
            spr = CCSprite::createWithSpriteFrameName(buttons[i].frame);
        }

        if (!spr) continue;

        spr->setScale(buttonScale);
        auto btn = CCMenuItemSpriteExtra::create(
            spr, nullptr, this, buttons[i].sel
        );
        if (buttons[i].nodeid) {
            btn->setID(buttons[i].nodeid);
        }

        int col = i % 5;
        int row = i / 5;

        auto center = CCPoint{
            ws.width * 0.5f,
            ws.height * 0.5f
        };

        auto menuCenter = menu->convertToNodeSpace(center);

        CCPoint offset{
            (col - 1.5f) * spacing - spacing * 0.5f,
            -(floorf(row) - 1.0f) * spacing
        };

        btn->setPosition(menuCenter + offset);
        menu->addChild(btn);

        if (buttons[i].iQ) {
            m_questsSprite = spr;
            this->checkQuestsStatus();
        }

        if (buttons[i].iS && GameManager::sharedState()->getGameVariable("0077")) {
            // constexpr auto OnlyAllowFeatured = "0077";
            // aka parental controls
            btn->setEnabled(false);
            btn->setVisible(false);
        }
    }

    Helper::sideart(this, {0.0f, 0.0f}, {dir->getScreenLeft() - 1.0f, dir->getScreenBottom() - 1.0f}, false, false, 1, "bottom-left-corner");
    Helper::sideart(this, {0.0f, 1.0f}, {dir->getScreenLeft() - 1.0f, dir->getScreenTop() + 1.0f}, false, true, -1, "top-left-corner");

    int diamonds = GameStatsManager::sharedState()->getStat("13");
    const char* vaultf = (diamonds >= 50) ? "GJ_lock_open_001.png" : "GJ_lockGray_001.png";

    auto vaultMenu = CCMenu::create();
    vaultMenu->setID("top-right-menu");
    this->addChild(vaultMenu);

    auto vault = CCSprite::createWithSpriteFrameName(vaultf);
    auto vaultB = CCMenuItemSpriteExtra::create(vault, nullptr, this, menu_selector(RECreatorLayer::onSecretVault));
    vaultB->setID("vault-button");
    vaultB->setPosition(vaultMenu->convertToNodeSpace({ws.width - 22.0f,ws.height - 18.0f}));
    vaultMenu->addChild(vaultB);

    if (diamonds < 50) {
        float h = vault->getContentSize().height;
        float w = vault->getContentSize().width;

        auto icon = CCSprite::createWithSpriteFrameName("GJ_diamondsIcon_001.png");
        icon->setPosition({
            w * 0.5f + 9.0f,
            h * -0.3f - 1.0f
        });
        icon->setScale(0.7f);
        vault->addChild(icon);

        auto count = CCLabelBMFont::create("50", "bigFont.fnt");
        count->setPosition({
            w * 0.5f - 8.5f,
            h * -0.3f
        });
        count->setScale(0.4f);
        vault->addChild(count);
    }

    bool unlocked = GameManager::sharedState()->getUGV("5");
    const char* door; // = unlocked ? "secretDoorBtn_open_001.png" : "secretDoorBtn_closed_001.png";
    if (unlocked) {
        door = "secretDoorBtn_open_001.png";
    } else {
        door = "secretDoorBtn_closed_001.png";
    }

    auto doorMenu = CCMenu::create();
    doorMenu->setID("bottom-right-menu");
    this->addChild(doorMenu);

    m_secretDoorSprite = CCSprite::createWithSpriteFrameName(door);

    auto doorbtn = CCMenuItemSpriteExtra::create(m_secretDoorSprite, nullptr, this, menu_selector(RECreatorLayer::onTreasureRoom));
    doorbtn->setID("treasure-room-button");
    doorbtn->setPosition(doorMenu->convertToNodeSpace({ws.width - 22.0f, 24.0f}));
    doorMenu->addChild(doorbtn);

    auto backspr = CCSprite::createWithSpriteFrameName("GJ_arrow_03_001.png");
    auto back = CCMenuItemSpriteExtra::create(
        backspr, nullptr, this, menu_selector(RECreatorLayer::onBack)
    );
    back->setID("back-button");

    auto backmenu = CCMenu::create(back, nullptr);
    backmenu->setPosition({dir->getScreenLeft() + 24.0f, dir->getScreenTop() - 23.0f});
    backmenu->setID("exit-menu");

    this->addChild(backmenu, 1);

    auto bottomleft = CCMenu::create();
    bottomleft->setID("bottom-left-menu");
    this->addChild(bottomleft);

    if (PlatformToolbox::isControllerConnected()) {
        GameToolbox::addBackButton(this, back);
    }

    if (GameLevelManager::sharedState()) GameLevelManager::sharedState()->updateUserScore();
    return true;
}
