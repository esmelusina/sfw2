#include "AssetLibrary.h"
#include "sfwdraw.h"
#include <map>
#include <iostream>

// Global Static objects in a SOURCE file will only be acccesible
// by functions in the same source file.
// This 'map' is an associative container between a string and an unsigned int.
// using template magic and other sugar, the map is basically an array such that
// a string can now be used as an index to store unsigned integers!
static std::map<std::string, unsigned> textures;

// sfw::loadTextureMap returns an unsigned int to use as a handle
// so that it knows which texture to draw when using sfw::drawTexture.
// It can be difficult to get that handle into the right variable.
// As a point of convenience, we could use a map to store an association
// between a human readable name and a texture we load in. This lets us
// name a texture and then reuse that name elsewhere.
void loadTexture(const std::string &name, const char *path,
											unsigned r, unsigned c)
{
	// Our parameters MATCH the sfw parameters, we just pass them along.
	// This allows to WRAP the functionality of sfw into our own easier
	// to use naming scheme.
	textures[name] = sfw::loadTextureMap(path,r,c);
}

// If we use the load texture, we now can use the name to fetch the
// the texture handle from anywhere! Once fetched, the handle can be
// used for drawing as per normal. This allows us to safely, globally
// access all of our textures by whatever name we give it.
// This sort of 'aliasing' or 'binding' is very common when working
// with other people's libraries. It gives us the freedom to use our
// own internal values until the library is actually needed.
unsigned getTexture(const std::string &name)
{
	if (name == "")
	{
		std::cerr << "Texture name not set!" << std::endl;
		return 0;
	}
	if (textures[name] == 0)
	{
		std::cerr << "Texture associated with the name " << name << " was not loaded in correctly." << std::endl;
		return 0;
	}
	return textures[name];
}