#pragma once

#include <QObject>
#include <QAbstractListModel>
#include <QRemoteObjectNode>
#include <QtQmlIntegration/qqmlintegration.h>

struct RegistryEntry {
    QString name;
    QRemoteObjectSourceLocationInfo info;
};

class RegistryModel : public QAbstractListModel
{
    Q_OBJECT
    QML_ELEMENT
    Q_PROPERTY(QRemoteObjectNode *node READ node WRITE setNode NOTIFY nodeChanged FINAL)

public:
    explicit RegistryModel(QObject *parent = nullptr);

    enum Roles {
        NameRole = Qt::UserRole + 1,
        UrlRole,
        TypeRole
    };

    QRemoteObjectNode *node() const;

    void setNode(QRemoteObjectNode *node);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QHash<int, QByteArray> roleNames() const override;

signals:
    void nodeChanged();

private:
    void updateList();
    QRemoteObjectNode *m_node = nullptr;
    const QRemoteObjectRegistry *m_registry = nullptr;
    QList<RegistryEntry> m_sources;
    QHash<int, QByteArray> m_roleNames;
};
