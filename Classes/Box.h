#ifndef __BOX_H__
#define __BOX_H__

#include "Entity.h"

class Box :public Entity
{
public:
	static Box* create();

	bool isDead() const { return m_isDead; }

	void setisDead(bool isDead) { m_isDead = isDead; }

	virtual void beAttacked(const float& Damage) override;

	virtual void Death()override;

	float getofferSpeed() const { return m_offerSpeed; }

	float getofferBlood() const { return m_offerBlood; }

private:
	//���ӵ�����
	Sprite* m_Body;

	bool init() override;

	bool m_isDead;

	float m_offerSpeed;

	float m_offerBlood;
};


#endif // !__BOX_H__