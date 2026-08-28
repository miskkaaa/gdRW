#pragma once
#include <Geode/Geode.hpp>
#include <Geode/modify/CreatorLayer.hpp>

using namespace geode::prelude;

class $modify(RECreatorLayer, CreatorLayer) {
    bool init();

    void checkQuestsStatus();
    void dialogClosed(DialogLayer* layer);
    void keyBackClicked();
    void onBack(CCObject* sender);
    void onAdventureMap(CCObject* sender);
    void onChallenge(CCObject* sender);
    void onDailyLevel(CCObject* sender);
    void onEventLevel(CCObject* sender);
    void onFeaturedLevels(CCObject* sender);
    void onGauntlets(CCObject* sender);

    CCScene* scene();
    CreatorLayer* create();
};