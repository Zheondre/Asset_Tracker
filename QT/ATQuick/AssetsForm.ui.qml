import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.1

//import StatsMdl 1.0
//import fcairsts 1.0
Page {

    id: page
    width: ApplicationWindow.width

    Rectangle {
        //id: AssetsLabel
        height: 45
        color: "#f0f3f4"
        anchors.verticalCenter: children.verticalCenter

        Row {
            id: pg2RowListLabel
            //anchors.verticalCenter: children.verticalCenter
            //Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
            height: parent.height
            Text {
                id: element
                text: qsTr("Name")
                anchors.verticalCenter: parent.verticalCenter
                verticalAlignment: Text.AlignVCenter
                //anchors.verticalCenter: parent.verticalCenter

                //transformOrigin: Item.Center
                Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                //font.pixelSize: 10
                //verticalAlignment: Text.AlignVCenter
                //Layout.leftMargin: 10
                //color: "white"
            }
            Text {
                id: element1
                text: qsTr("Price")
                anchors.left: element.right
                anchors.leftMargin: 8
                anchors.verticalCenter: parent.verticalCenter
                verticalAlignment: Text.AlignVCenter
                //font.pixelSize: 10
                //color: "white"
                //Layout.leftMargin: 60
            }
            Text {
                id: element2
                text: qsTr("Change")
                anchors.left: element1.right
                anchors.leftMargin: 8
                //anchors.leftMargin: 90
                verticalAlignment: Text.AlignVCenter
                anchors.verticalCenter: parent.verticalCenter
                //font.pixelSize: 10
                //color: "white"
                //Layout.leftMargin: 90
            }

            Text {
                id: element3
                text: qsTr("MC")
                anchors.left: element2.right
                anchors.leftMargin: 8
                verticalAlignment: Text.AlignVCenter
                anchors.verticalCenter: parent.verticalCenter
                //font.pixelSize: 10
                //color: "white"
                //Layout.leftMargin: -50
            }

            Text {
                id: element4
                width: 40
                anchors.left: element3.right
                anchors.leftMargin: 10
                text: qsTr("Favs")
                verticalAlignment: Text.AlignVCenter
                anchors.verticalCenter: parent.verticalCenter
                //font.pixelSize: 10
                //color: "white"
                // Layout.rightMargin: 60
            }
        }
    } //end of Label Rectangle

    ListView {

        anchors.top: statsLabel.bottom
        anchors.topMargin: 1

        implicitWidth: parent.width
        implicitHeight: applicationWindow.height - (statsLabel.height + mainHeader.height)
        spacing: 1

        clip: true

        model: StatsModel {
            list: fcStats
        }

        delegate: Rectangle {
            id: lvrec
            //color: model.force ? "Red" : "White"
            color: "white"
            height: 55
            width: applicationWindow.width

            // RowLayout {
            Row {
                id: row
                height: lvrec.height

                Text {
                    width: 100
                    height: parent.height
                    id: nameDisplay
                    text: model.name
                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignLeft
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.left: favCheck.right
                    anchors.leftMargin: -5
                    //color: "white"
                    //font
                }

                // }
                Text {
                    //height: lvrec.height
                    id: priceDisplay
                    text: model.price
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.left: dataLabelrec.right
                    anchors.leftMargin: 5
                    // Layout.leftMargin: -40
                    horizontalAlignment: Text.AlignLeft
                    verticalAlignment: Text.AlignVCenter
                }
                Text {
                    //height: lvrec.height
                    id: changeDisplay
                    text: model.change
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.left: dataLabelrec.right
                    anchors.leftMargin: 5
                    // Layout.leftMargin: -40
                    horizontalAlignment: Text.AlignLeft
                    verticalAlignment: Text.AlignVCenter
                }
                Text {
                    //height: lvrec.height
                    id: mcDisplay
                    text: model.mc
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.left: dataLabelrec.right
                    anchors.leftMargin: 5
                    // Layout.leftMargin: -40
                    horizontalAlignment: Text.AlignLeft
                    verticalAlignment: Text.AlignVCenter
                }
                CheckBox {
                    height: lvrec.height
                    id: faveCheck
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.left: unitDisplay.right
                    anchors.leftMargin: -5
                    // Layout.leftMargin: -10
                    scale: 0.7
                    //onClicked: bl.setForce = checked
                    onClicked: model.force = checked
                    // if check box is checked change row except value  color to yellow
                }
            }
        }
    } //end of List View
}

/*##^##
Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
##^##*/
