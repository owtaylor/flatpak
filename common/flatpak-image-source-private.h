/*
 * Copyright © 2024 Red Hat, Inc
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.	 See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library. If not, see <http://www.gnu.org/licenses/>.
 *
 * Authors:
 *       Owen Taylor <otaylor@redhat.com>
 */

#ifndef __FLATPAK_IMAGE_SOURCE_H__
#define __FLATPAK_IMAGE_SOURCE_H__

#include <glib.h>
#include <gio/gio.h>

#include <flatpak-common-types-private.h>

#define FLATPAK_TYPE_IMAGE_SOURCE flatpak_image_source_get_type ()
#define FLATPAK_IMAGE_SOURCE(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), FLATPAK_TYPE_IMAGE_SOURCE, FlatpakImageSource))
#define FLATPAK_IS_IMAGE_SOURCE(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), FLATPAK_TYPE_IMAGE_SOURCE))

GType flatpak_image_source_get_type (void);

G_DEFINE_AUTOPTR_CLEANUP_FUNC (FlatpakImageSource, g_object_unref)


FlatpakImageSource *flatpak_image_source_new_local (GFile        *file,
                                                    const char   *reference,
                                                    GCancellable *cancellable,
                                                    GError      **error);
FlatpakImageSource *flatpak_image_source_new_remote (const char   *uri,
                                                     const char   *oci_repository,
                                                     const char   *digest,
                                                     GCancellable *cancellable,
                                                     GError      **error);

void flatpak_image_source_set_token (FlatpakImageSource *self,
                                     const char         *token);

FlatpakOciRegistry *flatpak_image_source_get_registry       (FlatpakImageSource *self);
const char         *flatpak_image_source_get_oci_repository (FlatpakImageSource *self);
const char         *flatpak_image_source_get_digest         (FlatpakImageSource *self);
FlatpakOciManifest *flatpak_image_source_get_manifest       (FlatpakImageSource *self);
gsize               flatpak_image_source_get_manifest_size  (FlatpakImageSource *self);
FlatpakOciImage    *flatpak_image_source_get_image_config   (FlatpakImageSource *self);

const char *flatpak_image_source_get_ref              (FlatpakImageSource *self);
const char *flatpak_image_source_get_commit           (FlatpakImageSource *self);
const char *flatpak_image_source_get_parent_commit    (FlatpakImageSource *self);
guint64     flatpak_image_source_get_commit_timestamp (FlatpakImageSource *self);
const char *flatpak_image_source_get_commit_subject   (FlatpakImageSource *self);
const char *flatpak_image_source_get_commit_body      (FlatpakImageSource *self);

void flatpak_image_source_build_commit_metadata (FlatpakImageSource *self,
                                                 GVariantBuilder    *metadata_builder);

#endif /* __FLATPAK_IMAGE_SOURCE_H__ */
