/*!
 *  \file    ColourConversion.h
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

#ifndef COLOURCONVERSION_H_
#define COLOURCONVERSION_H_

#define MIN3(x,y,z) ((y)<=(z)?((x)<=(y)?(x):(y)):((x)<=(z)?(x):(z)))
#define MAX3(x,y,z) ((y)>=(z)?((x)>=(y)?(x):(y)):((x)>=(z)?(x):(z)))

/*!
 * Function for converting from RGB colour space to HSV colour space.
 *
 * Original copyright:
 *
 * Copyright (c) 2008 the authors listed at the following URL, and/or
 * the authors of referenced articles or incorporated external code:
 * http://en.literateprograms.org/RGB_to_HSV_color_space_conversion_(C)?action=history&offset=20060515030319
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
 * CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
 * TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * Retrieved from: http://en.literateprograms.org/RGB_to_HSV_color_space_conversion_(C)?oldid=4766
 *
 * \param[in] r Value for red (0-255).
 * \param[in] g Value for green (0-255).
 * \param[in] b Value for blue (0-255).
 * \param[in] h Calculated value for hue (0-255).
 * \param[in] s Calculated value for saturation (0-255).
 * \param[in] v Calculated value (0-255).
 */
void convertRGBtoHSV(unsigned char r, unsigned char g, unsigned char b,
                     unsigned char& h, unsigned char& s, unsigned char& v);

#endif
