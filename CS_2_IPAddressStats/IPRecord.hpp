class IPRecord
{
public:
	IPRecord(unsigned int ip) :
		m_ip(ip),
		m_frequency(1)
	{
	}

	unsigned int getIP() { return m_ip; }
	unsigned int getFrequency() { return m_frequency; }

	void setIP(unsigned int ip) { m_ip = ip; }
	void incrementFrequency() { m_frequency++; }

private:
	unsigned int m_ip;
	unsigned int m_frequency;
};