#include "Backend.h"

#include "rep_cas_qml_ui_merged.h"

Backend::Backend(QObject *parent)
    : QObject{parent}
{
    using namespace Qt::StringLiterals;

    m_vehicleService = new VehicleService(this);

    // let's watch the source properties changing as the replica pokes them
    connect(m_vehicleService, &VehicleService::vehicleTypeChanged, [=] () {
        qDebug() << "VehicleService vehicleTypeChanged" << m_vehicleService->vehicleType();
    });

    connect(m_vehicleService, &VehicleSimpleSource::enabledChanged, [=] () {
        qDebug() << "VehicleService enabledChanged" << m_vehicleService->enabled();
    });

    // Option 1: DIRECT CONNECTION:

    // enable remoting with the name of the repc class - the replica will be already expecting this;
    // there is no need for the replica to specify it.
    // m_uiServiceRemoteObjectHost = new QRemoteObjectHost(u"local:ui_services"_s);
    // m_uiServiceRemoteObjectHost->enableRemoting(m_vehicleService, u"Vehicle"_s);

    // Option 2: COMBINED REGISTRY HOST CONNECTION

    // enable remoting with the registry (as well)
    // Note: that in doing this, the registry is acting as a QRemoteObjectHost
    // at the same time; the "Vehicle" service will be found at the registry's own URL.
    // m_uiServicesRegistry = new QRemoteObjectRegistryHost(QUrl(QStringLiteral("local:ui_services_registry")));
    // m_uiServicesRegistry->enableRemoting(m_vehicleService, "Vehicle");

    // Option 3: (BEST) SPLIT CONCERNS: REGISTRY + HOST CONNECTION

    // We separate the concerns into
    // 1) the registry (QRemoteObjectRegistryHost, not QRemoteObjectRegistry)
    // 2) the QRemoteObjectHost
    // allows the registry to be in a separate process
    // allows services to be killed and restarted without stopping the registry,
    // meaning we can keep the UI going...
    // prevents the registry (process) from going down if a service (process) does down

    m_uiServicesRegistry = new QRemoteObjectRegistryHost(QUrl(QStringLiteral("local:ui_services_registry")));

    // This node holds the actual Source Objects (like VehicleService).
    // It needs TWO URLs:
    //   a. Its own address (where it listens for clients): "local:ui_services"
    //   b. The registry address (where it announces itself): "local:ui_services_registry"
    m_uiServiceRemoteObjectHost = new QRemoteObjectHost(QUrl(QStringLiteral("local:ui_services")),
                                                        QUrl(QStringLiteral("local:ui_services_registry")));

    // The m_uiServiceRemoteObjectHost Node will automatically tell the Registry:
    // "I have 'Vehicle' available at 'local:ui_services'"
    // Note: the name of the service is taken from the REPC class unless otherwise specified
    // which is good because that's how the replica works too. Just omit the second argument!
    // (this limits the instance to a single named instance.
    // ** You cannot have separate named replicas in QML. **I can
    m_uiServiceRemoteObjectHost->enableRemoting(m_vehicleService);
}

#include "moc_Backend.cpp"
