
#define     _ZERO_PASS_FIRSTLY    2



extern   unsigned  char   g_uc_trig_angle_a ;  //ȫ�֣�a�ഥ���Ƕ�

extern   unsigned  char   g_uc_trig_angle_b ;  //ȫ�֣�b�ഥ���Ƕ�

extern   unsigned  char   g_uc_trig_angle_c ;  //ȫ�֣�a�ഥ���Ƕ�

extern   unsigned  char   g_uc_trig_angle_instent ;   //ȫ�֣���ǰ��Ҫ���͵Ĵ����Ƕ�

extern   int   Fun_AD_Sample_Channel_Set_Single_Read( stru_Meter_Read * cmd ) ;


/////////////////////////////////////////////////////////////////////////////////
extern int Meter_Read_Single( stru_Meter_Read * cmd ) ;

extern int Meter_Read_Sync( stru_Meter_Read * cmd_a ,
						   stru_Meter_Read * cmd_b ,
						   stru_Meter_Read * cmd_c   ) ;

extern int Meter_Read_Sequence( stru_Meter_Read * cmd_a ,
							   stru_Meter_Read * cmd_b ,
							   stru_Meter_Read * cmd_c   ) ;
////////////////////////////////////////////////

extern int   Fun_Meter_Read_Single_Decode( ) ;
