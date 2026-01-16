#include "RegistryModel.h"

RegistryModel::RegistryModel(QObject *parent)
    : QAbstractListModel{parent}
{
    m_roleNames.insert(NameRole, "sourceName");
    m_roleNames.insert(UrlRole, "sourceUrl");
    m_roleNames.insert(TypeRole, "sourceType");
}

QRemoteObjectNode *RegistryModel::node() const
{
    return m_node;
}

void RegistryModel::setNode(QRemoteObjectNode *node)
{
    if (m_node == node)
        return;
    m_node = node;
    emit nodeChanged();

    if (m_registry) {
        disconnect(m_registry, nullptr, this, nullptr);
    }

    m_registry = node->registry(); // Access the underlying registry

    if (m_registry) {
        // Initial population
        updateList();

        // Listen for changes
        connect(m_registry, &QRemoteObjectRegistry::remoteObjectAdded,
                this, &RegistryModel::updateList);
        connect(m_registry, &QRemoteObjectRegistry::remoteObjectRemoved,
                this, &RegistryModel::updateList);
    }
}

int RegistryModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid()) return 0;
    return m_sources.count();
}

QVariant RegistryModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || index.row() >= m_sources.size()) return QVariant();

    const auto &entry = m_sources.at(index.row());

    switch (role) {
    case NameRole:
        return entry.name;
    case UrlRole:
        return entry.info.hostUrl;
    case TypeRole:
        return entry.info.typeName;
    }
    return QVariant();
}

QHash<int, QByteArray> RegistryModel::roleNames() const
{
    return m_roleNames;
}

void RegistryModel::updateList() {
    if (!m_registry) return;

    beginResetModel();
    m_sources.clear();

    // Qt 6: Map Key is the Name, Value is the Info.
    // We iterate the map and flatten it into our list.
    auto map = m_registry->sourceLocations();
    for (auto it = map.constBegin(); it != map.constEnd(); ++it) {
        RegistryEntry entry;
        entry.name = it.key();  // Capture the Key
        entry.info = it.value(); // Capture the Info
        m_sources.append(entry);
    }

    endResetModel();
}
