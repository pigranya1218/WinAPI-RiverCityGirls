#include "stdafx.h"
#include "AttackState.h"

void AttackState::enter(Player & player)
{
	switch (_skill)
	{
	case ATTACK_SKILL:: QC1:
		_img = IMAGE_MANAGER->findImage("Kyoko_attack1");
		_ani = new Animation;
		_ani->init(_img->getWidth(), _img->getHeight(), _img->getMaxFrameX(), _img->getMaxFrameY());
		if (player.getDirection() == DIRECTION::RIGHT)
		{
			_ani->setPlayFrame(0, 6, false, false);
		}
		else
		{
			_ani->setPlayFrame(6, 12, false, false);
		}

		_ani->setFPS(15);
		_ani->start();
		break;
	case ATTACK_SKILL::RUN_QC:
		_img = IMAGE_MANAGER->findImage("Kyoko_backelbow");
		_ani = new Animation;
		_ani->init(_img->getWidth(), _img->getHeight(), _img->getMaxFrameX(), _img->getMaxFrameY());
		if (player.getDirection() == DIRECTION::RIGHT)
		{
			_ani->setPlayFrame(0, 7, false, false);
		}
		else
		{
			_ani->setPlayFrame(7, 14, false, false);
		}

		_ani->setFPS(15);
		_ani->start();
		break;
	case ATTACK_SKILL::JUMP_QC:
		
		_img = IMAGE_MANAGER->findImage("Kyoko_buttbump");
		_ani = new Animation;
		_ani->init(_img->getWidth(), _img->getHeight(), _img->getMaxFrameX(), _img->getMaxFrameY());
		if (player.getDirection() == DIRECTION::RIGHT)
		{
			_ani->setPlayFrame(0, 10, false, false);
		}
		else
		{
			_ani->setPlayFrame(10, 20, false, false);
		}

		_ani->setFPS(15);
		_ani->start();
		
		break;
	case ATTACK_SKILL::HC:
		_img = IMAGE_MANAGER->findImage("Kyoko_axekick");
		_ani = new Animation;
		_ani->init(_img->getWidth(), _img->getHeight(), _img->getMaxFrameX(), _img->getMaxFrameY());
		if (player.getDirection() == DIRECTION::RIGHT)
		{
			_ani->setPlayFrame(0, 13, false, false);
		}
		else
		{
			_ani->setPlayFrame(13, 26, false, false);
		}

		_ani->setFPS(15);
		_ani->start();
		break;
	case ATTACK_SKILL::RUN_HC:
		_img = IMAGE_MANAGER->findImage("Kyoko_dive");
		_ani = new Animation;
		_ani->init(_img->getWidth(), _img->getHeight(), _img->getMaxFrameX(), _img->getMaxFrameY());
		if (player.getDirection() == DIRECTION::RIGHT)
		{
			_ani->setPlayFrame(0, 21, false, false);
		}
		else
		{
			_ani->setPlayFrame(21, 42, false, false);
		}

		_ani->setFPS(15);
		_ani->start();
		break;
	case ATTACK_SKILL::JUMP_HC:
		_img = IMAGE_MANAGER->findImage("Kyoko_airstep");
		_ani = new Animation;
		_ani->init(_img->getWidth(), _img->getHeight(), _img->getMaxFrameX(), _img->getMaxFrameY());
		if (player.getDirection() == DIRECTION::RIGHT)
		{
			_ani->setPlayFrame(0, 11, false, false);
		}
		else
		{
			_ani->setPlayFrame(11, 22, false, false);
		}

		_ani->setFPS(15);
		_ani->start();
		break;
	}
	

}

