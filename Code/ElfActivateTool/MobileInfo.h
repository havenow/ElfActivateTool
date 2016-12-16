#pragma once
#define  CMD_OUTPUT_SIZE 1024*40
class CMobileInfo
{
public:
	CMobileInfo();
	~CMobileInfo();

	void SetCmdOutput(const char* strCmdOutput);
	void ClearCmdOutput(){ memset(m_strCmdOutput, 0, CMD_OUTPUT_SIZE); };
	void AnalyseDevice(char* strAdbDevices);

	int GetDeviceCount(){ return m_nDevice; };

private:
	char m_strCmdOutput[CMD_OUTPUT_SIZE];
	char m_strDeviceID1[32];
	char m_strDeviceID2[32];
	char m_strDeviceID3[32];
	char m_strDeviceID4[32];
	int m_nDevice;
};

