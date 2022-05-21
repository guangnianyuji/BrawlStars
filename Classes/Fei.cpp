#include "Fei.h"


 Fei ::Fei(bool flag): Character()
{
	 m_FrontBody = Sprite::create("F/Ff1.png");
	 m_LeftBody = Sprite::create("F/Fl1.png");
	 m_RightBody = Sprite::create("F/Fr1.png");
	 m_BehindBody = Sprite::create("F/Fb1.png");

	 m_FrontMove = AnimationUtils::createAnimation("F","f");
	 m_BehindMove = AnimationUtils::createAnimation("F", "b");
	  m_LeftMove = AnimationUtils::createAnimation("F", "l");
	 m_RightMove = AnimationUtils::createAnimation("F", "r");
	
 }