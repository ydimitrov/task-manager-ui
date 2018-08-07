import QtQuick 2.4
import QtQuick.Window 2.2
import QtQuick.Controls 1.4
import TaskManager 1.0

Window {
	id: root
	visible: true
	width: 650
	height: 480

	TaskManager {
		id: taskmng
	}

	Button {
		text: "Add +1"
		anchors.bottom: parent.bottom
		onClicked: {
			
			taskmng.open(bindingAddress);
			for (var i=0; i < libraryModel.count; i++){
				libraryModel.setProperty(i, "tid", "5.95");
				console.log(libraryModel.get(i).state);
				//libraryModel.append({process: "pulseaudio", tid: "690", user: "0", user_cpu: "0", system_cpu: "0", resident_memory: "6.91796875", state: "S"})
			}
		}
	}

	ListModel {
		id: libraryModel
		ListElement {
			cmd: "pulseaudio"
			tid: "0"
			user: "0"
			system_cpu: "0"
			user_cpu: "0"
			resident_memory: "6.91796875"
			state: "S"
		}
		ListElement {
			cmd: "afm-user-daemon"
			tid: "698"
			user: "0"
			system_cpu: "0"
			user_cpu: "0"
			resident_memory: "0.8046875"
			state: "S"
		}
		ListElement {
			cmd: "afbd-task-manag"
			tid: "702"
			user: "0"
			system_cpu: "1.2962355388560667e-06"
			user_cpu: "1.8517650555086668e-07"
			resident_memory: "4.265625"
			state: "R"
		}
		ListElement {
			cmd: "afbd-windowmana"
			tid: "705"
			user: "0"
			system_cpu: "0"
			user_cpu: "0"
			resident_memory: "4.5078125"
			state: "S"
		}
	}

	onUpdateProcess: {
		var index = findId(tid_);
		libraryModel.set(index, {"cmd": cmd_, "tid": tid_, "user": euid_, "system_cpu": scpu_, 
								 "user_cpu": ucpu_, "resident_memory": resident_memory_, "state": state_});
	}

	onAddProcess: {
		libraryModel.append({"cmd": cmd_, "tid": tid_, "user": euid_, "system_cpu": scpu_, 
							 "user_cpu": ucpu_, "resident_memory": resident_memory_, "state": state_});
	}

	onRemoveProcess: {
		var index = findId(tid_);
		libraryModel.remove(index, 1);
	}

	function findId(tid) {
		for(var i = 0; i < libraryModel.count; i++) {
			var elemId = libraryModel.get(i);
			if(tid == libraryModel.get(i).tid) {
  				return elemId; 
  			}
		}
	}

	TableView {

		width: 600

		TableViewColumn {
			role: "cmd"
			title: "Process"
			width: 150
		}
		TableViewColumn {
			role: "tid"
			title: "ID"
			width: 50
		}
		TableViewColumn {
			role: "user"
			title: "User"
			width: 50
		}
		TableViewColumn {
			role: "system_cpu"
			title: "System %CPU"
			width: 100
		}
		TableViewColumn {
			role: "user_cpu"
			title: "User %CPU"
			width: 100
		}
		TableViewColumn {
			role: "resident_memory"
			title: "Memory"
			width: 100
		}
		TableViewColumn {
			role: "state"
			title: "State"
			width: 50
		}
		model: libraryModel
	}

}
