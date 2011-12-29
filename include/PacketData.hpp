#ifndef			PROTOCOLPACKETDATA_H_
# define		PROTOCOLPACKETDATA_H_

# include		"types.h"
# include		<vector>
# include		<algorithm>
# include		<string>

class			PacketData
{
/* ************************************************************************* */
/*                             Attributes                                    */
/* ************************************************************************* */
 private:
  std::vector<DataRawType>	data;
  uint				it;

/* ************************************************************************* */
/*                             Coplien Form                                  */
/* ************************************************************************* */
 public:
  PacketData(void);
  PacketData(DataRawType const * data, ushort size);
  PacketData(PacketData const &);
  PacketData &		operator=(PacketData const &);
  ~PacketData(void);

/* ************************************************************************* */
/*                             Member Functions                              */
/* ************************************************************************* */
 public:
  void			prettyPrint(void) const;

 public:
  DataRawType const *	getData(void) const;
  ushort		getDataSize(void) const;

 public:
  std::string		getNextString(void);
  char			getNextChar(void);
  uchar			getNextUChar(void);
  short			getNextShort(void);
  ushort		getNextUShort(void);
  UInt32		getNextUint32(void);

 public:
  void			addString(char const *, ushort);
  void			addString(std::string const &);
  void			addChar(char);
  void			addUChar(uchar);
  void			addShort(short);
  void			addUShort(ushort);
  void			addUint32(UInt32);
};

#endif			// !PROTOCOLPACKETDATA_H_
