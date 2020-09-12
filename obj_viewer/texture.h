#ifndef _TEXTURE_H_
#define _TEXTURE_H_
#include <string>

class Texture
{
private:
	unsigned int tex_id;
protected:
	
public:
	Texture();
	void load(std::string file, bool mipmap = false);
	
	inline unsigned int getId()
	{
		return tex_id;
	}
};


#endif /* _TEXTURE_H_ */