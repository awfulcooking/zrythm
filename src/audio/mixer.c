/*
 * audio/mixer.c - The mixer
 *
 * Copyright (C) 2018 Alexandros Theodotou
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

/** \file
 * Mixer implementation. */

#include <pthread.h>
#include <stdlib.h>
#include <string.h>

#include "audio/channel.h"
#include "audio/engine.h"
#include "audio/mixer.h"
#include "audio/track.h"
#include "gui/widgets/main_window.h"
#include "gui/widgets/mixer.h"
#include "gui/widgets/track.h"
#include "gui/widgets/tracklist.h"

#include <gtk/gtk.h>

/**
 * process callback
 */
void
mixer_process (nframes_t     nframes)           ///< number of frames to fill in
{
  int loop = 1;

  /* wait for channels to finish processing */
  while (loop)
    {
      loop = 0;
      for (int i = 0; i < MIXER->num_channels; i++)
        {
          if (!MIXER->channels[i]->processed)
            {
              loop = 1;
              break;
            }
        }
    }


  /* process master channel */
  channel_process (MIXER->master,
                   nframes);
}

void
mixer_init ()
{
  g_message ("Initializing mixer...");
  /* allocate size */
  MIXER = calloc (1, sizeof (Mixer));

  MIXER->num_channels = 0;

  /* create master channel */
  /*MIXER->master = channel_create_master ();*/

  /* init channel strips array and add one of each */
  /*ADD_CHANNEL (channel_create (CT_MIDI, "Ch 1"));*/
  /*ADD_CHANNEL (channel_create (CT_AUDIO));*/
}

/**
 * Loads plugins from state files. Used when loading projects.
 */
void
mixer_load_plugins ()
{
  for (int i = 0; i < MIXER->num_channels; i++)
    {
      Channel * channel = MIXER->channels[i];
      for (int j = 0; j < STRIP_SIZE; j++)
        {
          Plugin * plugin = channel->strip[j];
          if (plugin)
            {
              plugin_instantiate (plugin);
            }
        }
    }

  /* do master too  */
  for (int j = 0; j < STRIP_SIZE; j++)
    {
      Plugin * plugin = MIXER->master->strip[j];
      if (plugin)
        {
          plugin_instantiate (plugin);
        }
    }
}

static void
generate_track (Channel * channel)
{
  channel->track = track_new (channel);
  channel_generate_automatables (channel);
  track_update_automation_tracks (channel->track);
  channel->track->widget = track_widget_new (channel->track);
  /*track_widget_show (channel->track->widget);*/
}

/**
 * Adds channel to mixer.
 */
void
mixer_add_channel_and_init_track (Channel * channel)
{
  generate_track (channel);
  MIXER->channels[MIXER->num_channels++] = channel;
}

void
mixer_add_master_and_init_track (Channel * channel)
{
  generate_track (channel);
  MIXER->master = channel;
}

/**
 * Returns channel at given position (order)
 *
 * Channel order in the mixer is reflected in the track list
 */
Channel *
mixer_get_channel_at_pos (int pos)
{
  for (int i = 0; i < MIXER->num_channels; i++)
    {
      Channel * channel = MIXER->channels[i];
      if (channel->id == pos)
        {
          return channel;
        }
    }
  g_warning ("No channel found at pos %d", pos);
  return NULL;
}

/**
 * Removes the given channel.
 */
void
mixer_remove_channel (Channel * channel)
{
  AUDIO_ENGINE->run = 0;
  channel->enabled = 0;
  channel->stop_thread = 1;
  mixer_widget_remove_channel (channel);
  tracklist_widget_remove_track (channel->track);
  for (int i = channel->id; i < MIXER->num_channels - 1; i++)
    {
      MIXER->channels[i] = MIXER->channels[i + 1];
      MIXER->channels[i]->id = i;
    }
  MIXER->num_channels--;
  channel_free (channel);
  g_message ("removed channel");
}

