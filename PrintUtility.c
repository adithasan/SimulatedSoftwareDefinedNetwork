#include "IncludeUtility.h"

// Contains all the print functions

void PrintFlowTableEntry(int entryIndex, FlowTableEntry entry)
{
  char action[MSG_BUF];
  sprintf(action, entry.mActionType == Relay ? "RELAY" : "DROP");
  printf("[%d] (srcIP= %d-%d, dest_IP= %d-%d, action= %s-%d, pri=%d, pktCount=%d)\n", entryIndex, entry.mSrcIPLow, entry.mSrcIPHigh, entry.mDestIPLow, entry.mDestIPHigh, action, entry.mActionValue, entry.mPriority, entry.mPacketCount);
}

void PrintProgramData(ProgramStateData* programStateData)
{
  if (programStateData->mProgramMode == Switch)
  {
    printf("\nSuccessfully created a switch with following parameters: \n");
    printf("Switch ID: sw%d\n", programStateData->mSwitchData.mSwitchID);
    printf("Traffic File Name: %s\n", programStateData->mSwitchData.mTrafficFileName);
    printf("Left Node Number: %d\n", programStateData->mSwitchData.mLeftSwitchNode);
    printf("Right Node Number: %d\n", programStateData->mSwitchData.mRightSwitchNode);
    printf("IP High: %d\n", programStateData->mSwitchData.mIPHigh);
    printf("IP Low: %d\n", programStateData->mSwitchData.mIPLow);

    printf("Port Number: %d\n", programStateData->mSwitchData.mPortNumber);
  }
  else if (programStateData->mProgramMode == Controller)
  {
    printf("\nSuccessfully created a controller with following parameters: \n");
    printf("Number of Switches: %d\n", programStateData->mControllerData.mNumSwitches);
    printf("Port Number: %d\n", programStateData->mControllerData.mPortNumber);
  }
}

void PrintSwitchPacketStats(PacketStatsForSwitch* packetStats)
{
  printf("\nPacket Stats: \n");
  printf("\tReceived:\tADMIT:%d, ACK:%d, ADDRUlE:%d, RELAYIN:%d\n", packetStats->mNumAdmit, packetStats->mNumAck, packetStats->mNumAddRule, packetStats->mNumRelayIn);
  printf("\tTransmitted:\tOPEN:%d, QUERY:%d, RELAYOUT:%d\n", packetStats->mNumOpen, packetStats->mNumQuery, packetStats->mNumRelayOut);
}

void PrintControllerPacketStats(PacketStatsForController* packetStats)
{
  printf("\nPacket Stats: \n");
  printf("\tReceived:\tOPEN:%d, QUERY:%d\n", packetStats->mNumOpen, packetStats->mNumQuery);
  printf("\tTransmitted:\tACK:%d, ADD:%d\n", packetStats->mNumAck, packetStats->mNumAdd);
}

void PrintSwitchInformationForController(ControllerData* controllerData)
{
  printf("\nSwitch Information: \n");
  for (int i = 0; i < controllerData->mNumSwitches; i++)
  {
    if (controllerData->mSwitchData[i].mActive == 1)
    {
      SwitchDataForController switchData = controllerData->mSwitchData[i];
      printf("[sw%d] port1=%d, port2=%d, port3=%d-%d\n", switchData.mSwitchId, switchData.mLeftNode, switchData.mRightNode, switchData.mIPLow, switchData.mIPHigh);
    }
  }
}

void ListForController(ControllerData* controllerData, PacketStatsForController* packetStats)
{
  PrintSwitchInformationForController(controllerData);
  PrintControllerPacketStats(packetStats);
}

void ExitForController(ControllerData* controllerData, PacketStatsForController* packetStats)
{
  ListForController(controllerData, packetStats);
  exit(0);
}

void ListForSwitch(SwitchData* switchData, PacketStatsForSwitch* packetStats)
{
  printf("\nFlow Table: \n");
  for (int i = 0; i < switchData->mNumFlowTablesEntries; i++)
  {
    PrintFlowTableEntry(i, switchData->mFlowTable[i]);
  }
  PrintSwitchPacketStats(packetStats);
}


void ExitForSwitch(SwitchData* switchData, PacketStatsForSwitch* packetStats)
{
  ListForSwitch(switchData, packetStats);
  exit(0);
}