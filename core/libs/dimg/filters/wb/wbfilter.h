/* ============================================================
 *
 * This file is a part of digiKam project
 * https://www.digikam.org
 *
 * Date        : 2007-16-01
 * Description : white balance color correction.
 *
 * Copyright (C) 2007-2021 by Gilles Caulier <caulier dot gilles at gmail dot com>
 * Copyright (C) 2008      by Guillaume Castagnino <casta at xwing dot info>
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

#ifndef DIGIKAM_WB_FILTER_H
#define DIGIKAM_WB_FILTER_H

// Qt includes

#include <QColor>

// Local includes

#include "digikam_export.h"
#include "dimgthreadedfilter.h"
#include "digikam_globals.h"
#include "wbcontainer.h"

namespace Digikam
{

class DImg;

class DIGIKAM_EXPORT WBFilter : public DImgThreadedFilter
{
    Q_OBJECT

public:

    explicit WBFilter(QObject* const parent = nullptr);
    explicit WBFilter(DImg* const orgImage,
                      QObject* const parent = nullptr,
                      const WBContainer& settings = WBContainer());
    explicit WBFilter(const WBContainer& settings,
                      DImgThreadedFilter* const master,
                      const DImg& orgImage,
                      const DImg& destImage,
                      int progressBegin = 0,
                      int progressEnd = 100);
    ~WBFilter()                                             override;


    static void autoExposureAdjustement(const DImg* const img, double& black, double& expo);
    static void autoWBAdjustementFromColor(const QColor& tc, double& temperature, double& green);

    static QString FilterIdentifier()
    {
        return QLatin1String("digikam:WhiteBalanceFilter");
    }

    static QString DisplayableName();

    static QList<int> SupportedVersions()
    {
        return QList<int>() << 2;
    }

    static int CurrentVersion()
    {
        return 2;
    }

    void readParameters(const FilterAction& action)         override;

    QString filterIdentifier()                        const override
    {
        return FilterIdentifier();
    }

    FilterAction filterAction()                             override;

protected:

    void filterImage()                                      override;

protected:

    WBContainer m_settings;

private:

    void setLUTv();
    void adjustWhiteBalance(uchar* const data, int width, int height, bool sixteenBit);
    inline unsigned short pixelColor(int colorMult, int index);

    static void setRGBmult(const double& temperature, const double& green, double& mr, double& mg, double& mb);

private:

    class Private;
    Private* const d;
};

} // namespace Digikam

#endif // DIGIKAM_WB_FILTER_H
