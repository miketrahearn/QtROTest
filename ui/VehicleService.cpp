#include "VehicleService.h"

VehicleService::VehicleService(QObject *parent)
    : VehicleSimpleSource{parent}
{}

void VehicleService::doTrigger()
{
    emit triggered();
}

#include "moc_VehicleService.cpp"
