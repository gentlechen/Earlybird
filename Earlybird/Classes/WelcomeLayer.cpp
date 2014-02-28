#include "WelcomeLayer.h"

WelcomeLayer::WelcomeLayer(){};

WelcomeLayer::~WelcomeLayer(){};

bool WelcomeLayer::init(){
	if(!Layer::init()){
		return false;
	}
	//get the origin point of the X-Y zhou, and the visiable size of the screen
	Size visiableSize = Director::getInstance()->getVisibleSize();
	Point origin = Director::getInstance()->getVisibleOrigin();

	// add background to current scene
	Sprite *background = Sprite::createWithSpriteFrame(AtlasLoader::getInstance()->getSpriteFrameByName("bg_day"));
	background->setAnchorPoint(Point::ZERO);
	background->setPosition(Point::ZERO);
	this->addChild(background);

	//add the word game-title to the current scene
	Sprite *title  = Sprite::createWithSpriteFrame(AtlasLoader::getInstance()->getSpriteFrameByName("title"));
	float titleWidth = title->getContentSize().width;
	float titleHeight = title->getContentSize().height;
	title->setPosition(Point(origin.x + visiableSize.width/2 , (visiableSize.height * 5) / 7));
	this->addChild(title);

	//add the start-menu to the current scene
	Sprite *startButton = Sprite::createWithSpriteFrame(AtlasLoader::getInstance()->getSpriteFrameByName("button_play"));
	Sprite *activeStartButton = Sprite::createWithSpriteFrame(AtlasLoader::getInstance()->getSpriteFrameByName("button_play"));
	activeStartButton->setPositionY(5);
	auto menuItem  = MenuItemSprite::create(startButton,activeStartButton,NULL,CC_CALLBACK_1(WelcomeLayer::menuStartCallback, this));
	menuItem->setPosition(Point(origin.x + visiableSize.width/2 ,origin.y + visiableSize.height*2/5));

    auto menu = Menu::create(menuItem,NULL);
	menu->setPosition(Point(origin.x ,origin.y));
	this->addChild(menu,1);

	//create a bird and set the position in the center of the screen
	Sprite* bird = Sprite::createWithSpriteFrame(AtlasLoader::getInstance()->getSpriteFrameByName("bird2_0"));
	bird->setPosition(Point(origin.x + visiableSize.width / 2,origin.y + visiableSize.height*3/5 - 7));

	//create the bird animation
	Animation* animation = Animation::create();
	animation->setDelayPerUnit(0.1f);
	animation->addSpriteFrame(AtlasLoader::getInstance()->getSpriteFrameByName("bird2_0"));
	animation->addSpriteFrame(AtlasLoader::getInstance()->getSpriteFrameByName("bird2_1"));
	animation->addSpriteFrame(AtlasLoader::getInstance()->getSpriteFrameByName("bird2_2"));
	//bind the animate to the bird
	Animate* animate = Animate::create(animation);

	ActionInterval *fly = CCMoveBy::create(0.4f,Point(0, 14));
	ActionInterval *flyBack= fly->reverse();
	Sequence *swing = Sequence::create(fly, flyBack, NULL);
	//Spawn *birdFly = Spawn::createWithTwoActions(swing, animate);
	bird->runAction(RepeatForever::create(animate));
	bird->runAction(RepeatForever::create(swing));
	this->addChild(bird);

	// Add the land
	this->land1 = Sprite::createWithSpriteFrame(AtlasLoader::getInstance()->getSpriteFrameByName("land"));
	this->land1->setAnchorPoint(Point::ZERO);
	this->land1->setPosition(Point::ZERO);
	this->addChild(this->land1, 4);

	this->land2 = Sprite::createWithSpriteFrame(AtlasLoader::getInstance()->getSpriteFrameByName("land"));
	this->land2->setAnchorPoint(Point::ZERO);
	this->land2->setPosition(this->land1->getContentSize().width - 2.0f, 0);
	this->addChild(this->land2, 0);

	this->schedule(schedule_selector(WelcomeLayer::scrollLand), 0.01f);

	//add the copyright-text to the current scne
	Sprite *copyright = Sprite::createWithSpriteFrame(AtlasLoader::getInstance()->getSpriteFrameByName("brand_copyright"));
	copyright->setPosition(Point(origin.x + visiableSize.width/2, origin.y + visiableSize.height/6));
	this->addChild(copyright, 10);

	return true;
}

void WelcomeLayer::scrollLand(float dt){
	this->land1->setPositionX(this->land1->getPositionX() - 2.0f);
	this->land2->setPositionX(this->land1->getPositionX() + this->land1->getContentSize().width - 2.0f);

	if(this->land2->getPositionX() == 0) {
		this->land1->setPositionX(0);
	}else if(this->land2->getPositionX() <= this->land1->getContentSize().width/2.0f){
		// Avoid the black line bug
		this->land2->setLocalZOrder(5);
	}else if(this->land2->getPositionX() > this->land1->getContentSize().width/2.0f) {
		// Avoid the black line bug
		this->land2->setLocalZOrder(0);
	}
}

void WelcomeLayer::menuStartCallback(Object *sender){

}
