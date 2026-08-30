#pragma once
#include <Geode/Geode.hpp>
using namespace geode::prelude;

namespace Helper {
    inline void sideart(CCNode* layer, CCPoint anchor, CCPoint pos, bool flipX, bool flipY, int zOrder, const char* node) {
        auto art = CCSprite::createWithSpriteFrameName("GJ_sideArt_001.png");
        if (!art) return;
        art->setAnchorPoint(anchor);
        art->setPosition(pos);
        art->setFlipX(flipX);
        art->setFlipY(flipY);
        art->setID(node);
        layer->addChild(art, zOrder);
    }

    inline bool s(std::string_view setting) {
        auto mod = geode::Mod::get();
        if (!mod->getSettingValue<bool>("themasterswitch")) return false;
        return mod->getSettingValue<bool>(setting);
    }
}