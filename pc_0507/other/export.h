
//***************************************************************************
//========================================================================= 
#define         _ACTRUAL_ADDR_END          9000 

#define         _SIMULATIVE_ADDR_START     10000 

#define         _SIMULATIVE_ADDR_END       20000 


//***************************************************************************
//========================================================================
#define        _READ_TRIG_ANGLE_ALL     0x00	 //������Ƕ�

#define        _READ_TRIG_ANGLE_A       0x01	//��A��Ƕ�

#define        _READ_TRIG_ANGLE_B       0x02	//��B��Ƕ�

#define        _READ_TRIG_ANGLE_C       0x03	//��C��Ƕ�

#define        _SET_TRIG_ANGLE_ALL      0x10	//��������Ƕ�

#define        _SET_TRIG_ANGLE_A        0x11	//����A��Ƕ�

#define        _SET_TRIG_ANGLE_B        0x12	//����B��Ƕ�

#define        _SET_TRIG_ANGLE_C        0x13	//����C��Ƕ�

#define        _TRIG_SYNC               0x20	//���ഥͬʱ��������

#define        _TRIG_A                  0x21	//A�ഥ������

#define        _TRIG_B                  0x22	//B�ഥ������

#define        _TRIG_C                  0x23	//C�ഥ������

#define        _TRIG_SEQU               0x24	//���ഥ˳�򴥷�����

#define        _CONF_DTU                0x70	//����������ֶ�

#define        _TRIG_AD                 0x0F  //�������û�л���


//***************************************************************************
//==========================================================================
#define       _ERROR_CURRENT_LOOP_OK                0x10

#define       _ERROR_API_TIMEOUT                    0x00
//////////////////////////
#define       _ERROR_CURRENT_LOOP_TIMEOUT           0x01 

#define       _ERROR_CURRENT_LOOP_ERROR             0x02 

#define       _ERROR_API_ERROR                      0x03

#define       _MODULE_ADDR_ERROR                    0x04

#define       _CMD_ERROR                            -1

#define       _PROTOCOL_NOT_SET                     0x05 

#define       _OK                                   0x06

//////////////////////////////////////////////////////////////////////////////////////////////////////
//====================================================================================================

typedef  union
{
	unsigned long   ldata ;
	
	unsigned char   ucdata[ 4 ] ;
} Long_Byte ;


typedef  union
{
	unsigned int   idata ;
	
	unsigned char   ucdata[ 2 ] ;
} Int_Byte ;


//////��д�����ǶȽṹ��//////////////////////////////////////////////////////////////////////////////
//====================================================================================================
struct   stru_Set_Angle_Single
{	
	unsigned char   uc_section  ; //ĸ�ߡ��� to outerdoor addr   
	
	unsigned char   uc_mcu_phase_number ;//��
	
	unsigned char   uc_trig_angle ;//��Ƕ�
	
};

struct   stru_Set_Angle_All
{	
	unsigned char   uc_section  ; //ĸ�ߡ��� to outerdoor addr
	
	unsigned char   uc_trig_angle_a ;//A��Ƕ�
	
	unsigned char   uc_trig_angle_b ;//B��Ƕ�
	
	unsigned char   uc_trig_angle_c ;//C��Ƕ�
	
};

struct   stru_Read_Angle
{	
	unsigned char   uc_mcu_cmd ;  //PC-mcu  cmd  PC�����ذ�����
	
	unsigned char   uc_section  ; //ĸ�ߡ��� to outerdoor addr	
	
};

struct   stru_Angle_Data
{
	unsigned char   uc_trig_angle_a ;//A��Ƕȣ�ͬʱҲ�����ݷ�������
	
	unsigned char   uc_trig_angle_b ;//B��Ƕȣ�ͬʱҲ�����ݷ�������
	
	unsigned char   uc_trig_angle_c ;//C��Ƕȣ�ͬʱҲ�����ݷ�������
} ;


////////////////////////////////////////////////////////////////////////////////
extern stru_Angle_Data Set_Angle_Single( stru_Set_Angle_Single * cmd  ) ;

extern stru_Angle_Data Set_Angle_All( stru_Set_Angle_All * cmd  ) ;	

extern stru_Angle_Data Read_Trig_Angle( stru_Read_Angle * cmd  ) ;

/////////////////////////////////////////////////////////////////////////////////



//////���������ݽṹ��//////////////////////////////////////////////////////////////////////////////
//====================================================================================================
struct   stru_Meter_Read
{
	unsigned char   uc_user_cmd ;  //ui cmd  UI�����֣�����A�๦������
	
	Long_Byte       un_module_addr  ;//ģ���ַ
	
	unsigned char   uc_sub_meter_addr ; //�ӱ��ַ
	
	unsigned char   uc_phase_number ; //��λ
	
	unsigned char   uc_station_number ; //վ��
	
	unsigned char   uc_section  ; //ĸ�ߡ��� to outerdoor addr
	
	unsigned char   uc_line_number ;  //�� 
} ;

