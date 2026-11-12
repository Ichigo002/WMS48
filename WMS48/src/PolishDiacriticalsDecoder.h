#ifndef PL_DIACRITICAL_DECODER_H
#define PL_DIACRITICAL_DECODER_H

#include <Arduino.h>
#include <vector>

inline char32_t decode2(const String &s)
{
    return ((s[0] & 0x1F) << 6) | (s[1] & 0x3F);
}

inline static const char32_t PL[18] = {
    U'Ą', U'Ć', U'Ę', U'Ł', U'Ń', U'Ó', U'Ś', U'Ź', U'Ż', // 0..8
    U'ą', U'ć', U'ę', U'ł', U'ń', U'ó', U'ś', U'ź', U'ż'  // 9..17
};

inline int polishIndex(char32_t cp)
{
    for (int i = 0; i < 18; ++i)
        if (PL[i] == cp)
            return i;
    return -1;
}

inline const int PL_SHIFT = 9;

#define TXT_DECODER_DEFAULT_BUFFER_SIZE 50
inline std::vector<int> _char_decoding_polish_index_buffer;


// positive values idxs = standard ascii
// negative values idxs = polish diacritical
inline std::vector<int> &decodeTextToCharIndex(const String &txt)
{
    _char_decoding_polish_index_buffer.clear();


    if(_char_decoding_polish_index_buffer.capacity() < TXT_DECODER_DEFAULT_BUFFER_SIZE)
        _char_decoding_polish_index_buffer.reserve(TXT_DECODER_DEFAULT_BUFFER_SIZE);

    for (size_t i = 0; i < txt.length(); i++)
    {
        if ((unsigned char)txt[i] <= 127)
        {
            _char_decoding_polish_index_buffer.push_back((unsigned char)txt[i]);
        }
        else
        {
            String t = txt.substring(i, i+2);
            i++;
            //Serial.printf("decode index pl: %i\n", -polishIndex(decode2(t)));
            _char_decoding_polish_index_buffer.push_back(-polishIndex(decode2(t)));
        }
    }

    return _char_decoding_polish_index_buffer;
}

#endif