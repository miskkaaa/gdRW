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

#include "../Helpers.hpp"

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
        CreatorLayer::onChallenge(sender);
        return;
    }
    auto page = GJPromoPopup::create("promo_boom.png");
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

CCScene* RECreatorLayer::scene() {
    if (!Helper::s("CLscene")) {
        CreatorLayer::scene();
        return nullptr;
    }
    auto scene = CCScene::create();
    if (!scene) return nullptr;

    auto layer = RECreatorLayer::create();
    if (!layer) return nullptr;

    scene->addChild(layer);
    return scene;
}

CreatorLayer* RECreatorLayer::create() {
    if (!Helper::s("CLcreate")) {
        CreatorLayer::create();
        return nullptr;
    }
    auto ret = new CreatorLayer();
    log::info("test");
    if (ret && ret->init()) {
        ret->autorelease();
        return ret;
    }
    delete ret;
    return nullptr;
}

bool RECreatorLayer::init() {
    if (!Helper::s("CLinit")) {
        CreatorLayer::init();
        return true;
    }
    if (!CCLayer::init()) return false;
    this->setKeypadEnabled(true);
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
    this->addChild(bg, -2);

    auto menu = CCMenu::create();
    this->addChild(menu);

    auto searchTemp = CCSprite::createWithSpriteFrameName("GJ_searchBtn_001.png");
    if (!searchTemp) return false;

    // float searchWidth = searchTemp ? searchTemp->getContentSize().width : 120.0f;
    float searchWidth = searchTemp->getContentSize().width;
    float scaleF = std::max(0.9f, (ws.width - 100.f) / (searchWidth * 0.8f + 360.f));
    // v16 = fmaxf(0.89999998, (float)(v118 - 100.0) / (float)((float)(v15->m_obRect.size.width * 0.80000001) + 360.0));
    // like what the actual fuck
    scaleF = std::min(scaleF, 1.0f);

    if (scaleF > 1.0f) scaleF = 1.0f;
    float spacing = scaleF * 90.f;

    log::info(
        "width={} searchWidth={} scaleF={} spacing={}",
        ws.width,
        searchWidth,
        scaleF,
        spacing
    );

    // now its time to add my own additions
    struct bi {
        const char* frame;
        SEL_MenuHandler sel; // selector
        bool gs = false; // grayscale
        bool iQ = false; // isQuests
        bool iS = false; // isSearch
    };

    bi buttons[15] = {
        {"GJ_createBtn_001.png",        menu_selector(CreatorLayer::onMyLevels)},
        {"GJ_savedBtn_001.png",         menu_selector(CreatorLayer::onSavedLevels)},
        {"GJ_highscoreBtn_001.png",     menu_selector(CreatorLayer::onLeaderboards)},
        {"GJ_challengeBtn_001.png",     menu_selector(RECreatorLayer::onChallenge), false, true},
        {"GJ_versusBtn_001.png",        menu_selector(CreatorLayer::onMultiplayer), true},
        {"GJ_mapBtn_001.png",           menu_selector(RECreatorLayer::onAdventureMap), true},
        {"GJ_dailyBtn_001.png",         menu_selector(RECreatorLayer::onDailyLevel)},
        {"GJ_weeklyBtn_001.png",        menu_selector(CreatorLayer::onWeeklyLevel)},
        {"GJ_eventBtn_001.png",         menu_selector(CreatorLayer::onEventLevel)},
        {"GJ_gauntletsBtn_001.png",     menu_selector(CreatorLayer::onGauntlets)},
        {"GJ_featuredBtn_001.png",     menu_selector(CreatorLayer::onFeaturedLevels)},
        {"GJ_listsBtn_001.png",        menu_selector(CreatorLayer::onTopLists)},
        {"GJ_pathsBtn_001.png",        menu_selector(CreatorLayer::onPaths)},
        {"GJ_mapPacksBtn_001.png",     menu_selector(CreatorLayer::onMapPacks)},
        {"GJ_searchBtn_001.png",       menu_selector(CreatorLayer::onOnlineLevels), false, false, true}
    };

    for (int i = 0; i < 15; ++i) {
        // auto spr = CCSprite::createWithSpriteFrameName(buttons[i].frame);
        CCSprite* spr;
        if (buttons[i].gs) {
            auto gray = CCSpriteGrayscale::createWithSpriteFrameName(
                buttons[i].frame
            );

            gray->m_luminance._Elems[0] = 0.33f;
            gray->m_luminance._Elems[1] = 0.33f;
            gray->m_luminance._Elems[2] = 0.33f;

            gray->setColor({175, 175, 175});

            spr = gray;
        } else {
            spr = CCSprite::createWithSpriteFrameName(buttons[i].frame);
        }

        if (!spr) continue;

        spr->setScale(scaleF);
        auto btn = CCMenuItemSpriteExtra::create(
            spr, nullptr, this, buttons[i].sel
        );

        int col = i % 5;
        int row = i / 5;

        float posX = (col - 2.0f) * spacing;
        float posY = -(row - 1.0f) * spacing;

        btn->setPosition(menu->convertToNodeSpace({ws.width * 0.5f + posX, ws.height * 0.5f + posY}));
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

    Helper::sideart(this, {0.0f, 0.0f}, {dir->getScreenLeft() - 1.0f, dir->getScreenBottom() - 1.0f}, false, false, 1);
    Helper::sideart(this, {0.0f, 1.0f}, {dir->getScreenLeft() - 1.0f, dir->getScreenTop() + 1.0f}, false, true, -1);

    int diamonds = GameStatsManager::sharedState()->getStat("13");
    const char* vaultf = (diamonds >= 50) ? "GJ_lock_open_001.png" : "GJ_lock_001.png";
    auto vault = CCSprite::createWithSpriteFrameName(vaultf);
    auto vaultB = CCMenuItemSpriteExtra::create(
        vault, nullptr, this, menu_selector(CreatorLayer::onSecretVault)
    );
    vaultB->setPosition(menu->convertToNodeSpace({ws.width - 22.0f, ws.height - 18.0f}));
    menu->addChild(vaultB);

    if (diamonds > 50) {
        float h = vault->getContentSize().height;
        float w = vault->getContentSize().width;

        auto icon = CCSprite::createWithSpriteFrameName("GJ_diamondsIcon_001.png");
        icon->setPosition({
            w * 0.5f + 9.0f,
            h * 0.5f - 23.0f
        });
        icon->setScale(0.8f);
        vault->addChild(icon);

        auto count = CCLabelBMFont::create("50", "bigFont.fnt");
        count->setPosition({
            w * 0.5f - 8.5f,
            h * 0.5f - 22.0f
        });
        count->setScale(0.5f);
        vault->addChild(count);
    }

    bool unlocked = GameManager::sharedState()->getUGV("1");
    const char* door = unlocked ? "secretDoorBtn_open_001.png" : "secretDoorBtn_closed_001.png";
    m_secretDoorSprite = CCSprite::createWithSpriteFrameName(door);

    auto doorbtn = CCMenuItemSpriteExtra::create(
        m_secretDoorSprite, nullptr, this, menu_selector(CreatorLayer::onTreasureRoom)
    );
    doorbtn->setPosition(menu->convertToNodeSpace({ws.width - 22.0f, 24.0f}));
    menu->addChild(doorbtn);

    auto backspr = CCSprite::createWithSpriteFrameName("GJ_arrow_03_001.png");
    auto back = CCMenuItemSpriteExtra::create(
        backspr, nullptr, this, menu_selector(RECreatorLayer::onBack)
    );

    auto backmenu = CCMenu::create(back, nullptr);
    backmenu->setPosition({dir->getScreenLeft() + 24.0f, dir->getScreenTop() - 23.0f});
    this->addChild(backmenu, 1);

    GameToolbox::addBackButton(this, back);

    if (GameLevelManager::sharedState()) GameLevelManager::sharedState()->updateUserScore();
    return true;
}