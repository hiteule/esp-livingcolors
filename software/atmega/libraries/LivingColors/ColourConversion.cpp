/*!
 *  \file    ColourConversion.cpp
 *  \version 1.1
 *  \date    29-01-2009
 *  \author  George Mathijssen, george.knutsel@gmail.com
 *
 *  Copyright (c) 2008, 2009 George Mathijssen
 *  
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License along
 *  with this program; if not, write to the Free Software Foundation, Inc.,
 *  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 *  \internal
 *    Created: 29-09-2008
 */

#include "ColourConversion.h"

void convertRGBtoHSV(unsigned char r, unsigned char g, unsigned char b,
    unsigned char& h, unsigned char& s, unsigned char& v)
{
    unsigned char rgb_min = MIN3(r, g, b);
    unsigned char rgb_max = MAX3(r, g, b);

    v = rgb_max;

    if (v == 0) {
        // colour is black
        h = s = 0;
        return;
    }

    s = 255 * long(rgb_max - rgb_min) / v;

    if (s == 0) {
        // grey colour, no chroma
        h = 0;
        return;
    }

    // compute hue
    if (rgb_max == r) {
        h = 0 + 43 * (g - b) / (rgb_max - rgb_min);
    } else if (rgb_max == g) {
        h = 85 + 43 * (b - r) / (rgb_max - rgb_min);
    } else {
        // rgb_max == b
        h = 171 + 43 * (r - g) / (rgb_max - rgb_min);
    }
}
