/* ============================================================
 *
 * This file is a part of digiKam project
 * https://www.digikam.org
 *
 * Date        : 2006-10-15
 * Description : XMP subjects settings page.
 *
 * Copyright (C) 2006-2021 by Gilles Caulier <caulier dot gilles at gmail dot com>
 * Copyright (C) 2009      by Andi Clemens <andi dot clemens at googlemail dot com>
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

#ifndef DIGIKAM_XMP_SUBJECTS_H
#define DIGIKAM_XMP_SUBJECTS_H

// Qt includes

#include <QWidget>

// Local includes

#include "dmetadata.h"
#include "subjectwidget.h"

using namespace Digikam;

namespace DigikamGenericMetadataEditPlugin
{

class XMPSubjects : public SubjectWidget
{
    Q_OBJECT

public:

    explicit XMPSubjects(QWidget* const parent);
    ~XMPSubjects() override;

    void applyMetadata(const DMetadata& meta);
    void readMetadata(const DMetadata& meta);
};

} // namespace DigikamGenericMetadataEditPlugin

#endif // DIGIKAM_XMP_SUBJECTS_H
