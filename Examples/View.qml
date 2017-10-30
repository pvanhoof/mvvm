import QtQuick 2.3
import QtQuick.Window 2.0
import QtQuick.Controls 1.2

import be.codeminded.mvvm 1.0

import Example 1.0

Item {
    id: container
    property ViewModel viewModel: ViewModel {}

    Connections {
        target: viewModel.asyncHelloCommand
        onExecuteProgressed: {
            progressBar.height = 25
            progressBar.value = value
            progressBar.maximumValue = maximum
        }
        onExecuteFinished: {
            progressBar.height = 0
        }
    }

    ProgressBar {
        id: progressBar
        anchors.top: container.top
        anchors.left: container.left
        anchors.right: container.right
        height: 0
    }

    ListView {
        id: list
        anchors {
            top: progressBar.bottom
            left: parent.left
            right: parent.right
        }
        height: 200
        model: viewModel.objectList
        delegate: Rectangle {
            color: "red"
            height: 20
            width: 30
            Text {
                text: modelData.title
            }
        }
    }

    Button {
        id: syncButton
        text: "Sync command"
        anchors.top: list.bottom
        anchors.left: container.left
        anchors.right: container.right
        height: 20

        enabled: viewModel.helloCommand.canExecute
        onClicked: viewModel.helloCommand.execute()
    }

    Button {
        id: asyncButton
        text: "Async command"
        anchors.top: syncButton.bottom
        anchors.left: container.left
        anchors.right: container.right
        height: 20

        enabled: viewModel.asyncHelloCommand.canExecute
        onClicked: viewModel.asyncHelloCommand.execute()
    }

}
