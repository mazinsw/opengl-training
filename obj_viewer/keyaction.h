#ifndef _KEYACTION_H_
#define _KEYACTION_H_

class KeyAction
{
private:
	int keyLow;
	int keyHigh;
	int state;
	int side;
public:
	KeyAction()
	{
		side = 1;
		state = 0;
		keyLow = keyHigh = 0;
	}
	
	KeyAction(int keyLow, int keyHigh)
	{
		side = 1;
		state = 0;
		setKeys(keyLow, keyHigh);
	}
	
	inline void setKeys(int keyLow, int keyHigh)
	{
		this->keyLow = keyLow;
		this->keyHigh = keyHigh;
	}
	
	inline void update(int key, bool down)
	{
		if(down)
		{
			if(key == keyLow)
			{
				state |= 1;
				side = -1;
			}
			else if(key == keyHigh)
			{
				state |= 2;
				side = 1;
			}
		}
		else
		{
			if(key == keyLow)
			{
				state &= ~1;
				if(state > 0)
					side = 1;
			}
			else if(key == keyHigh)
			{
				state &= ~2;
				if(state > 0)
					side = -1;
			}
		}
	}
	
	inline int getSide()
	{
		return side;
	}

	inline bool inAction()
	{
		return state > 0;
	}
};

#endif /* _KEYACTION_H_ */