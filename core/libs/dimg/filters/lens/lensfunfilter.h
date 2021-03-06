/* ============================================================
 *
 * Date        : 2008-02-10
 * Description : a tool to fix automatically camera lens aberrations
 *
 * Copyright (C) 2008      by Adrian Schroeter <adrian at suse dot de>
 * Copyright (C) 2008-2021 by Gilles Caulier <caulier dot gilles at gmail dot com>
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

#ifndef DIGIKAM_LENS_FUN_FILTER_H
#define DIGIKAM_LENS_FUN_FILTER_H

// Local includes

#include "digikam_config.h"
#include "dimgthreadedfilter.h"
#include "digikam_export.h"

namespace Digikam
{

class DIGIKAM_EXPORT LensFunContainer
{

public:

    explicit LensFunContainer()
      : filterCCA       (true),
        filterVIG       (true),
        filterDST       (true),
        filterGEO       (true),
        cropFactor      (-1.0),
        focalLength     (-1.0),
        aperture        (-1.0),
        subjectDistance (-1.0),
        cameraMake      (QString()),
        cameraModel     (QString()),
        lensModel       (QString())
    {
    };

    ~LensFunContainer()
    {
    };

public:

    bool      filterCCA;       ///< Chromatic Aberration Corrections
    bool      filterVIG;       ///< Vignetting Corrections
    bool      filterDST;       ///< Distortion Corrections
    bool      filterGEO;       ///< Geometry Corrections

    double    cropFactor;
    double    focalLength;
    double    aperture;
    double    subjectDistance;

    QString   cameraMake;
    QString   cameraModel;
    QString   lensModel;
};

// -----------------------------------------------------------------

class DIGIKAM_EXPORT LensFunFilter : public DImgThreadedFilter
{
    Q_OBJECT

public:

    explicit LensFunFilter(QObject* const parent = nullptr);
    explicit LensFunFilter(DImg* const origImage,
                           QObject* const parent,
                           const LensFunContainer& settings);
    ~LensFunFilter()                                       override;

    bool registerSettingsToXmp(MetaEngineData& data) const;
    void readParameters(const FilterAction& action)        override;

    static QString FilterIdentifier()
    {
        return QLatin1String("digikam:LensFunFilter");
    }

    static QString DisplayableName();

    static QList<int> SupportedVersions()
    {
        return QList<int>() << 1 << 2;
    }

    static int CurrentVersion()
    {
        return 2;
    }

    QString filterIdentifier()                       const override
    {
        return FilterIdentifier();
    }

    FilterAction filterAction()                            override;

private:

    void filterImage()                                     override;
    void filterCCAMultithreaded(uint start, uint stop);
    void filterVIGMultithreaded(uint start, uint stop);
    void filterDSTMultithreaded(uint start, uint stop);

private:

    class Private;
    Private* const d;
};

} // namespace Digikam

#endif // DIGIKAM_LENS_FUN_FILTER_H
