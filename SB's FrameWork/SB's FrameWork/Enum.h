#ifndef _ENUM_H_
#define _ENUM_H_

enum eObjectType
{
	OBJ_BACKGROUND,
	OBJ_PLAYER,
	OBJ_PLAYER_LEG,
	OBJ_MONSTER,
	OBJ_TOMA,
	OBJ_ZOMBIE,
	OBJ_ZOMBIEGRANADE,
	OBJ_BULLET,
	OBJ_GRANADE,
	OBJ_EFFECT,
	OBJ_MOUSE,
	OBJ_LINE,
	OBJ_BOSS,
	OBJ_ITEM,
	OBJ_END,
};

enum eSceneState
{
	SCENE_LOGO,
	SCENE_MENU,
	SCENE_SELECT_PLAYER,
	SCENE_STAGE,
	SCENE_BOSS,
	SCENE_EDIT,
	SCENE_END,
};

enum eEnemyMotionState
{
	ENEMY_STAND,
	ENEMY_WALK,
	ENEMY_THROW,
	ENEMY_DEAD,
};

enum eTomaMotionState
{
	TOMA_STAND,
	TOMA_WALK,
};

enum eZombieMotionState
{
	ZOMBIE_WALK,
	ZOMBIE_ATTACK,
};

enum eBossMotionState
{
	BOSS_STAND,
	BOSS_CHARGE,
	BOSS_BULLET,
	BOSS_FIRE,
	BOSS_LAZER,
	BOSS_DEAD,
};

enum eBulletDirection
{
	BULLET_LEFT,
	BULLET_RIGHT,
	BULLET_UP,
	BULLET_DOWN,
	BULLET_HEAVYDIR,
};

enum eBulletType
{
	BULLET_PISTOL,
	BULLET_TOMA,
	BULLET_HEAVY,
	BULLET_BOSS,
};

enum eGranadeType
{
	GRANADE_PZOMBIE,
	GRANADE_PLAYER,
	GRANADE_MONSTER,
	GRANADE_ZOMBIE,
};

enum eEffectType
{
	EFFECT_MGRANADE,
	EFFECT_GRANADE,
	EFFECT_PISTOL,
	EFFECT_BIGEXPLOSION
};

enum eCurAction			//스프라이트중 다른행동.
{
	EA_ATTACK,
	EA_DEAD,
	EA_JUMP,
	EA_END,


	//좀비
	EA_CHANGEEND,
	EA_ZBOMB,
	EA_STAND,
};

enum eHeavyDir
{
	LEFT,
	RIGHT,
	UP,
	DOWN,
	RIGHT_UP_1,
	RIGHT_UP_2,
	RIGHT_UP_3,
	RIGHT_DOWN_1,
	RIGHT_DOWN_2,
	RIGHT_DOWN_3,
	LEFT_UP_1,
	LEFT_UP_2,
	LEFT_UP_3,
	LEFT_DOWN_1,
	LEFT_DOWN_2,
	LEFT_DOWN_3,
	
	BOSSBULLETSTAY,
	BOSSBULLET,
};

enum ePlayerZombie
{
	PZOMBIE_CHANGE,
	PZOMBIE_STAND,
	PZOMBIE_WALK,
	PZOMBIE_JUMP,
	PZOMBIE_ATT,
	PZOMBIE_GRANDE,
	PZOMBIE_DEAD,
};

enum eItem
{
	ITEM_HEAVY,
	ITEM_BOMB,
};

#endif