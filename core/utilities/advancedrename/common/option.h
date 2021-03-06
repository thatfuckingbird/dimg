/* ============================================================
 *
 * This file is a part of digiKam project
 * https://www.digikam.org
 *
 * Date        : 2009-08-08
 * Description : an abstract option class
 *
 * Copyright (C) 2009-2012 by Andi Clemens <andi dot clemens at gmail dot com>
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

#ifndef DIGIKAM_OPTION_H
#define DIGIKAM_OPTION_H

// Local includes

#include "rule.h"

namespace Digikam
{

class Option : public Rule
{
    Q_OBJECT

public:

    Option(const QString& name, const QString& description);
    Option(const QString& name, const QString& description, const QString& icon);
    ~Option()                                       override;

protected:

    QString parseOperation(ParseSettings& settings) override = 0;

private:

    // Disable
    Option(QObject*)                 = delete;
    Option(const Option&)            = delete;
    Option& operator=(const Option&) = delete;

private:

    class Private;
    Private* const d;
};

} // namespace Digikam

#endif // DIGIKAM_OPTION_H
