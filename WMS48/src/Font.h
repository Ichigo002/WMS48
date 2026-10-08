#ifndef FONT_H
#define FONT_H

class Font
{
public:
    virtual ~Font() = default;

    int getCharacterWidth() { return width; };
    int getCharacterHeight() { return height; };

    virtual uint8_t *getCharacter(char ascii) = 0;

protected:
    int height;
    int width;

    
};

#endif