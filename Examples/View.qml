import QtQuick 2.3
import QtQuick.Window 2.0
import QtQuick.Controls 1.2

import Example 1.0

Item {
    property ViewModel viewModel: ViewModel {}

    Button {
        enabled: viewModel.helloCommand.canExecute
        onClicked: viewModel.helloCommand.execute()
    }
}
