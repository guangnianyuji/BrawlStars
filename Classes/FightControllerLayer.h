#ifndef __FIGHTCONTROLLERLAYER_H__
#define __FIGHTCONTROLLERLAYER_H__

#include "cocos2d.h"
#include "Math.h"

using namespace cocos2d;

class FightControllerLayer :public Layer
{

public:
	//�������Ʋ�
	static FightControllerLayer* create();

	//�����ƶ�ҡ�ˣ�����ҡ�ˣ����������¼���
	void startAllRockers(bool isStop);

	//ֹͣ�ƶ�ҡ�ˣ�����ҡ�ˣ�ȡ�������¼���
	void stopAllRockers();


	//�õ��ƶ�ҡ���Ƿ����ƶ�
	bool getMoveRockerIsMoving() const { return m_MoveRockerIsMoving; }

	//�õ��ƶ�ҡ���ƶ��ķ����
	float getMoveRockerAngle() const { return m_MoveRockerAngle; }

	//�õ���ͨ����ҡ���Ƿ����ƶ�
	bool getNormalAttackRockerIsMoving() const{ return m_NormalAttackRockerIsMoving; }

	//�õ���ͨ����ҡ���ƶ��ķ����
	float getNormalAttackRockerAngle() const{ return m_NormalAttackRockerAngle; }

	//�õ����й���ҡ���Ƿ����ƶ�
	bool getACERockerIsMoving() const { return m_ACERockerIsMoving; }

	//�õ����й���ҡ���ƶ��ķ����
	float getACERockerAngle() const { return m_ACERockerAngle; }

	//�õ���ͨ����״̬
	bool getNormalAttackState() const { return m_NormalAttackState; }

	//������ͨ����״̬
	void setNormalAttackState(bool state) {  m_NormalAttackState=state; }

	//�õ����й���״̬
	bool getACEState() const { return m_ACEState; }

	//���ô��й���״̬
	void setACEState(bool state) { m_ACEState = state; }

	


	


private:

	EventListenerTouchAllAtOnce* m_TouchListener;

	EventListenerKeyboard* m_KeyboardListener;

	//��ʼ��
	virtual bool init() override;	
	
	/* �����ƶ��͹���ҡ�� */
	void initMoveandAttackRocker();


	void initEventListener();

	//�ƶ�ҡ��

	//�ƶ�ҡ�˽ڵ�
	Sprite* m_MoveRockerBackgroundSprite;

	//�ƶ�ҡ�˱����ڵ�
	Sprite* m_MoveRockerSprite;

	//�ƶ�ҡ�˱���������
	Vec2 m_MoveRockerBackgroundPosition;

	//�ƶ�ҡ�˱����İ뾶
	float m_MoveRockerBackgroundRadius;

	//�ƶ�ҡ�˵�����
	Vec2 m_MoveRockerPosition;

	//�ƶ�ҡ�˵õ��ķ����
	float m_MoveRockerAngle;

    //�ƶ�ҡ���Ƿ��ƶ�
	bool m_MoveRockerIsMoving;

	//��ͨ����ҡ��
	
	//��ͨ����ҡ�˽ڵ�
	Sprite* m_NormalAttackRockerBackgroundSprite;

	//��ͨ����ҡ�˱����ڵ�
	Sprite* m_NormalAttackRockerSprite;

	//��ͨ����ҡ�˱���������
	Vec2 m_NormalAttackRockerBackgroundPosition;

	//��ͨ����ҡ�˱����İ뾶
	float m_NormalAttackRockerBackgroundRadius;

	//��ͨ����ҡ�˵�����
	Vec2 m_NormalAttackRockerPosition;

	//��ͨ����ҡ�˵õ��ķ����
	float m_NormalAttackRockerAngle;

	//�չ�ҡ���Ƿ��ƶ�
	bool m_NormalAttackRockerIsMoving;

	//�Ƿ�ʼ����
	bool m_NormalAttackState;

	//���й���ҡ��

	//���й���ҡ�˽ڵ�
	Sprite* m_ACERockerBackgroundSprite;

	//���й���ҡ�˱����ڵ�
	Sprite* m_ACERockerSprite;

	//���й���ҡ�˱���������
	Vec2 m_ACERockerBackgroundPosition;

	//���й���ҡ�˱����İ뾶
	float m_ACERockerBackgroundRadius;

	//���й���ҡ�˵�����
	Vec2 m_ACERockerPosition;

	//���й���ҡ�˵õ��ķ����
	float m_ACERockerAngle;
	
   //����ҡ���Ƿ��ƶ�
	bool m_ACERockerIsMoving;

	//�Ƿ�ʼ���й���
	bool m_ACEState;

	void update(float delta);

	//�����ƶ�ҡ����ָ�Ƕ�
	void updateMoveRad( );

};

#endif//__FIGHTCONTROLLERLAYER_H__