/* ============================================================
 *
 * This file is a part of digiKam project
 * https://www.digikam.org
 *
 * Date        : 2011-02-09
 * Description : color label filter
 *
 * Copyright (C) 2011-2021 by Gilles Caulier <caulier dot gilles at gmail dot com>
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

#ifndef DIGIKAM_COLOR_LABEL_FILTER_H
#define DIGIKAM_COLOR_LABEL_FILTER_H

// Qt includes

#include <QList>
#include <QWidget>

// Local includes

#include "colorlabelwidget.h"

namespace Digikam
{

class TAlbum;

class ColorLabelFilter : public ColorLabelWidget
{
    Q_OBJECT

public:

    explicit ColorLabelFilter(QWidget* const parent = nullptr);
    ~ColorLabelFilter() override;

    QList<TAlbum*> getCheckedColorLabelTags();

    void reset();

Q_SIGNALS:

    void signalColorLabelSelectionChanged(const QList<ColorLabel>&);

private Q_SLOTS:

    void slotColorLabelSelectionChanged();
};

} // namespace Digikam

#endif // DIGIKAM_COLOR_LABEL_FILTER_H
