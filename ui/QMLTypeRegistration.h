#pragma once

#include <QtQml/qqml.h>
#include "rep_cas_qml_ui_merged.h"

struct VehicleForeign
{
    Q_GADGET
    QML_FOREIGN(VehicleReplica)
    QML_NAMED_ELEMENT(VehicleReplica)

    // consider making this uncreatable if we expose through a parent singleton readonly property
    // or making this a singleton in its own right - but if we keep it uncreatable,
    // we can still use acquire() properly in C++
    // QML_UNCREATABLE("Vehicle is a replica and cannot be created directly.")
};

struct TestPodForeign
{
    Q_GADGET
    QML_FOREIGN(TestPod)
    QML_VALUE_TYPE(testPod)
    QML_STRUCTURED_VALUE
};
