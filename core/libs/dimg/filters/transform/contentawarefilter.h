/* ============================================================
 *
 * This file is a part of digiKam project
 * https://www.digikam.org
 *
 * Date        : 2009-02-01
 * Description : Content aware resizer class.
 *
 * Copyright (C) 2009      by Julien Pontabry <julien dot pontabry at ulp dot u-strasbg dot fr>
 * Copyright (C) 2009-2021 by Gilles Caulier <caulier dot gilles at gmail dot com>
 * Copyright (C) 2010      by Martin Klapetek <martin dot klapetek at gmail dot com>
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

#ifndef DIGIKAM_CONTENT_AWARE_FILTER_H
#define DIGIKAM_CONTENT_AWARE_FILTER_H

// Qt includes

#include <QImage>

// Local includes

#include "digikam_config.h"
#include "dcolor.h"
#include "digikam_export.h"
#include "dimgthreadedfilter.h"

namespace Digikam
{

class DIGIKAM_EXPORT ContentAwareContainer
{

public:

    enum EnergyFunction
    {
        GradientNorm = 0,
        SumOfAbsoluteValues,
        XAbsoluteValue,
        LumaGradientNorm,
        LumaSumOfAbsoluteValues,
        LumaXAbsoluteValue
    };

public:

    ContentAwareContainer()
      : preserve_skin_tones(false),
        width(0),
        height(0),
        step(1),
        side_switch_freq(4),
        rigidity(0.0),
        func(GradientNorm),
        resize_order(Qt::Horizontal)
    {
    };

    ~ContentAwareContainer()
    {
    };

public:

    bool            preserve_skin_tones;

    uint            width;
    uint            height;

    int             step;
    int             side_switch_freq;

    double          rigidity;

    QImage          mask;

    EnergyFunction  func;
    Qt::Orientation resize_order;
};

// -----------------------------------------------------------------------------------------

class DIGIKAM_EXPORT ContentAwareFilter : public DImgThreadedFilter
{
    Q_OBJECT

public:

    explicit ContentAwareFilter(QObject* const parent = nullptr);
    explicit ContentAwareFilter(DImg* const orgImage,
                                QObject* const parent = nullptr,
                                const ContentAwareContainer& settings = ContentAwareContainer());
    ~ContentAwareFilter() override;

    void progressCallback(int progress);

    static QString          FilterIdentifier()
    {
        return QLatin1String("digikam:ContentAwareFilter");
    }

    static QString          DisplayableName();

    static QList<int>       SupportedVersions()
    {
        return QList<int>() << 1;
    }

    static int              CurrentVersion()
    {
        return 1;
    }

    QString         filterIdentifier()                          const override
    {
        return FilterIdentifier();
    }

    FilterAction    filterAction()                                    override;
    void                    readParameters(const FilterAction& action)        override;

private:

    void cancelFilter()                                                       override;
    void filterImage()                                                        override;

    void        buildBias(const QImage& mask);
    void        buildSkinToneBias();
    inline bool isSkinTone(const DColor& c);
    void        getEnergyImage();

private:

    class Private;
    Private* const d;
};

} // namespace Digikam

#endif // DIGIKAM_CONTENT_AWARE_FILTER_H
