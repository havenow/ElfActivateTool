#include "stdafx.h"
#include "MobileInfo.h"
#include "Tool.hpp"


CMobileInfo::CMobileInfo()
{
	memset(m_strCmdOutput, 0, CMD_OUTPUT_SIZE);
	memset(m_strDeviceID1, 0, 32);
	memset(m_strDeviceID2, 0, 32);
	memset(m_strDeviceID3, 0, 32);
	memset(m_strDeviceID4, 0, 32);
	m_nDevice = 0;
}


CMobileInfo::~CMobileInfo()
{
}

void CMobileInfo::SetCmdOutput(const char* strCmdOutput)
{
	if (NULL != strCmdOutput)
	{
		memcpy(m_strCmdOutput, strCmdOutput, CMD_OUTPUT_SIZE);
	}
}

void CMobileInfo::AnalyseDevice(char* strAdbDevices)
{
	int nDevice = getSubStrCount(strAdbDevices, "device") - 1;
	if (nDevice > 4)
		return;
	m_nDevice = nDevice;
	char strFormat[512] = "\0";
	strcpy(strFormat, "List of devices attached");
	for (int i = 0; i < nDevice; i++)
	{
		strcat(strFormat, "\n%s device");
	}
	strcat(strFormat, "\n\n");
	switch (nDevice)
	{
	case 1:
		sscanf(strAdbDevices, strFormat, m_strDeviceID1);
		break;
	case 2:
		sscanf(strAdbDevices, strFormat, m_strDeviceID1, m_strDeviceID2);
		break;
	case 3:
		sscanf(strAdbDevices, strFormat, m_strDeviceID1, m_strDeviceID2, m_strDeviceID3);
		break;
	case 4:
		sscanf(strAdbDevices, strFormat, m_strDeviceID1, m_strDeviceID2, m_strDeviceID3, m_strDeviceID4);
		break;
	}
}