PlayerState * AttackState::update(Player & player)
{
	Vector3 moveDir;
	moveDir.x = 0;
	moveDir.y = 0;
	moveDir.z = 0;

	_ani->frameUpdate(TIME_MANAGER->getElapsedTime());

	float lastPlayerY = player.getPosition().y;

	
	

		switch (_skill)
		{
		case ATTACK_SKILL::QC1:
		{
			_initTime += TIME_MANAGER->getElapsedTime();
			if (!_ani->isPlay())
			{
				if (KEY_MANAGER->isStayKeyDown(VK_RIGHT) || KEY_MANAGER->isStayKeyDown(VK_LEFT))return new WalkState;
				else return new IdleState;
			}
			
			/*CAMERA_MANAGER->rectangle(viewRc, D2D1::ColorF::Enum::Red, 1, 1);
			CAMERA_MANAGER->drawShadow(player.getPosition(), player.getSize());*/
			
			if (2 <= _ani->getPlayIndex() && _ani->getPlayIndex() <= 3)
			{
				Vector3 position = player.getPosition();
				if (player.getDirection() == DIRECTION::RIGHT)
				{
					attackRc = FloatRect(position.x + 20, position.y - 45,
						position.x + 130, position.y + 10);
				}
				else
				{
					attackRc = FloatRect(position.x - 130, position.y - 45,
						position.x - 20, position.y + 10);
				}
				
				viewRc = FloatRect(attackRc.left, position.z + attackRc.top,
					attackRc.right, position.z + attackRc.bottom);
				player.attack(attackRc, 10, ATTACK_TYPE::HIT);
			}
			
			if (_initTime>=0.2 &&KEY_MANAGER->isOnceKeyDown('Z'))
			{
				_img = IMAGE_MANAGER->findImage("Kyoko_attack2");

				_ani->init(_img->getWidth(), _img->getHeight(), _img->getMaxFrameX(), _img->getMaxFrameY());
				if (player.getDirection() == DIRECTION::RIGHT)
				{
					_ani->setPlayFrame(0, 7, false, false);
				}
				else
				{
					_ani->setPlayFrame(7, 14, false, false);
				}
				_ani->setFPS(15);
				_ani->start();

				
				_skill = ATTACK_SKILL::QC2;
				_initTime = 0;
			}

		}

		break;
		case ATTACK_SKILL::QC2:
			//CAMERA_MANAGER->rectangle(FloatRect(300, 300, 800, 800), D2D1::ColorF::Enum::Red, 1, 20);
			if (!_ani->isPlay())
			{
				if (KEY_MANAGER->isStayKeyDown(VK_RIGHT) || KEY_MANAGER->isStayKeyDown(VK_LEFT))return new WalkState;
				else return new IdleState;
			}
			else
			{
				if (2 <= _ani->getPlayIndex() && _ani->getPlayIndex() <= 4)
				{
					Vector3 position = player.getPosition();
					if (player.getDirection() == DIRECTION::RIGHT)
					{
						attackRc = FloatRect(position.x + 30, position.y - 60,
							position.x + 140, position.y + 70);
					}
					else
					{
						attackRc = FloatRect(position.x - 140, position.y - 60,
							position.x - 30, position.y + 70);
					}

					viewRc = FloatRect(attackRc.left, position.z + attackRc.top,
						attackRc.right, position.z + attackRc.bottom);
					player.attack(attackRc, 10, ATTACK_TYPE::HIT);
				}

				_initTime += TIME_MANAGER->getElapsedTime();
				
				if (_initTime>=0.25 &&KEY_MANAGER->isOnceKeyDown('Z'))
				{
					_img = IMAGE_MANAGER->findImage("Kyoko_attack3");

					_ani->init(_img->getWidth(), _img->getHeight(), _img->getMaxFrameX(), _img->getMaxFrameY());
					if (player.getDirection() == DIRECTION::RIGHT)
					{
						_ani->setPlayFrame(0, 7, false, false);
					}
					else
					{
						_ani->setPlayFrame(7, 14, false, false);
					}
					_ani->setFPS(15);
					_ani->start();
					_initTime = 0;
					_skill = ATTACK_SKILL::QC3;

				}
				
					

			}
				break;
			case ATTACK_SKILL::QC3:
			    if (!_ani->isPlay())
				{
					if (KEY_MANAGER->isStayKeyDown(VK_RIGHT) || KEY_MANAGER->isStayKeyDown(VK_LEFT))return new WalkState;
					else return new IdleState;
					
				}
				else
				{
					if (4 <= _ani->getPlayIndex() && _ani->getPlayIndex() <= 6)
					{
						Vector3 position = player.getPosition();
						if (player.getDirection() == DIRECTION::RIGHT)
						{
							attackRc = FloatRect(position.x + 30, position.y - 100,
								position.x + 160, position.y + 100);
						}
						else
						{
							attackRc = FloatRect(position.x - 160, position.y - 100,
								position.x - 30, position.y + 100);
						}

						viewRc = FloatRect(attackRc.left, position.z + attackRc.top,
							attackRc.right, position.z + attackRc.bottom);
						player.attack(attackRc, 10, ATTACK_TYPE::KNOCKDOWN);
					}
					
				}
			break;

			case ATTACK_SKILL::RUN_QC:
				if (!_ani->isPlay())
				{
					if (KEY_MANAGER->isStayKeyDown(VK_RIGHT) || KEY_MANAGER->isStayKeyDown(VK_LEFT))return new WalkState;
					else return new IdleState;
				}
				else {
					_initTime += TIME_MANAGER->getElapsedTime();
					if (player.getDirection() == DIRECTION::RIGHT)
					{
						moveDir.x += player.getSpeed() / 5;
					}
					else
					{
						moveDir.x -= player.getSpeed() / 5;
					}


					if (2 <= _ani->getPlayIndex() && _ani->getPlayIndex() <= 3)
					{
						Vector3 position = player.getPosition();
						if (player.getDirection() == DIRECTION::RIGHT)
						{
							attackRc = FloatRect(position.x + 20, position.y - 45,
								position.x + 130, position.y + 10);
						}
						else
						{
							attackRc = FloatRect(position.x - 130, position.y - 45,
								position.x - 20, position.y + 10);
						}


						viewRc = FloatRect(attackRc.left, position.z + attackRc.top,
							attackRc.right, position.z + attackRc.bottom);
						player.attack(attackRc, 10, ATTACK_TYPE::HIT);
					}

					if (_initTime >= 0.2 &&KEY_MANAGER->isOnceKeyDown('Z'))
					{
						_img = IMAGE_MANAGER->findImage("Kyoko_attack2");

						_ani->init(_img->getWidth(), _img->getHeight(), _img->getMaxFrameX(), _img->getMaxFrameY());
						if (player.getDirection() == DIRECTION::RIGHT)
						{
							_ani->setPlayFrame(0, 7, false, false);
						}
						else
						{
							_ani->setPlayFrame(7, 14, false, false);
						}
						_ani->setFPS(15);
						_ani->start();


						_skill = ATTACK_SKILL::QC2;
						_initTime = 0;

					}
				}
				break;
			case ATTACK_SKILL::JUMP_QC:
				
				if (4 <= _ani->getPlayIndex() && _ani->getPlayIndex() <= 10)
				{
					//Vector3 position = player.getPosition();
					if (player.getDirection() == DIRECTION::RIGHT)
					{
						attackRc = FloatRect(player.getPosition().x + 20, player.getPosition().y ,
							player.getPosition().x + 90, player.getPosition().y + 100);
					}
					else
					{
						attackRc = FloatRect(player.getPosition().x - 90, player.getPosition().y,
							player.getPosition().x - 20, player.getPosition().y + 100);
					}


					viewRc = FloatRect(attackRc.left, player.getPosition().z + attackRc.top,
						attackRc.right, player.getPosition().z + attackRc.bottom);
					player.attack(attackRc, 10, ATTACK_TYPE::HIT);
				}

				moveDir.y -= _currJumpPower;
				_currJumpPower -= player.getGravity();

				moveDir.x += _currMoveDirX;
				


				break;
			case ATTACK_SKILL::HC:
				if (!_ani->isPlay())
				{
					if (KEY_MANAGER->isStayKeyDown(VK_RIGHT) || KEY_MANAGER->isStayKeyDown(VK_LEFT))return new WalkState;
					else return new IdleState;

				}
				else
				{
					if (5 <= _ani->getPlayIndex() && _ani->getPlayIndex() <= 7)
					{
						Vector3 position = player.getPosition();
						if (player.getDirection() == DIRECTION::RIGHT)
						{
							attackRc = FloatRect(position.x + 10, position.y - 100,
								position.x + 140, position.y + 100);
						}
						else
						{
							attackRc = FloatRect(position.x - 140, position.y - 100,
								position.x - 10, position.y + 100);
						}

						viewRc = FloatRect(attackRc.left, position.z + attackRc.top,
							attackRc.right, position.z + attackRc.bottom);
						player.attack(attackRc, 10, ATTACK_TYPE::KNOCKDOWN);
					}

				}

				break;
			case ATTACK_SKILL::RUN_HC:
				if (!_ani->isPlay())
				{
					if (KEY_MANAGER->isStayKeyDown(VK_RIGHT) || KEY_MANAGER->isStayKeyDown(VK_LEFT))return new WalkState;
					else return new IdleState;

				}
				else
				{
					if (3 <= _ani->getPlayIndex() && _ani->getPlayIndex() <= 10)
					{
						Vector3 position = player.getPosition();
						if (player.getDirection() == DIRECTION::RIGHT)
						{
							attackRc = FloatRect(position.x + 10, position.y - 40,
								position.x + 140, position.y + 100);
							moveDir.x += _currMoveDirX;
							_currMoveDirX -= 0.02f;
						}
						else
						{
							attackRc = FloatRect(position.x - 140, position.y - 40,
								position.x - 10, position.y + 100);
							moveDir.x += _currMoveDirX;
							_currMoveDirX += 0.02f;
						}

						viewRc = FloatRect(attackRc.left, position.z + attackRc.top,
							attackRc.right, position.z + attackRc.bottom);
						player.attack(attackRc, 10, ATTACK_TYPE::KNOCKDOWN);
					}

				}
				
				break;
			case ATTACK_SKILL::JUMP_HC:
				

				if (5 <= _ani->getPlayIndex() && _ani->getPlayIndex() <= 11)
				{
					//Vector3 position = player.getPosition();
					if (player.getDirection() == DIRECTION::RIGHT)
					{
						attackRc = FloatRect(player.getPosition().x , player.getPosition().y+90,
							player.getPosition().x + 60, player.getPosition().y + 150);
						
					}
					else
					{
						attackRc = FloatRect(player.getPosition().x - 60, player.getPosition().y+90,
							player.getPosition().x , player.getPosition().y + 150);
						
					}


					viewRc = FloatRect(attackRc.left, player.getPosition().z + attackRc.top,
						attackRc.right, player.getPosition().z + attackRc.bottom);
					player.attack(attackRc, 10, ATTACK_TYPE::KNOCKDOWN);
				}

				moveDir.x += _currMoveDirX;
				moveDir.y -= _currJumpPower;
				_currJumpPower -= player.getGravity();

				if (KEY_MANAGER->isStayKeyDown(VK_RIGHT))
				{
					moveDir.x += player.getSpeed();
				}
				if (KEY_MANAGER->isStayKeyDown(VK_LEFT))
				{
					moveDir.x -= player.getSpeed();
				}
				
				break;

				}
		
			
		

				player.move(moveDir);
			
				float currentPlayerY = player.getPosition().y;

				if (_currJumpPower < -1 && currentPlayerY == lastPlayerY && moveDir.y != 0 
					&& (_skill == ATTACK_SKILL::JUMP_QC|| _skill == ATTACK_SKILL::JUMP_HC))
				{
					if (KEY_MANAGER->isStayKeyDown(VK_RIGHT) || KEY_MANAGER->isStayKeyDown(VK_LEFT))
					{
						return new WalkState;
					}
					else
					{
						return new IdleState;
					}
				}
				
				

			return nullptr;

		}

	

void AttackState::render(Player & player)
{
	_img->setScale(3);
	Vector3 position = player.getPosition();
	
	if (_skill == ATTACK_SKILL::JUMP_HC)
	{
		if (player.getDirection() == DIRECTION::RIGHT)
		{
			position.x += 25;
		}
		else
		{
			position.x -= 25;
		}
	}
	else
	{
		if (player.getDirection() == DIRECTION::RIGHT)
		{
			position.x += 35;
		}
		else
		{
			position.x -= 35;
		}
	}

	if (_skill == ATTACK_SKILL::HC)
	{
		position.y += 15;
	}
	//CAMERA_MANAGER->rectangle(FloatRect(300, 300, 800, 800), D2D1::ColorF::Enum::Red, 1, 20);
	CAMERA_MANAGER->rectangle(viewRc, D2D1::ColorF::Enum::Red, 1, 1);
	CAMERA_MANAGER->aniRenderZ(_img, position, player.getSize(), _ani);

}

void AttackState::exit(Player & paleyr)
{
	_ani->release();
	SAFE_DELETE(_ani);
}
