#include"Character.h"

bool Character::operator==(Character& aCharacter)
{
	return this->m_Name == aCharacter.m_Name;
}


Fei::Fei() : Character()
{
	m_Name = "F";
	m_Speed = 720;
	m_BloodVolume = 200.0f;
	m_NormalAttackDamage = 20;
}
Yu::Yu() : Character()
{
	m_Name = "Y";
	m_Speed = 720;
	m_BloodVolume = 200.0f;
	m_NormalAttackDamage = 20;
}
Jide::Jide() : Character()
{
	m_Name = "J";
	m_Speed = 720;
	m_BloodVolume = 200.0f;
	m_NormalAttackDamage = 20;
}
Lin::Lin() : Character()
{
	m_Name = "L";
	m_Speed = 720;
	m_BloodVolume = 200.0f;
	m_NormalAttackDamage = 20;
}

Nothing::Nothing():Character()
{
	m_Name = "Nothing";
}