#include <Geode/Geode.hpp>
#include <Geode/modify/CCMenuItem.hpp>
#include <random>
#include <user95401.gif-sprites/include/CCGIFAnimatedSprite.hpp>

using namespace geode::prelude;

class $modify(ExplodingItem, CCMenuItem) {
    void activate() {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(1, 2);

        int randomValue = dis(gen);

        if (randomValue == 1) {
            auto audioEngine = FMODAudioEngine::sharedEngine();

            audioEngine->playEffect("explode.wav"_spr);

            auto explosionSprite = CCGIFAnimatedSprite::create("explosion.gif"_spr);
            explosionSprite->setPosition(getPosition());
            explosionSprite->setScale(getScale());
            explosionSprite->setLoop(false);
            getParent()->addChild(explosionSprite);

            explosionSprite->runAction(
                CCSequence::createWithTwoActions(
                    CCDelayTime::create(1.5f),
                    CCCallFunc::create(explosionSprite, callfunc_selector(CCNode::removeFromParentAndCleanup))
                )
            );

            removeFromParentAndCleanup(true);
        } else {
            activate();
        }
    }
};