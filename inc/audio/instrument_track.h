/*
 * Copyright (C) 2018-2019 Alexandros Theodotou
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

#ifndef __AUDIO_INSTRUMENT_TRACK_H__
#define __AUDIO_INSTRUMENT_TRACK_H__

#include "audio/channel_track.h"
#include "audio/track.h"

#include <jack/jack.h>

typedef struct Position Position;
typedef struct _TrackWidget TrackWidget;
typedef struct Channel Channel;
typedef struct MidiEvents MidiEvents;
typedef struct AutomationTrack AutomationTrack;
typedef struct Automatable Automatable;
typedef struct Region MidiRegion;
typedef jack_nframes_t nframes_t;

typedef struct Track InstrumentTrack;

/**
 * Initializes an instrument track.
 */
void
instrument_track_init (Track * track);

void
instrument_track_setup (InstrumentTrack * self);

/**
 * NOTE: real time func
 */
void
instrument_track_fill_midi_events (InstrumentTrack      * track,
                        Position   * pos, ///< start position to check
                        nframes_t  nframes, ///< n of frames from start pos
                        MidiEvents * midi_events); ///< midi events to fill

/**
 * Frees the track.
 *
 * TODO
 */
void
instrument_track_free (InstrumentTrack * track);

#endif // __AUDIO_INSTRUMENT_TRACK_H__
