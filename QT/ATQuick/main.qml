import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Layouts 1.1
//import QtGraphicalEffects 1.15
import QtQuick.Controls 2.15

ApplicationWindow {
    width: 640
    height: 480
    visible: true
    title: qsTr("Hello World")

    Item{
     id: itemDesc
     property int ph: 24
     property int pw: 24
    // property var tchBttnClr: "white"
     property string tchBttnClr:"#004e66"

    }


    SwipeView {
        id: swipeView
        /*
        anchors.top: parent.top
        anchors.topMargin: mainHeader.height
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        */
        currentIndex: tabBar.currentIndex

        AssetsForm {}

        FavsForm {}

        StatsForm {}

        SettingsForm {}
    }


     footer:  TabBar {
          id: tabBar
          contentHeight: 50
          currentIndex: swipeView.currentIndex

         // contentItem: ListView {
          //       orientation: ListView.Vertical   // <<-- VERTICAL

          TabButton {
              text: qsTr("Assets")

              background: Rectangle {
                  color: tabBar.currentIndex === 0 ? itemDesc.tchBttnClr : "#007ea3"
              }
          }

          TabButton {
              text: qsTr("Favs")

              background: Rectangle {
                  color: tabBar.currentIndex === 1 ? itemDesc.tchBttnClr : "#007ea3"
              }
          }

          TabButton {
              text: qsTr("Stats")

              background: Rectangle {
                  color: tabBar.currentIndex === 2 ? itemDesc.tchBttnClr : "#007ea3"
              }
          }

          TabButton {
              text: qsTr("Settings")

              background: Rectangle {
                  color: tabBar.currentIndex === 3 ? itemDesc.tchBttnClr : "#007ea3"
              }
          }
          //}

      }
}
