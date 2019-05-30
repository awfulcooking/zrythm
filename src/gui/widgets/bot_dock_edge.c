/*
 * Copyright (C) 2018-2019 Alexandros Theodotou <alex at zrythm dot org>
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

#include "gui/widgets/bot_dock_edge.h"
#include "gui/widgets/chord_pad.h"
#include "gui/widgets/clip_editor.h"
#include "gui/widgets/mixer.h"
#include "gui/widgets/modulator_view.h"
#include "gui/widgets/piano_roll.h"
#include "gui/widgets/rack.h"
#include "utils/gtk.h"
#include "utils/resources.h"

G_DEFINE_TYPE (BotDockEdgeWidget,
               bot_dock_edge_widget,
               GTK_TYPE_BOX)

static void
bot_dock_edge_widget_init (BotDockEdgeWidget * self)
{
  g_type_ensure (MIXER_WIDGET_TYPE);
  g_type_ensure (RACK_WIDGET_TYPE);
  g_type_ensure (CLIP_EDITOR_WIDGET_TYPE);
  g_type_ensure (MODULATOR_VIEW_WIDGET_TYPE);
  g_type_ensure (CHORD_PAD_WIDGET_TYPE);

  gtk_widget_init_template (GTK_WIDGET (self));

  /* set icons */
  gtk_button_set_image (
    GTK_BUTTON (self->mixer->channels_add),
    resources_get_icon (ICON_TYPE_ZRYTHM,
                        "plus.svg"));
}

static void
bot_dock_edge_widget_class_init (
  BotDockEdgeWidgetClass * _klass)
{
  GtkWidgetClass * klass = GTK_WIDGET_CLASS (_klass);
  resources_set_class_template (
    klass, "bot_dock_edge.ui");

  gtk_widget_class_set_css_name (
    klass, "bot-dock-edge");

  gtk_widget_class_bind_template_child (
    klass,
    BotDockEdgeWidget,
    bot_notebook);
  gtk_widget_class_bind_template_child (
    klass,
    BotDockEdgeWidget,
    clip_editor);
  gtk_widget_class_bind_template_child (
    klass,
    BotDockEdgeWidget,
    mixer);
  gtk_widget_class_bind_template_child (
    klass,
    BotDockEdgeWidget,
    modulator_view);
}
