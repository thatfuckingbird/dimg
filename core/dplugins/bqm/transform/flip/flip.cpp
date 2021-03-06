/* ============================================================
 *
 * This file is a part of digiKam project
 * https://www.digikam.org
 *
 * Date        : 2009-02-10
 * Description : flip image batch tool.
 *
 * Copyright (C) 2009-2021 by Gilles Caulier <caulier dot gilles at gmail dot com>
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

#include "flip.h"

// Qt includes

#include <QLabel>
#include <QWidget>
#include <QComboBox>

// KDE includes

#include <klocalizedstring.h>

// Local includes

#include "dlayoutbox.h"
#include "digikam_debug.h"
#include "dimg.h"
#include "dimgbuiltinfilter.h"
#include "jpegutils.h"

namespace DigikamBqmFlipPlugin
{

Flip::Flip(QObject* const parent)
    : BatchTool(QLatin1String("Flip"), TransformTool, parent),
      m_comboBox(nullptr)
{
}

Flip::~Flip()
{
}

BatchTool* Flip::clone(QObject* const parent) const
{
    return new Flip(parent);
}

void Flip::registerSettingsWidget()
{
    DVBox* const vbox      = new DVBox;
    QLabel* const label    = new QLabel(vbox);
    m_comboBox             = new QComboBox(vbox);
    m_comboBox->insertItem(DImg::HORIZONTAL, i18nc("@item: orientation", "Horizontal"));
    m_comboBox->insertItem(DImg::VERTICAL,   i18nc("@item: orientation", "Vertical"));
    label->setText(i18nc("@label", "Flip:"));
    QLabel* const space    = new QLabel(vbox);
    vbox->setStretchFactor(space, 10);

    m_settingsWidget       = vbox;

    setNeedResetExifOrientation(true);

    connect(m_comboBox, SIGNAL(activated(int)),
            this, SLOT(slotSettingsChanged()));

    BatchTool::registerSettingsWidget();
}

BatchToolSettings Flip::defaultSettings()
{
    BatchToolSettings settings;
    settings.insert(QLatin1String("Flip"), DImg::HORIZONTAL);

    return settings;
}

void Flip::slotAssignSettings2Widget()
{
    m_comboBox->setCurrentIndex(settings()[QLatin1String("Flip")].toInt());
}

void Flip::slotSettingsChanged()
{
    BatchToolSettings settings;
    settings.insert(QLatin1String("Flip"), m_comboBox->currentIndex());
    BatchTool::slotSettingsChanged(settings);
}

bool Flip::toolOperations()
{
    DImg::FLIP flip = (DImg::FLIP)(settings()[QLatin1String("Flip")].toInt());

    if (JPEGUtils::isJpegImage(inputUrl().toLocalFile()) && image().isNull())
    {
        JPEGUtils::JpegRotator rotator(inputUrl().toLocalFile());
        rotator.setDestinationFile(outputUrl().toLocalFile());

        switch (flip)
        {
            case DImg::HORIZONTAL:
            {
                return rotator.exifTransform(MetaEngineRotation::FlipHorizontal);
            }

            case DImg::VERTICAL:
            {
                return rotator.exifTransform(MetaEngineRotation::FlipVertical);
            }

            default:
            {
                qCDebug(DIGIKAM_DPLUGIN_BQM_LOG) << "Unknown flip action";
                return false;
            }
        }
    }

    if (!loadToDImg())
    {
        return false;
    }

    DImgBuiltinFilter filter;

    switch (flip)
    {
        case DImg::HORIZONTAL:
        {
            filter = DImgBuiltinFilter(DImgBuiltinFilter::FlipHorizontally);
            break;
        }

        case DImg::VERTICAL:
        {
            filter = DImgBuiltinFilter(DImgBuiltinFilter::FlipVertically);
            break;
        }
    }

    applyFilter(&filter);

    return (savefromDImg());
}

} // namespace DigikamBqmFlipPlugin
