/* ============================================================
 *
 * This file is a part of kipi-plugins project
 * https://www.digikam.org
 *
 * Date        : 2006-09-24
 * Description : DNG converter plugin action descriptions
 *
 * Copyright (C) 2008-2013 by Gilles Caulier <caulier dot gilles at gmail dot com>
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

#ifndef DIGIKAM_DNG_CONVERTER_ACTIONS_H
#define DIGIKAM_DNG_CONVERTER_ACTIONS_H

// Qt includes

#include <QString>
#include <QImage>
#include <QMetaType>
#include <QUrl>

// Local includes

#include "dngwriter.h"

using namespace Digikam;

namespace DigikamGenericDNGConverterPlugin
{

enum DNGConverterAction
{
    NONE = 0,
    IDENTIFY,
    PROCESS
};

class DNGConverterActionData
{

public:

    DNGConverterActionData()
      : starting(false),
        result  (DNGWriter::PROCESS_COMPLETE),
        action  (NONE)
    {
    }

    bool                starting;
    int                 result;

    QString             destPath;
    QString             message;

    QImage              image;

    QUrl                fileUrl;

    DNGConverterAction  action;
};

}  // namespace DigikamGenericDNGConverterPlugin

Q_DECLARE_METATYPE(DigikamGenericDNGConverterPlugin::DNGConverterActionData)

#endif /// DIGIKAM_DNG_CONVERTER_ACTIONS_H
