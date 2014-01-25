#include "HelloWorldScene.h"

GameNetDelegate::GameNetDelegate()
{

}

GameNetDelegate::~GameNetDelegate()
{
	
}


void GameNetDelegate::onMessageReceived(CCBuffer& oBuffer)
{
	CCLOG("onMessageReceived");

	switch( oBuffer.readInt() )
	{
	case 10:
		{
			CCLOG("%d", oBuffer.readInt());
			CCLOG("%d", oBuffer.readShort());
			CCLOG("%lld", oBuffer.readLongLong());
			CCLOG("%c", oBuffer.readChar());
			CCLOG("%f", oBuffer.readFloat());
			CCLOG("%lf", oBuffer.readDouble());
			CCLOG("%s", oBuffer.readLengthAndString().c_str());
		}
		break;
	case 5:
		{
			// large data
			CCLOG("large data length = %d", oBuffer.length());
		}
		break;
	}
}

void GameNetDelegate::onConnected()
{
	CCLOG("onConnected");
}

void GameNetDelegate::onConnectTimeout()
{
	CCLOG("onConnectTimeout");
}

void GameNetDelegate::onDisconnected()
{
	CCLOG("onDisconnected");
}

void GameNetDelegate::onExceptionCaught(CCSocketStatus eStatus)
{
	CCLOG("onExceptionCaught %d", (int)eStatus);
}

void GameNetDelegate::CS_Test()
{
	CCBuffer buffer;
	buffer.writeInt(10);
	buffer.writeLongLong(999999999L);
	buffer.writeFloat(77.7f);
	buffer.writeDouble(99.9);
	buffer.writeChar('h');
	buffer.writeLengthAndString("hahahahaha");

	this->send(&buffer);
}

void GameNetDelegate::CS_LargePackage()
{
	CCBuffer buffer;
	buffer.writeInt(5);

	this->send(&buffer);
}



bool AlphaScene::init()
{
	CCScene::init();

	CCMenuItemFont* pConnect = CCMenuItemFont::create("Connect", this, menu_selector(AlphaScene::onConnectClick));
	pConnect->setFontSize(30);
	pConnect->setPosition(ccp(200, 200));

	CCMenuItemFont* pDisconnect = CCMenuItemFont::create("Disconnect", this, menu_selector(AlphaScene::onDisconnectClick));
	pDisconnect->setFontSize(30);
	pDisconnect->setPosition(ccp(350, 200));

	CCMenuItemFont* pLargeData = CCMenuItemFont::create("LargeDataTest", this, menu_selector(AlphaScene::onLargeDataClick));
	pLargeData->setFontSize(30);
	pLargeData->setPosition(ccp(500, 300));

	CCMenuItemFont* pTest = CCMenuItemFont::create("Test", this, menu_selector(AlphaScene::onTestClick));
	pTest->setFontSize(30);
	pTest->setPosition(ccp(500, 200));

	CCMenu* pMenu = CCMenu::create(pConnect, pDisconnect, pTest, pLargeData, NULL);
	pMenu->setPosition(CCPointZero);
	addChild(pMenu);

	//test frame 
	CCSprite* picon = CCSprite::create("Icon.png");
	picon->setPosition(ccp(150, 400));

	CCMoveBy* pMoveRight = CCMoveBy::create(0.5f, ccp(500, 0));
	CCMoveBy* pMoveLeft = CCMoveBy::create(0.5f, ccp(-500, 0));
	CCSequence* pSeq = CCSequence::create(pMoveRight, pMoveLeft, NULL);
	picon->runAction(CCRepeatForever::create(pSeq));


	addChild(picon);
	
	return true;
}

void AlphaScene::onConnectClick(CCObject* pSender)
{
	CCInetAddress oAddres;
	oAddres.setIp("192.168.0.100");
	oAddres.setPort(7789);

	GameNetDelegate::sharedDelegate()->setInetAddress(oAddres);
	GameNetDelegate::sharedDelegate()->connect();
}

void AlphaScene::onDisconnectClick(CCObject* pSender)
{
	GameNetDelegate::sharedDelegate()->disconnect();
}

void AlphaScene::onTestClick(CCObject* pSender)
{
	GameNetDelegate::sharedDelegate()->CS_Test();
}

void AlphaScene::onLargeDataClick(CCObject* pSender)
{
	GameNetDelegate::sharedDelegate()->CS_LargePackage();
}