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

#include "audio/control_room.h"
#include "gui/widgets/control_room.h"
#include "gui/widgets/file_browser.h"
#include "gui/widgets/plugin_browser.h"
#include "gui/widgets/right_dock_edge.h"
#include "project.h"
#include "utils/resources.h"

#include <glib/gi18n.h>

G_DEFINE_TYPE (RightDockEdgeWidget,
               right_dock_edge_widget,
               GTK_TYPE_BOX)

static void
right_dock_edge_widget_init (
  RightDockEdgeWidget * self)
{
  g_type_ensure (CONTROL_ROOM_WIDGET_TYPE);

  gtk_widget_init_template (GTK_WIDGET (self));

  GtkWidget * img;

  self->file_browser =
    file_browser_widget_new ();
  img =
    gtk_image_new_from_icon_name (
      "z-media-optical-audio",
      GTK_ICON_SIZE_SMALL_TOOLBAR);
  gtk_widget_set_tooltip_text (
    img, _("File Browser"));
  gtk_notebook_prepend_page (
    self->right_notebook,
    GTK_WIDGET (self->file_browser),
    img);
  gtk_widget_show_all (
    GTK_WIDGET (self->right_notebook));

  /* setup browser */
  self->plugin_browser =
    plugin_browser_widget_new ();
  img =
    gtk_image_new_from_icon_name (
      "z-plugins",
      GTK_ICON_SIZE_SMALL_TOOLBAR);
  gtk_widget_set_tooltip_text (
    img, _("Plugin Browser"));
  gtk_notebook_prepend_page (
    self->right_notebook,
    GTK_WIDGET (self->plugin_browser),
    img);

  control_room_widget_setup (
    self->control_room,
    CONTROL_ROOM);
}

static void
right_dock_edge_widget_class_init (
  RightDockEdgeWidgetClass * _klass)
{
  GtkWidgetClass * klass =
    GTK_WIDGET_CLASS (_klass);
  resources_set_class_template (
    klass, "right_dock_edge.ui");

  gtk_widget_class_set_css_name (
    klass, "right-dock-edge");

  gtk_widget_class_bind_template_child (
    klass,
    RightDockEdgeWidget,
    right_notebook);
  gtk_widget_class_bind_template_child (
    klass,
    RightDockEdgeWidget,
    control_room);
}
