
"use strict";

let RawRequest = require('./RawRequest.js')
let GetLoadedProgram = require('./GetLoadedProgram.js')
let GetSafetyMode = require('./GetSafetyMode.js')
let GetRobotMode = require('./GetRobotMode.js')
let Load = require('./Load.js')
let Popup = require('./Popup.js')
let IsProgramSaved = require('./IsProgramSaved.js')
let AddToLog = require('./AddToLog.js')
let GetProgramState = require('./GetProgramState.js')
let IsInRemoteControl = require('./IsInRemoteControl.js')
let IsProgramRunning = require('./IsProgramRunning.js')

module.exports = {
  RawRequest: RawRequest,
  GetLoadedProgram: GetLoadedProgram,
  GetSafetyMode: GetSafetyMode,
  GetRobotMode: GetRobotMode,
  Load: Load,
  Popup: Popup,
  IsProgramSaved: IsProgramSaved,
  AddToLog: AddToLog,
  GetProgramState: GetProgramState,
  IsInRemoteControl: IsInRemoteControl,
  IsProgramRunning: IsProgramRunning,
};
