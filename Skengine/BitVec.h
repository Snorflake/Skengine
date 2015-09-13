#pragma once
#include <Windows.h>
class BitVec
{
public:
	BitVec(DWORD dwNumBits) :
		m_dwNumBits(dwNumBits),
		m_dwNumBytes((dwNumBits + (8 - (dwNumBits % 8))) / 8),
		m_pData(0)
	{
		Init();
	}

	BitVec() :
		m_dwNumBits(0),
		m_dwNumBytes(0),
		m_pData(0)
	{
	}

	~BitVec()
	{
		Destroy();
	}

	bool Init() {
		if (!m_dwNumBits || !m_dwNumBytes)
			return false;

		Resize(m_dwNumBits);

		return true;
	}

	void Destroy() { Free(); }

	void Free() { if (m_pData) delete[] m_pData; }

	BitVec &Resize(DWORD dwNumBits) {
		DWORD dwNumBytes = (dwNumBits + (8 - (dwNumBits % 8))) / 8;
		if (m_dwNumBytes < dwNumBytes) {
			unsigned char *pTemp = new unsigned char[dwNumBytes];
			memcpy(pTemp, m_pData, m_dwNumBytes);
			Free();
			m_dwNumBytes = dwNumBytes;
			m_dwNumBits = dwNumBits;
			m_pData = new unsigned char[m_dwNumBytes];
			memset(m_pData, 0, m_dwNumBytes);
			memcpy(m_pData, pTemp, m_dwNumBytes);
			delete[] pTemp;
			//(dwLength + (8 - (dwLength % 8)))/8
		}
		if (!m_pData) {
			m_pData = new unsigned char[m_dwNumBytes];
			memset(m_pData, 0, m_dwNumBytes);
		}
		return *this;
	}
	bool IsBitSet(DWORD dwBit) const { return (bool)m_pData[(dwBit - (dwBit % 8)) / 8] >> dwBit % 8; }
	void SetBit(DWORD dwBit) { m_pData[(dwBit - (dwBit % 8)) / 8] |= (1 << (dwBit % 8)); }
	void ClearBit(DWORD dwBit) { m_pData[(dwBit - (dwBit % 8)) / 8] &= ~(1 << (dwBit % 8)); }

	operator void*() const  { return m_pData; }

private:
	DWORD m_dwNumBits;
	DWORD m_dwNumBytes;
	unsigned char *m_pData;
};