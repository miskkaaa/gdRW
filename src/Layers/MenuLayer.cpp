#include "../Helpers.hpp"
#include "../includes/MenuLayer.hpp"

void REMenuLayer::FLAlert_Clicked(FLAlertLayer* layer, bool btn2) {
    if (!btn2) return;

    switch (layer->getTag()) {
        case 0: { // quit
            auto app = AppDelegate::get();
            app->trySaveGame(true);
            app->showLoadingCircle(false, true, true);

            auto del = CCDelayTime::create(0.5f);
            auto cb = CCCallFunc::create(this, callfunc_selector(REMenuLayer::endGame));
            auto seq = CCSequence::create(del, cb, nullptr);
            this->runAction(seq);
            break;
        } case 1: { // game center
            auto gm = GameManager::sharedState();
            gm->setGameVariable("0034", true);
            PlatformToolbox::activateGameCenter();

            if (PlatformToolbox::isLocalPlayerAuthenticated()) {
                if (GameManager::sharedState()->getGameVariable("0034")) {
                    GameManager::sharedState()->syncPlatformAchievements();
                    PlatformToolbox::showAchievements();
                } else {
                    this->showGCQuestion();
                }
            }
            break;
        } case 2: { // i actually dont know what this is
            auto url = fmt::format("https://www.robtopgames.com/download/gj{}",0);
            CCApplication::sharedApplication()->openURL(url.c_str()); // idk if i should use c_str
            break;
        } case 3: { // newgrounds
            cocos2d::CCApplication::sharedApplication()->openURL("https://www.newgrounds.com/audio");
            break;
        }

        default:
            break;
    }
}

void REMenuLayer::endGame() {
    CCDirector::sharedDirector()->end();
}

void REMenuLayer::firstNetworkTest() {
    auto gml = GameLevelManager::sharedState();
    gml->performNetworkTest();
}

void REMenuLayer::googlePlaySignedIn() {
    if (!m_gpSprite) return;
    if (PlatformToolbox::isSignedInGooglePlay()) {
        auto frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("GJ_gpgBtn_001.png");
        m_gpSprite->setDisplayFrame(frame);
        CCDirector::sharedDirector()
            ->getScheduler()
            ->scheduleSelector(
                schedule_selector(MenuLayer::syncPlatformAchievements),
                this,
                0.0f,
                kCCRepeatForever,
                0.0f,
                false
            );
    } else {
        auto frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("GJ_gpgBtn_001.png");
        m_gpSprite->setDisplayFrame(frame);
    }
}

void REMenuLayer::keyBackClicked() {
    MenuLayer::onQuit(this);
}

void REMenuLayer::keyDown(cocos2d::enumKeyCodes key, double timestamp) {
    log::info("gay");
    switch (key) {
        case CONTROLLER_X:
            this->onGarage(nullptr);
            break;

        case CONTROLLER_Y:
            this->onCreator(nullptr);
            break;

        case CONTROLLER_Start:
        case KEY_Enter:
        case KEY_Space:
            this->onPlay(nullptr);
            break;

        case CONTROLLER_Down: {
            auto options = OptionsLayer::create();
            this->addChild(options, 100);
            options->showLayer(false);
            break;
        }

        default:
            CCLayer::keyDown(key, timestamp);
            break;
    }
}
