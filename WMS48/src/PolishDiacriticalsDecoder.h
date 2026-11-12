#ifndef PL_DIACRITICAL_DECODER_H
#define PL_DIACRITICAL_DECODER_H

#include <Arduino.h>

char32_t decode2(const String &s)
{
    return ((s[0] & 0x1F) << 6) | (s[1] & 0x3F);
}

static const char32_t PL[18] = {
    U'Ą', U'Ć', U'Ę', U'Ł', U'Ń', U'Ó', U'Ś', U'Ź', U'Ż', // 0..8
    U'ą', U'ć', U'ę', U'ł', U'ń', U'ó', U'ś', U'ź', U'ż'  // 9..17
};

int polishIndex(char32_t cp)
{
    for (int i = 0; i < 18; ++i)
        if (PL[i] == cp)
            return i;
    return -1;
}

const int PL_SHIFT = 9;

// positive values idxs = standard ascii
// negative values idxs = polish diacritical
void decodeTextToFontIndex(const String txt, int *idxs, int &size)
{
    size = txt.length();
    idxs = new int[size];
    int index = 0;
    

    for (size_t i = 0; i < size; i++)
    {
        if ((unsigned char)txt[i] <= 127)
        {
            idxs[index] = (unsigned char)txt[i];
            index++;
            //printf("char: %i\n", (int)txt[i]);
        }
        else
        {
            String t = txt.substring(i, i+1);
            i++;
            char32_t cp = decode2(t);
            idxs[index] = polishIndex(cp);
            index++;
            //printf("cp=0x%X idx=%d\n", (unsigned)cp, -idx);
        }
    }

    if(index < size)
    {
        size = index;
    }
}

#endif