#pragma once

#include <QObject>
#include "rep_cas_qml_ui_merged.h"

class VehicleService : public VehicleSimpleSource
{
    Q_OBJECT
public:
    explicit VehicleService(QObject *parent = nullptr);

public slots:
    void doTrigger() override;

signals:
};
