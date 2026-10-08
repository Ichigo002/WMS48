#ifndef FONT_H
#define FONT_H

class Font
{
public:
    virtual ~Font() = default;

    int getCharacterWidth() const { return width; };
    int getCharacterHeight() const { return height; };

     virtual const uint8_t *getCharacter(char ascii) const = 0;

protected:
    int height;
    int width;
};

#endif