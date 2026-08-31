#pragma once
#include <Geode/Geode.hpp>
#include <Geode/modify/MenuLayer.hpp>

using namespace geode::prelude;

class $modify(REMenuLayer, MenuLayer) {
    void FLAlert_Clicked(FLAlertLayer* layer, bool btn2);
    void endGame();
    void firstNetworkTest();
    void googlePlaySignedIn();
    void keyBackClicked();
    void keyDown(cocos2d::enumKeyCodes key, double timestamp);
};