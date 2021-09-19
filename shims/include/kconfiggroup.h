#pragma once

#include <QVariant>
#include <QString>

class KConfigGroup
{
public:
    // Implement these:

    QStringList groupList() const;
    KConfigGroup group(const QString &group);
    bool hasGroup(const QString &group) const;
    void deleteGroup();
    QVariant readEntry(const QString& key) const;
    void writeEntry(const QString& key, const QVariant& value);
    bool sync();

    ///////////////////////////////////////////

    template<typename T>
    T readEntry(const QString &key, const T &aDefault) const
    {
        const QVariant value = readEntry(key);
        if(value.isValid()) return value.value<T>();
        return aDefault;
    }
    template<typename T >
    T readEntry(const char *key, const T &aDefault) const
    {
        return readEntry(QString::fromUtf8(key), aDefault);
    }
    QString readEntry(const char *key) const {
        return readEntry(QString::fromUtf8(key), QString{});
    }
    QString readPathEntry(const QString &pKey, const QString &aDefault) const {
        return readEntry(pKey, aDefault);
    }
    QString readPathEntry(const char *key, const QString &aDefault) const {
        return readPathEntry(QString::fromUtf8(key), aDefault);
    }
    template<typename T >
    void writeEntry(const char *key, const T &value)
    {
        writeEntry(QString::fromUtf8(key), value);
    }
    template<typename T >
    void writeEntry(const QString &key, const T &value)
    {
        writeEntry(key, QVariant::fromValue(value));
    }
    void writePathEntry(const QString &pKey, const QString &path) {
        writeEntry(pKey, path);
    }
    void writePathEntry(const char *Key, const QString &path) {
        writeEntry(QString::fromUtf8(Key), path);
    }
};

class KSharedConfig
{
public:
    // Implement these:

    KConfigGroup group(const QString &groupName);

    ///////////////////////////////////////////

    using Ptr = KSharedConfig*;
    static Ptr openConfig() {
        return new KSharedConfig{};
    }
    KConfigGroup group(const char *groupName) {
        return group(QString::fromUtf8(groupName));
    }
};