struct   stru_Meter_Congel
{	
	unsigned char   uc_phase_number ; //��λ
	
	Int_Byte        un_congeal_time ;//����ʱ��
} ;




////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////
extern int Meter_Read_Single( stru_Meter_Read * cmd ) ;

extern int Meter_Read_Sync( stru_Meter_Read * cmd_a ,
						    stru_Meter_Read * cmd_b ,
						    stru_Meter_Read * cmd_c   ) ;

extern int Meter_Read_Sequence( stru_Meter_Read * cmd_a ,
							    stru_Meter_Read * cmd_b ,
						        stru_Meter_Read * cmd_c   ) ;
////////////////////////////////////////////////
extern int Meter_Congel_Single( stru_Meter_Congel * cmd ) ;

extern int Meter_Congel_Sync( stru_Meter_Congel * cmd_a ,
							  stru_Meter_Congel * cmd_b ,
							  stru_Meter_Congel * cmd_c   ) ;

extern int Meter_Congel_Sequence( stru_Meter_Congel * cmd_a ,
								  stru_Meter_Congel * cmd_b ,
							      stru_Meter_Congel * cmd_c   ) ;

////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

/*����ͼ��ʼ��
����һ��Input_Channel_Map�ṹ��
�����Ӧ������Input_Channel�ṹ������
��Input_Channel_Map�ṹ���ڵ�ָ��*p_input_channle��Input_Channel�ṹ�������ַ����
����Fun_Channel_Map_Init( Input_Channel_Map * p )����ʼ������map��
*/


//ͨ������λ�õ���ϸ˵���ṹ�壬��ʼ����������ʱ���ȶ��岢��ʼ�������ܸ����ĸýṹ�壬
//Ȼ�󽫸ýṹ�����ָ�븶��*p_input_channle
//===============================================================
typedef  struct 
{
	unsigned char  uc_phase_number ; //��
	
	unsigned char  uc_line_number  ;//��
	
	unsigned char  uc_section_number ; //��
	
	unsigned char  uc_station_number ; //վ
	
	unsigned char  uc_occupy_line_number ; //ʵ�������ӵ�ͨ��
	
	unsigned char  uc_card_number ; //���ڵ�ad�ɼ�����
	
} Input_Channel ;



//ͨ������ͼ�ṹ�壬*p_input_channleָ��ָ���趨�õ�ͨ��˵���ṹ��,�ýṹ����Ŀ�ɳ����ܸ�������
//===============================================================
typedef  struct
{
	Iput_Channel   *p_input_channle ;
	
	unsigned char  uc_input_channle_number ;
	
} Input_Channel_Map ;



//AD �ɼ����������ýṹ�壬�ɲɼ��������ṩ
//===============================================================
typedef struct _PCI8664_PARA_AD
{
	LONG ADMode; // AD ģʽѡ��(����/���鷽ʽ)
	
	LONG FirstChannel; // ͬ����ͨ����[0, 31]
	
	LONG LastChannel; // ͬ��ĩͨ����[0, 31]��Ҫ��ĩͨ��������ڻ������ͨ��
	
	LONG Frequency; // �ɼ�Ƶ�ʣ���λΪHz
	
	LONG GroupInterval; // ����ʱ�������(��λ��΢��) [1, 419430]
	
	LONG LoopsOfGroup; // ����ѭ������[1, 255]
	
	LONG Gains; // ��������
	
	LONG InputRange; // ģ�����������̷�Χ
	
	LONG TriggerMode; // ����ģʽѡ��
	
	LONG TriggerType; // ��������ѡ��(���ش���/���崥��)
	
	LONG TriggerDir; // ��������ѡ��(����/���򴥷�)
	
	LONG TimeoutForNpt; // �ǿղ�ѯ��ʽ�µĳ�ʱʱ��,��λ��,ȡֵ��ΧΪ[0, 3600]
	
}PCI8664_PARA_AD, *PPCI8664_PARA_AD;




//===============================================================
void    Fun_Card_Number_Init( int  num ) ;//����ϵͳ�ڲɼ������

void    Fun_Line_Number_Init( int  num ) ; //����ϵͳ�ڳ�������Ŀ

void    Fun_AD_Init( int card_number , PPCI8664_PARA_AD * p ) ;//�����û�����Ĳ���AD�ɼ�����ʼ��

void    Fun_AD_Init( int card_number ) ;//����Ĭ�ϵĲ�������ʼ����AD�ɼ���

void    Fun_Channel_Map_Init( Input_Channel_Map * p ) ;//��ʼ�����߶��壬��ʼ���趨����ͨ�����ڵ��ߡ��ࡢ��

void    Fun_Buf_Len_Init( int line_data_deep , int ad_data_deep ) ;//��ʼ��ad�ɼ����ݻ������Ĵ�С����ͨ���������ݻ�������С

void    Fun_Uninstall_Device( ) ;//�ͷų�ʼ����̬���ٵ��ڴ浥Ԫ



