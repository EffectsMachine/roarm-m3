void jsonCmdReceiveHandler(){
	int cmdType = jsonCmdReceive["T"].as<int>();
	switch(cmdType){
	// emergency stop.
	case CMD_EMERGENCY_STOP:
												RoArmM3_emergencyStopFlag = true;
												emergencyStopProcessing();
												break;
	case CMD_RESET_EMERGENCY: 
												RoArmM3_emergencyStopFlag = false;
												break;


	// it moves to goal position directly
	// with interpolation.
	case CMD_MOVE_INIT:		RoArmM3_moveInit();break;
	case CMD_SINGLE_JOINT_CTRL: 
												RoArmM3_singleJointAbsCtrl(
												jsonCmdReceive["joint"],
												jsonCmdReceive["rad"],
												jsonCmdReceive["spd"],
												jsonCmdReceive["acc"]
												);break;
	case CMD_JOINTS_RAD_CTRL: 
												RoArmM3_allJointAbsCtrl(
												jsonCmdReceive["base"],
												jsonCmdReceive["shoulder"],
												jsonCmdReceive["elbow"],
												jsonCmdReceive["wrist"],
												jsonCmdReceive["roll"],
												jsonCmdReceive["hand"],
												jsonCmdReceive["spd"],
												jsonCmdReceive["acc"]
												);break;
	case CMD_SINGLE_AXIS_CTRL: 
												RoArmM3_singlePosAbsBesselCtrl(
												jsonCmdReceive["axis"],
												jsonCmdReceive["pos"],
												jsonCmdReceive["spd"]
												);break;
	case CMD_XYZT_GOAL_CTRL: 
												RoArmM3_allPosAbsBesselCtrl(
												jsonCmdReceive["x"],
											  jsonCmdReceive["y"],
											  jsonCmdReceive["z"],
											  jsonCmdReceive["t"],
											  jsonCmdReceive["r"],
											  jsonCmdReceive["g"],
											  jsonCmdReceive["spd"]
											  );break;
	case CMD_XYZT_DIRECT_CTRL:
												RoArmM3_baseCoordinateCtrl(
												jsonCmdReceive["x"],
												jsonCmdReceive["y"],
												jsonCmdReceive["z"],
												jsonCmdReceive["t"],
												jsonCmdReceive["r"],
												jsonCmdReceive["g"]);
												RoArmM3_goalPosMove();
												break;
	case CMD_SERVO_RAD_FEEDBACK:
												RoArmM3_getPosByServoFeedback();
												RoArmM3_infoFeedback();
												break;

	case CMD_EOAT_HAND_CTRL: 
												RoArmM3_handJointCtrlRad(1,
												jsonCmdReceive["cmd"],
												jsonCmdReceive["spd"],
												jsonCmdReceive["acc"]
												);break;
	case CMD_EOAT_GRAB_TORQUE:
												RoArmM3_handTorqueCtrl(
												jsonCmdReceive["tor"]
												);break;

	case CMD_SET_JOINT_PID:
												RoArmM3_setJointPID(
												jsonCmdReceive["joint"],
												jsonCmdReceive["p"],
												jsonCmdReceive["i"]
												);break;
	case CMD_RESET_PID:		RoArmM3_resetPID();break;

	// set a new x-axis.
	case CMD_SET_NEW_X: 	setNewAxisX(
												jsonCmdReceive["xAxisAngle"]
												);break;
	case CMD_DELAY_MILLIS:
												RoArmM3_delayMillis(
												jsonCmdReceive["cmd"]
												);break;
	case CMD_DYNAMIC_ADAPTATION: 
												RoArmM3_dynamicAdaptation(
												jsonCmdReceive["mode"],
												jsonCmdReceive["b"],
												jsonCmdReceive["s"],
												jsonCmdReceive["e"],
												jsonCmdReceive["t"],
												jsonCmdReceive["r"],
												jsonCmdReceive["h"]
												);break;
	case CMD_SWITCH_CTRL: switchCtrl(
												jsonCmdReceive["pwm_a"],
												jsonCmdReceive["pwm_b"]
												);break;
	case CMD_LIGHT_CTRL:	lightCtrl(
												jsonCmdReceive["led"]
												);break;
	case CMD_SWITCH_OFF:  switchEmergencyStop();break;
	case CMD_SINGLE_JOINT_ANGLE:
												RoArmM3_singleJointAngleCtrl(
												jsonCmdReceive["joint"],
												jsonCmdReceive["angle"],
												jsonCmdReceive["spd"],
												jsonCmdReceive["acc"]
												);break;
	case CMD_JOINTS_ANGLE_CTRL:
												RoArmM3_allJointsAngleCtrl(
												jsonCmdReceive["b"],
												jsonCmdReceive["s"],
												jsonCmdReceive["e"],
												jsonCmdReceive["t"],
												jsonCmdReceive["r"],
												jsonCmdReceive["h"],
												jsonCmdReceive["spd"],
												jsonCmdReceive["acc"]
												);break;
// constant ctrl
// m: 0 - angle
//    1 - xyzt
// cmd: 0 - stop
// 		  1 - increase
// 		  2 - decrease
// {"T":123,"m":0,"axis":0,"cmd":0,"spd":0}
	case CMD_CONSTANT_CTRL:
												constantCtrl(
												jsonCmdReceive["m"],
												jsonCmdReceive["axis"],
												jsonCmdReceive["cmd"],
												jsonCmdReceive["spd"]
												);break;




	// mission & steps edit & file edit.
	case CMD_SCAN_FILES:  scanFlashContents();
												break;
	case CMD_CREATE_FILE: createFile(
												jsonCmdReceive["name"],
												jsonCmdReceive["content"]
												);break;
	case CMD_READ_FILE:		readFile(
												jsonCmdReceive["name"]
												);break;
	case CMD_DELETE_FILE: deleteFile(
												jsonCmdReceive["name"]
												);break;
	case CMD_APPEND_LINE:	appendLine(
												jsonCmdReceive["name"],
												jsonCmdReceive["content"]
												);break;
	case CMD_INSERT_LINE: insertLine(
												jsonCmdReceive["name"],
												jsonCmdReceive["lineNum"],
												jsonCmdReceive["content"]
												);break;
	case CMD_REPLACE_LINE:
												replaceLine(
												jsonCmdReceive["name"],
												jsonCmdReceive["lineNum"],
												jsonCmdReceive["content"]
												);break;
	case CMD_READ_LINE:   readSingleLine(
												jsonCmdReceive["name"],
												jsonCmdReceive["lineNum"]
												);break;
	case CMD_DELETE_LINE: deleteSingleLine(
												jsonCmdReceive["name"],
												jsonCmdReceive["lineNum"]
												);break;


	case CMD_TORQUE_CTRL: servoTorqueCtrl(254,
												jsonCmdReceive["cmd"]);
												break;


	case CMD_CREATE_MISSION:
												createMission(
												jsonCmdReceive["name"],
												jsonCmdReceive["intro"]
												);break;
	case CMD_MISSION_CONTENT:
												missionContent(
												jsonCmdReceive["name"]
												);break;
	case CMD_APPEND_STEP_JSON: 
												appendStepJson(
												jsonCmdReceive["name"],
												jsonCmdReceive["step"]
												);break;
	case CMD_APPEND_STEP_FB:
												appendStepFB(
												jsonCmdReceive["name"],
												jsonCmdReceive["spd"]
												);break;
	case CMD_APPEND_DELAY:
												appendDelayCmd(
												jsonCmdReceive["name"],
												jsonCmdReceive["delay"]
												);break;
	case CMD_INSERT_STEP_JSON:
												insertStepJson(
												jsonCmdReceive["name"],
												jsonCmdReceive["stepNum"],
												jsonCmdReceive["step"]
												);break;
	case CMD_INSERT_STEP_FB:
												insertStepFB(
												jsonCmdReceive["name"],
												jsonCmdReceive["stepNum"],
												jsonCmdReceive["spd"]
												);break;
	case CMD_INSERT_DELAY:
												insertDelayCmd(
												jsonCmdReceive["name"],
												jsonCmdReceive["stepNum"],
												jsonCmdReceive["spd"]
												);break;
	case CMD_REPLACE_STEP_JSON:
												replaceStepJson(
												jsonCmdReceive["name"],
												jsonCmdReceive["stepNum"],
												jsonCmdReceive["step"]
												);break;
	case CMD_REPLACE_STEP_FB:
												replaceStepFB(
												jsonCmdReceive["name"],
												jsonCmdReceive["stepNum"],
												jsonCmdReceive["spd"]
												);break;
	case CMD_REPLACE_DELAY:
												replaceDelayCmd(
												jsonCmdReceive["name"],
												jsonCmdReceive["stepNum"],
												jsonCmdReceive["delay"]
												);break;
	case CMD_DELETE_STEP: deleteStep(
												jsonCmdReceive["name"],
												jsonCmdReceive["stepNum"]
												);break;

	case CMD_MOVE_TO_STEP:
												moveToStep(
												jsonCmdReceive["name"],
												jsonCmdReceive["stepNum"]
												);break;
	case CMD_MISSION_PLAY:
												missionPlay(
												jsonCmdReceive["name"],
												jsonCmdReceive["times"]
												);break;



	// esp-now settings.
  case CMD_BROADCAST_FOLLOWER:
  											changeBroadcastMode(
  											jsonCmdReceive["mode"],
  											jsonCmdReceive["mac"]
  											);break;
  case CMD_ESP_NOW_CONFIG:
  											changeEspNowMode(
  											jsonCmdReceive["mode"]
  											);break;
  case CMD_GET_MAC_ADDRESS: 
  											getThisDevMacAddress();
  											break;
  case CMD_ESP_NOW_ADD_FOLLOWER:
  											registerNewFollowerToPeer(
  											jsonCmdReceive["mac"]);break;
  case CMD_ESP_NOW_REMOVE_FOLLOWER:
  											deleteFollower(
  											jsonCmdReceive["mac"]);break;
  case CMD_ESP_NOW_GROUP_CTRL:
  											espNowGroupSend(
  											jsonCmdReceive["dev"],
  											jsonCmdReceive["b"],
  											jsonCmdReceive["s"],
  											jsonCmdReceive["e"],
  											jsonCmdReceive["t"],
  											jsonCmdReceive["r"],
  											jsonCmdReceive["h"],
  											jsonCmdReceive["cmd"],
  											jsonCmdReceive["megs"]
  											);break;
  case CMD_ESP_NOW_SINGLE:
  											espNowSingleDevSend(
  											jsonCmdReceive["mac"],
  											jsonCmdReceive["dev"],
  											jsonCmdReceive["b"],
  											jsonCmdReceive["s"],
  											jsonCmdReceive["e"],
  											jsonCmdReceive["t"],
  											jsonCmdReceive["r"],
  											jsonCmdReceive["h"],
  											jsonCmdReceive["cmd"],
  											jsonCmdReceive["megs"]
  											);break;



	// wifi settings.
	case CMD_WIFI_ON_BOOT: 
												configWifiModeOnBoot(
												jsonCmdReceive["cmd"]
												);break;
	case CMD_SET_AP: 			wifiModeAP(
									 			jsonCmdReceive["ssid"],
									 			jsonCmdReceive["password"]
									 			);break;
	case CMD_SET_STA: 		wifiModeSTA(
												jsonCmdReceive["ssid"],
												jsonCmdReceive["password"]
												);break;
	case CMD_WIFI_APSTA: 	wifiModeAPSTA(
										 	 	jsonCmdReceive["ap_ssid"],
											 	jsonCmdReceive["ap_password"],
											 	jsonCmdReceive["sta_ssid"],
											 	jsonCmdReceive["sta_password"]
											 	);break;
	case CMD_WIFI_INFO: 	wifiStatusFeedback();break;
	case CMD_WIFI_CONFIG_CREATE_BY_STATUS: 
												createWifiConfigFileByStatus();break;
	case CMD_WIFI_CONFIG_CREATE_BY_INPUT: 
												createWifiConfigFileByInput(
												jsonCmdReceive["mode"],
												jsonCmdReceive["ap_ssid"],
												jsonCmdReceive["ap_password"],
												jsonCmdReceive["sta_ssid"],
												jsonCmdReceive["sta_password"]
												);break;
	case CMD_WIFI_STOP: 	wifiStop();break;



	// servo settings.
	case CMD_SET_SERVO_ID:
												changeID(
												jsonCmdReceive["raw"],
												jsonCmdReceive["new"]
												);break;
	case CMD_SET_MIDDLE:  setMiddlePos(
												jsonCmdReceive["id"]
												);break;
	case CMD_SET_SERVO_PID: 
												setServosPID(
												jsonCmdReceive["id"],
												jsonCmdReceive["p"]
												);break;

	// esp-32 dev ctrl.
	case CMD_REBOOT: 			esp_restart();break;
	case CMD_FREE_FLASH_SPACE:
												freeFlashSpace();break;
	case CMD_BOOT_MISSION_INFO:
												missionContent("boot");break;
	case CMD_RESET_BOOT_MISSION:
												deleteFile("boot.mission");break;
												createFile("boot", "these cmds run automatically at boot.");
	case CMD_NVS_CLEAR:		nvs_flash_erase();
												delay(1000);
												nvs_flash_init();
												break;
	case CMD_INFO_PRINT:	configInfoPrint(
												jsonCmdReceive["cmd"]
												);break;
	}
}


void serialCtrl() {
  static String receivedData;

  while (Serial.available() > 0) {
    char receivedChar = Serial.read();
    receivedData += receivedChar;

    // Detect the end of the JSON string based on a specific termination character
    if (receivedChar == '\n') {
      // Now we have received the complete JSON string
      DeserializationError err = deserializeJson(jsonCmdReceive, receivedData);
      if (err == DeserializationError::Ok) {
  			if (InfoPrint == 1) {
  				Serial.println(receivedData);
  			}
        jsonCmdReceiveHandler();
      } else {
        // Handle JSON parsing error here
      }
      // Reset the receivedData for the next JSON string
      receivedData = "";
    }
  }
}