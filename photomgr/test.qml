import QtQuick 2.0

Item {
    Column {
        id: column1
        x: 8
        y: 0
        width: 200
        height: 400

        TextEdit {
            id: textEdit1
            width: 80
            height: 20
            text: qsTr("Text Edit")
            font.pixelSize: 12
        }
    }

}

