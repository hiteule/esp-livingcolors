/*!
 *  \file    LivingColors.h
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
 *    Created: 03-10-2008
 */

#ifndef LIVINGCOLORS_H_
#define LIVINGCOLORS_H_

#include "CC2500.h"
#include "ColourConversion.h"
#include <inttypes.h>

#define MAXLAMPS 6

/*! \brief Class for interfacing with Philips LivingColors lamp.
 *
 * This class implements basic functions to communicate with the LivingColors lamp.
 */
class LivingColors
{
protected:
    /*!
     * CC2500 object to communicate with the LivingColors lamp.
     */
    CC2500 m_cc2500;

    /*!
     * Sequence number which is used during communication with the LivingColors lamp. The sent
     * sequence number must match the received sequence number.
     */
    unsigned char m_sequence;

    /*!
     * Address storage for lamps. The first byte indicates a valid address (0x01), the next 9 bytes
     * are the lamp address.
     *
     * A lamp address consists of a unique lamp identifier (first 4 bytes) and a unique remote
     * identifier (last 5 bytes).
     */
    unsigned char m_lamps[MAXLAMPS][10];

    /*!
     * Maximum number of lamps that can be controlled.
     */
    unsigned char m_maxNumLamps;

    /*!
     * Number of stored lamp addresses.
     */
    unsigned char m_numLamps;

public:
    /*!
     * Constructor.
     *
     * \param[in] pinCS Pin number of slave select, default is 10.
     * \param[in] pinSCK Pin number of clock, default is 13 (Arduino standard).
     * \param[in] pinMOSI Pin number of master output slave input, default is 11 (Arduino standard).
     * \param[in] pinMISO Pin number of master input slave output, default is 12 (Arduino standard).
     */
    LivingColors(unsigned char pinCS = 10,
                 unsigned char pinSCK = 13,
                 unsigned char pinMOSI = 11,
                 unsigned char pinMISO = 12);

    /*!
     * Destructor.
     */
    ~LivingColors();

    /*!
     * Initializes communication with the LivingColors lamp.
     */
    void init();

    /*!
     * Returns the maximum number of storable lamps.
     *
     * \return Maximum number of lamps.
     */
    unsigned char getMaxNumLamps();

    /*!
     * Returns the number of currently known lamps.
     *
     * \return Number of known adresses.
     */
    unsigned char getNumLamps();

    /*!
     * Adds a lamp address to storage. Address must be 9 bytes long.
     *
     * \param[in] address Array holding lamp address.
     * \return Lamp index for address or -1 on failure.
     */
    char addLamp(unsigned char* address);

    /*!
     * Saves the address of lamp with given index in supplied array. Only fills array when index and
     * address are valid.
     *
     * \param[in] index Lamp index, must be 0 <= index < getNumLamps().
     * \param[in] address Array for lamp address, must be at least 9 bytes long.
     * \return True if array is filled with valid address, false otherwise.
     */
    bool getLamp(unsigned char index, unsigned char* address);

    /*!
     * Tries to learn lamp addresses by snooping the commands which are sent by the official
     * remote. The learning time period is about 5 seconds; hold the official remote very close
     * to the board and press some commands (e.g. change colour, off, on).
     */
    void learnLamps();

    /*!
     * Clears all lamp addresses.
     */
    void clearLamps();

    /*!
     * Sets colour of lamp with given index. Updates colour only if lamp address is valid.
     *
     * \param[in] index Lamp index, must be 0 <= index < getNumLamps().
     * \param[in] r Red value for lamp (0-255).
     * \param[in] g Green value for lamp (0-255).
     * \param[in] b Blue value for lamp (0-255).
     */
    void setLampColourRGB(unsigned char index, unsigned char r, unsigned char g, unsigned char b);

    /*!
     * Sets colour of lamp with given index. Updates colour only if lamp address is valid.
     *
     * \param[in] index Lamp index, must be 0 <= index < getNumLamps().
     * \param[in] h Hue value for lamp (0-255).
     * \param[in] s Saturation value for lamp (0-255).
     * \param[in] v Value value for lamp (0-255).
     */
    void setLampColourHSV(unsigned char index, unsigned char h, unsigned char s, unsigned char v);

    /*!
     * Turns lamp with given index on and sets colour if lamp address is valid.
     *
     * \param[in] index Lamp index, must be 0 <= index < getNumLamps().
     * \param[in] r Red value for lamp (0-255).
     * \param[in] g Green value for lamp (0-255).
     * \param[in] b Blue value for lamp (0-255).
     */
    void turnLampOnRGB(unsigned char index, unsigned char r, unsigned char g, unsigned char b);

    /*!
     * Turns lamp with given index on and sets colour if lamp address is valid.
     *
     * \param[in] index Lamp index, must be 0 <= index < getNumLamps().
     * \param[in] h Hue value for lamp (0-255).
     * \param[in] s Saturation value for lamp (0-255).
     * \param[in] v Value value for lamp (0-255).
     */
    void turnLampOnHSV(unsigned char index, unsigned char h, unsigned char s, unsigned char v);

    /*!
     * Turns lamp with given index off if lamp address is valid.
     *
     * \param[in] index Lamp index, must be 0 <= index < getNumLamps();
     */
    void turnLampOff(unsigned char index);

private:
    /*!
     * Checks if lamp address is already known, stores address if not known.
     *
     * \param[in] address Lamp address to check, length must be at least 10 bytes.
     */
    void checkAddress(unsigned char* address);

    /*!
     * Sends command to lamp. Command can be on, off or set colour.
     *
     * \param[in] index Lamp index, must be 0 <= index < getNumLamps().
     * \param[in] command Command to send (3 = set colour, 5 = on, 7 = off).
     * \param[in] h Hue value to sent (0-255), must be corrected for LivingColors.
     * \param[in] s Saturation value to sent (0-255).
     * \param[in] v Value to sent (0-255).
     */
    void sendCommand(unsigned char index,
                     unsigned char command,
                     unsigned char h,
                     unsigned char s,
                     unsigned char v);

    /*!
     * Copy constructor, disabled.
     */
    LivingColors(const LivingColors& that);

    /*!
     * Assignment operator, disabled.
     */
    LivingColors& operator=(const LivingColors& that);
};

#endif
