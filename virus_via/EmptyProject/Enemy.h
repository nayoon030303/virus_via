#pragma once
class Enemy
{
public:
	virtual ~Enemy(){}
	virtual void Render() = 0;
	virtual void Update() = 0;
	virtual D3DXVECTOR2 getPos()=0;
	virtual bool isDead() = 0;
};

