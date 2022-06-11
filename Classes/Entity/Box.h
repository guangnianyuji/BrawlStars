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

	float getofferDamage() const { return m_offerDamage; }

	float getofferBlood() const { return m_offerBlood; }

private:

	void setPhyBody();

	//箱子的身体
	Sprite* m_Body;

	bool init() override;

	bool m_isDead;

	float m_offerDamage;

	float m_offerBlood;
};


#endif // !__BOX_H__