/*
 * Copyright (C) 2019 Alexandros Theodotou <alex at zrythm dot org>
 *
 * This file is part of Zrythm
 *
 * Zrythm is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Zrythm is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Zrythm.  If not, see <https://www.gnu.org/licenses/>.
 */

/**
 * \file
 *
 * The control room backend.
 */
#ifndef __AUDIO_CONTROL_ROOM_H__
#define __AUDIO_CONTROL_ROOM_H__

#include "audio/fader.h"

/**
 * @addtogroup
 *
 * @{
 */

#define CONTROL_ROOM (&PROJECT->control_room)

/**
 * The control room allows to specify how Listen will
 * work on each Channel and to set overall volume
 * after the Master Channel so you can change the
 * volume without touching the Master Fader.
 */
typedef struct ControlRoom
{
  /** Temporarily dim the output volume. */
  int        dim_output;

  /**
   * Output volume.
   */
  Fader      vol_fader;

  /**
   * The volume to set other channels to when Listen
   * is enabled on a Channel.
   */
  Fader      listen_vol_fader;

} ControlRoom;

/**
 * Inits the ControlRoom.
 */
void
control_room_init (
  ControlRoom * self);

/**
 * Sets dim_output to on/off and notifies interested
 * parties.
 */
void
control_room_set_dim_output (
  ControlRoom * self,
  int           dim_output);

/**
 * @}
 */

#endif
