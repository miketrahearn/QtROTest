import QtQuick
import QtQuick.Controls.Basic
import QtQuick.Layouts

import ui
// import prototypeService
// import registry

ApplicationWindow {
    width: 640
    height: 480
    visible: true
    title: qsTr("Hello World")

    SettingsStore {

    }

    Backend {

    }

    ColumnLayout {

        Label {
            text: switch(vehicle.state) {
                    case VehicleReplica.Uninitialized:
                        return "Uninitialized"
                    case VehicleReplica.Default:
                        return "Default"
                    case VehicleReplica.Valid:
                        return "Valid"
                    case VehicleReplica.Suspect:
                        return "Suspect"
                    case VehicleReplica.SignatureMismatch:
                        return "SignatureMismatch"
                  }
        }

        Repeater {
            model: registryModel

            Label {
                required property string sourceName
                required property url sourceUrl
                required property string sourceType

                text: `Name: ${sourceName}, HostUrl: ${sourceUrl}, TypeName: ${sourceType}`
            }
        }
    }

    Node {
        id: directNode

        Component.onCompleted: connectToNode("local:ui_services")
    }

    Node {
        id: registryNode

        registryUrl: "local:ui_services_registry"
    }

    RegistryModel {
        id: registryModel

        // this gives us the node's local "copy of the address book"
        // fetched from the registry on the other end - and updates it
        // whenever it changes.

        node: registryNode
    }

    readonly property alias remoteObjectModel: vehicleServiceInternal.remoteObjectModel

    VehicleServiceReplica {
        id: vehicleServiceInternal
    }

    VehicleReplica {
        id: vehicle

        node: registryNode

        onInitialized: {
            console.log("State:", vehicle.state)
            if(state === VehicleReplica.Valid) {
                console.log("Valid!")

                pushEnabled(true)

                pushVehicleType(VehicleReplica.TRUCK)

                console.log("isValid", isValid)

                vehicle.doTrigger()

                console.log("immediate:", vehicleType, enabled, testPod.bar, testPod.bas)

                // this is an asyc write so it won't change immediately!
                testPod = ({ bar: 1, bas: 2 })
                console.log("synchronous testPod", vehicle.testPod.bar, vehicle.testPod.bas)
            }
        }

        onVehicleTypeChanged: console.log("VehicleType:", vehicle.vehicleType)
        onEnabledChanged: console.log("enabled:", vehicle.enabled)
        onTestPodChanged: console.log("async testPod", vehicle.testPod.bar, vehicle.testPod.bas)
        onTriggered: console.log("triggered")
    }
}
