/* ============================================================
 *
 * This file is a part of digiKam project
 * https://www.digikam.org
 *
 * Date        : 2006-10-12
 * Description : EXIF caption settings page.
 *
 * Copyright (C) 2006-2021 by Gilles Caulier <caulier dot gilles at gmail dot com>
 *
 * This program is free software; you can redistribute it
 * and/or modify it under the terms of the GNU General
 * Public License as published by the Free Software Foundation;
 * either version 2, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * ============================================================ */

#ifndef DIGIKAM_EXIF_CAPTION_H
#define DIGIKAM_EXIF_CAPTION_H

// Qt includes

#include <QWidget>

// Local includes

#include "dmetadata.h"

using namespace Digikam;

namespace DigikamGenericMetadataEditPlugin
{

class EXIFCaption : public QWidget
{
    Q_OBJECT

public:

    explicit EXIFCaption(QWidget* const parent);
    ~EXIFCaption() override;

    void applyMetadata(const DMetadata& meta);
    void readMetadata(const DMetadata& meta);

    bool syncJFIFCommentIsChecked() const;
    bool syncXMPCaptionIsChecked() const;
    bool syncIPTCCaptionIsChecked() const;

    void setCheckedSyncJFIFComment(bool c);
    void setCheckedSyncXMPCaption(bool c);
    void setCheckedSyncIPTCCaption(bool c);

    QString getEXIFUserComments() const;

Q_SIGNALS:

    void signalModified();

private:

    class Private;
    Private* const d;
};

} // namespace DigikamGenericMetadataEditPlugin

#endif // DIGIKAM_EXIF_CAPTION_H
