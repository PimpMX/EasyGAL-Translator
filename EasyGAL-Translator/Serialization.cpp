#include "Serialization.h"

//	String buffer.

ostringstream Buffer;

void JEDEC::Serialize()
{
	//	Comment section start.

	m_FileBuffer.append({ ASCII_CTRL_STX, '\n' });
	m_FileBuffer.append(string("Created by ") + string(EASYGAL_VERSION) + string(1, '\n'));

	//	Comment section end.

	m_FileBuffer.append({ '*', ID_VALUE, ID_PIN });
	m_FileBuffer.append(to_string(m_iNumPins));
	m_FileBuffer.append(1, '\n');

	m_FileBuffer.append({ '*', ID_VALUE, ID_DEFAULT_FUSESTATE_FIELD });
	m_FileBuffer.append(to_string(m_iNumFuses));
	m_FileBuffer.append(1, '\n');

	m_FileBuffer.append("*G0\n");
	m_FileBuffer.append("*F0\n");

	pair<uint32_t, pair<uint32_t, uint32_t>> FuseChecksum;
	FuseChecksum.second.first = m_FileBuffer.size();

	//	Start writing fusestates to file buffer.

	for(uint32_t Index = 0; Index < m_FuseStates.size(); Index++)
	{
		if (Index % FUSE_BLOCKSIZE == false && !BlockContainsData(Index))
		{
			Index += FUSE_BLOCKSIZE - 1;
			continue;
		}
		else if (Index % FUSE_BLOCKSIZE == false)
		{
			if (Index) 
				m_FileBuffer.append("\n");
			
			Buffer << std::setw(4) << std::setfill('0') << Index;
			m_FileBuffer.append(string("*L") + Buffer.str() + " ");
			Buffer = std::ostringstream();
		}
		
		m_FileBuffer.append(1, m_FuseStates[Index] ? '1' : '0');
	}

	FuseChecksum.second.second = m_FileBuffer.size();

	//	Calculate checksum for fuselist.

	for (uint32_t Index = FuseChecksum.second.first; Index < FuseChecksum.second.second; Index++)
		FuseChecksum.first += m_FileBuffer.at(Index);

	//	Write checksum to file buffer.

	Buffer << std::setw(4) << std::setfill('0') << std::hex << std::uppercase << FuseChecksum.first;
	m_FileBuffer.append(string("\n*C") + Buffer.str());
	Buffer = std::ostringstream();

	m_FileBuffer.append("\n");
	m_FileBuffer.append(1, ASCII_CTRL_ETX);

	pair<uint32_t, pair<uint32_t, uint32_t>> FileChecksum;
	FileChecksum.second.first = 0;
	FileChecksum.second.second = m_FileBuffer.size();

	//	Calculate checksum for complete file buffer.

	for (uint32_t Index = FileChecksum.second.first; Index < FileChecksum.second.second; Index++)
		FileChecksum.first += m_FileBuffer.at(Index);

	//	Write file buffer checksum.

	Buffer << std::setw(4) << std::setfill('0') << std::hex << std::uppercase << FileChecksum.first;
	m_FileBuffer.append(Buffer.str());
	Buffer = std::ostringstream();

	//	Output file to disk.

	ofstream File(m_Filename);
	File << m_FileBuffer;
	File.close();
}

/*
*		JEDEC::BlockContainsData checks if a block of fuses contains data which needs to be written,
*		it returns true if it finds a '1' in a block of fuses. The startindex parameter is used as 
*		a block starting point in the fuse state list.
*/

bool JEDEC::BlockContainsData(uint32_t StartIndex)
{
	for (uint32_t Index = StartIndex; Index < StartIndex + FUSE_BLOCKSIZE; Index++)
	{
		if (Index > m_FuseStates.size() - 1)
			return false;
		else if (m_FuseStates[Index])
			return true;
	}
	return false;
}