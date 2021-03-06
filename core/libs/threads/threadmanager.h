/* ============================================================
 *
 * This file is a part of digiKam project
 * https://www.digikam.org
 *
 * Date        : 2010-04-13
 * Description : Thread object scheduling
 *
 * Copyright (C) 2010-2012 by Marcel Wiesweg <marcel dot wiesweg at gmx dot de>
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

#ifndef DIGIKAM_THREAD_MANAGER_H
#define DIGIKAM_THREAD_MANAGER_H

// Qt includes

#include <QObject>
#include <QRunnable>

// Local includes

#include "digikam_export.h"

namespace Digikam
{

class DynamicThread;
class WorkerObject;

class DIGIKAM_EXPORT ThreadManager : public QObject
{
    Q_OBJECT

public:

    static ThreadManager* instance();

    void initialize(WorkerObject* const object);
    void initialize(DynamicThread* const dynamicThread);

public Q_SLOTS:

    void schedule(WorkerObject* object);
    void schedule(QRunnable* runnable);

protected Q_SLOTS:

    void slotDestroyed(QObject* object);

protected:

    explicit ThreadManager();
    ~ThreadManager() override;

private:

    // Disable
    explicit ThreadManager(QObject*)               = delete;
    ThreadManager(const ThreadManager&)            = delete;
    ThreadManager& operator=(const ThreadManager&) = delete;

private:

    friend class ThreadManagerCreator;

    class Private;
    Private* const d;
};

} // namespace Digikam

#endif // DIGIKAM_THREAD_MANAGER_H
