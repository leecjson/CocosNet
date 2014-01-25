#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "../../CocosNet/cocos-net.h"
USING_NS_CC;


class GameNetDelegate : public CCNetDelegate
{

public:
	GameNetDelegate();
	virtual ~GameNetDelegate();

	SINGLE_DELEGATE_INSTANCE_FUNC(GameNetDelegate);

	virtual void onMessageReceived(CCBuffer& oBuffer);
	virtual void onConnected();
	virtual void onConnectTimeout();
	virtual void onDisconnected();
	virtual void onExceptionCaught(CCSocketStatus eStatus);

public:
	void CS_Test();
	void CS_LargePackage();
};

class AlphaScene : public CCScene
{
public:
	virtual bool init();

	void onConnectClick(CCObject* pSender);
	void onDisconnectClick(CCObject* pSender);
	void onTestClick(CCObject* pSender);
	void onLargeDataClick(CCObject* pSender);
};

#endif // __HELLOWORLD_SCENE_H__
