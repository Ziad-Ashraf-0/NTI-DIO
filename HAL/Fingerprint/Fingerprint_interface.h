/*
 * Fingerprint_interface.h
 *
 * Created: 11/4/2023 9:32:18 AM
 *  Author: Ziad
 */ 


#ifndef FINGERPRINT_INTERFACE_H_
#define FINGERPRINT_INTERFACE_H_

typedef enum{
	COMMAND_EXECUTION_COMPLETE												= 0X00,
	ERROR_RECEIVING_DATA_PACKAGE											= 0X01,
	NO_FINGER_ON_SENSOR														= 0X02,
	FAIL_ENROLL_FINGER														= 0X03,
	FAIL_GENERATE_OVER_DISORDERLY_FINGERPRINT_IMAGE							= 0X06,
	FAIL_GENERATE_OVER_CHARACTER_POINT_OVERSMALLNESS_FINGERPRINT_IMAGE		= 0X07,
	FINGER_NOT_MATCH														= 0X08,
	FAIL_FIND_MATCHING_FINGE												= 0X09,
	FAIL_COMBINE_CHARACTER_FILES											= 0X0A,
	ADDRESS_PAGEID_BEYOND_FINGER_LIBRARY									= 0X0B,
	ERROR_READTEMPLATE_FROM_LIBRARY_TEMPLATE_INVALID						= 0X0C,
	ERROR_UPLOAD_TEMPLATE													= 0X0D,
	MODULE_NO_RECEIVE_FOLLOWING_DATA_PACKAGES								= 0X0E,
	ERROR_UPLOAD_IMAGE														= 0X0F,
	FAIL_DELETE_TEMPLATE													= 0X10,
	FAIL_CLEAR_FINGER_LIBRARY												= 0X11,
	WRONG_PASSWORD															= 0X13,
	FAIL_TO_GENERATE_THE_IMAGE_FOR_THE_LAKENESS								= 0X15,
	ERROR_WRITE_FLASH														= 0X18,
	ERROR_NO_DEFINITION														= 0X19,
	INVALID_REGISTER_NUMBER													= 0X1A,
	INCORRECT_CONFIGURATION_REGISTER										= 0X1B,
	WRONG_NOTEPAD_PAGE_NUMBER												= 0X1C,
	FAILED_TO_OPERATE_COMM_PORT												= 0X1D
}Error_FingerPS_t;

typedef enum{
	T_BUFFER_1= 0x01,
	T_BUFFER_2= 0x02
}Template_Buffer_t;


typedef enum{
	BREATHING_LIGHT		= 0x01,
	FLASHING_LIGHT		= 0x02,
	LIGHT_ALWAYS_ON		= 0x03,
	LIGHT_ALWAYS_OFF	= 0x04,
	LIGHT_GRADUALY_ON	= 0x05,
	LIGHT_GRADUALY_OFF	= 0x06
}AuraLightControl_t;

typedef enum{
	RED_COLOR	= 0x01,
	BLUE_COLOR	= 0x02,
	PURPLE_COLOR= 0x03
}AuraColorControl_t;


Error_FingerPS_t FingerPS_Init(void);
Error_FingerPS_t FingerPS_AuraLedControl(AuraLightControl_t l_code, u8 l_speed, AuraColorControl_t l_color, u8 l_count);
Error_FingerPS_t FingerPS_handShake(void);
Error_FingerPS_t FingerPS_genImg(void);
Error_FingerPS_t FingerPS_convertImg2CharFile(Template_Buffer_t bufferID);
Error_FingerPS_t FingerPS_genTemplate(void);
Error_FingerPS_t FingerPS_strTemplate(Template_Buffer_t bufferId, u16 pageId);
Error_FingerPS_t FingerPS_searchFinger(Template_Buffer_t bufferId, u16 startPage, u16 pageNum);





#endif /* FINGERPRINT_INTERFACE_H_ */