import QtQuick 2.3
import QtQuick.Window 2.0
import QtQuick.Controls 1.2

import be.codeminded.mvvm 1.0

import Example 1.0 as A

Window {
    width: 360
    height: 360
    visible: true

    View {
        id: view
        height: 40
        anchors {
            top: parent.top
            left: parent.left
            right: parent.right
        }
    }

    ListView {
        id: listView
        anchors {
            top: view.bottom
            bottom: parent.bottom
            left: parent.left
            right: parent.right
        }

        delegate: Item {
            height: 20
            width: listView.width
            MouseArea {
                anchors.fill: parent
                onClicked: if (modelData.canExecute) modelData.execute()
            }
            Text {
                anchors.fill: parent
                text: modelData.text
                color: modelData.canExecute ? "black" : "grey"
            }
        }

        model: comsModel.commands

        property bool combineCanExecute: false

        CommandListModel {
            id: comsModel

            ListCommand {
                text: "Enable combined"
                command: EmitCommand {
                    onExecutes: { console.warn( "Hello1");
                        listView.combineCanExecute=true; }
                    canExecute: true
                }
            }

            ListCommand {
                text: "Disable combined"
                command: EmitCommand {
                    onExecutes: { console.warn( "Hello2");
                        listView.combineCanExecute=false; }
                    canExecute: true
                }
            }

            ListCommand {
                text: "Combined emit commands"
                command: CompositeCommand {
                    EmitCommand {
                        onExecutes: console.warn( "Emit command 1");
                        canExecute: listView.combineCanExecute
                    }
                    EmitCommand {
                        onExecutes: console.warn( "Emit command 2");
                        canExecute: listView.combineCanExecute
                    }
                }
            }
        }
    }
}
