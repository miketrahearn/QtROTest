#pragma once

#include <QObject>
#include <QQmlEngine>
#include "VehicleService.h"

class Backend : public QObject
{
    QML_ELEMENT
    Q_OBJECT
public:
    explicit Backend(QObject *parent = nullptr);

signals:

private:
    QRemoteObjectHost *m_uiServiceRemoteObjectHost { nullptr };
    QRemoteObjectRegistryHost *m_uiServicesRegistry { nullptr };
    VehicleService *m_vehicleService { nullptr };
};
