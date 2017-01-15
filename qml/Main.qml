import QtQuick 2.0
import QtQml 2.2
import QtQuick.Window 2.2

Rectangle {
    id: mainBox;
    objectName: "MainBox";
    width: 100;
    height: 20;
    property int textWidth: 10;
    property int textHeight: 10;
    property string theOS: Qt.platform.os;
    property int fullWidth: Screen.desktopAvailableWidth;
    property int fullHeight: Screen.desktopAvailableHeight;
    color: "red";
    property string theText: "nothing said";
    function setText (t) {
        console.log("settings text to" +t);
    }

    Rectangle{
        id: middleBox;
        width: childrenRect.width + 10;
        height: childrenRect.height + 10;
        color: "white";
        anchors.fill: mainBox;
        Flickable {
            width: middleBox.width;
            height: middleBox.height;
            contentHeight: middleText.height;
            contentWidth: middleText.width;
            clip: true;
            flickableDirection: Flickable.HorizontalAndVerticalFlick;
            interactive: true; //middleText.width >= middleBox.width || middleText.height >= middleBox.height;
            Text {
                id: middleText;
                anchors {
                    centerIn: middleBox;
                }

                width: mainBox.textWidth;
                height: mainBox.textHeight;
                text: mainBox.theText;

            }
        }
    }

}
