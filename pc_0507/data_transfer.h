

#define    _ZERO_PASS_FLAG   0x55 //0x99  //�����ʱ���յ��ı�־λ

#define    _ZERO_HANDSHAKE_FLAG   0xAA 

#define    _ZER_PASS_NUMBER_BEFORE_MODULATE    65   //�ɼ����ƻص�����ǰ�ȴ��Ĺ�������


#define    _UP_FRAME_DATA_LEN_BYTE       0x04 


#define    _FAILING_EDGE      true 

#define    _RAISING_EDGE      false 



extern     unsigned char     g_uc_zero_pass_times ;//���յ��Ĺ�������


extern  BYTE            g_uc_send_io_data[ 16 ] ;

extern  BYTE            g_uc_recv_io_data[ 16 ] ;

extern  unsigned char   g_uc_PC_RX_Buf[ 16 ] ; //pc����дָ��������Ŷ�д������ָ��ķ�������


extern  void            Fun_PC_CLK_Init( ) ;

extern  void            Fun_PC_Send_Data( unsigned char * buf , int len ) ;

extern  int             Fun_PC_Recv_Data( int len , unsigned char start_flag ) ;

extern  int   Fun_PC_Recv_Data( unsigned char start_flag ) ;

extern  unsigned char   Fun_Recv_Data_Set( BYTE  * data ) ;


////////////////////////////////////////////////////
extern  int             Fun_PC_Zero_Cap_Firstly( ) ;

extern  int             Fun_PC_Zero_Cap( int zero_pass_number ) ;


/////////////////////////////////////////////////////
extern  int  Fun_PC_Trig_Pulse_Init(  bool   edge_type ) ;

extern  int  Fun_PC_Trig_Pulse(  bool   edge_type ) ;