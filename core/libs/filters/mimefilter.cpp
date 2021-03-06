/* ============================================================
 *
 * This file is a part of digiKam project
 * https://www.digikam.org
 *
 * Date        : 2007-10-22
 * Description : a widget to filter album contents by type mime
 *
 * Copyright (C) 2007-2021 by Gilles Caulier <caulier dot gilles at gmail dot com>
 *
 * This program is free software; you can redistribute it
 * and/or modify it under the terms of the GNU General
 * Public License as published by the Free Software Foundation;
 * either version 2, or (at your option)
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * ============================================================ */

#include "mimefilter.h"

// KDE includes

#include <klocalizedstring.h>

namespace Digikam
{

MimeFilter::MimeFilter(QWidget* const parent)
    : QComboBox(parent)
{
    insertItem(AllFiles,       i18n("All Files"));
    insertItem(ImageFiles,     i18n("Image Files"));
    insertItem(NoRAWFiles,     i18n("No RAW Files"));
    insertItem(JPGFiles,       i18n("JPEG Files"));
    insertItem(PNGFiles,       i18n("PNG Files"));
    insertItem(TIFFiles,       i18n("TIFF Files"));
    insertItem(PGFFiles,       i18n("PGF Files"));
    insertItem(HEIFFiles,      i18n("HEIF Files"));
    insertItem(DNGFiles,       i18n("DNG Files"));
    insertItem(RAWFiles,       i18n("RAW Files"));
    insertItem(MoviesFiles,    i18n("Video Files"));
    insertItem(AudioFiles,     i18n("Audio Files"));
    insertItem(RasterGraphics, i18n("Raster Graphics"));

    setToolTip(i18n("Filter by file type"));
    setWhatsThis(i18n("Select the file types (MIME types) that you want shown. "
                      "Note: \"Raster Graphics\" are file formats from raster graphics editors, "
                      "such as Photoshop, The Gimp, Krita, etc."));

    setMimeFilter(AllFiles);
}

MimeFilter::~MimeFilter()
{
}

void MimeFilter::setMimeFilter(int filter)
{
    setCurrentIndex(filter);
    emit activated(filter);
}

int MimeFilter::mimeFilter()
{
    return currentIndex();
}

} // namespace Digikam
