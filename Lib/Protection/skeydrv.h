#ifndef __SKEYDRV_H
#define __SKEYDRV_H

#ifdef __cplusplus
extern "C" {
#endif

/*
	Smartkey commands
*/
#define MAKE_KEY_CODE(low,high) (((unsigned short)(low)) | (((unsigned short)(high)) << 8))

#define SCRAMBLING_MODE		's'
#define READING_MODE		'r'
#define WRITING_MODE		'w'
#define FIXING_MODE		'f'
#define LOCATING_MODE		'l'
#define COMPARING_MODE		'c'
#define PROGRAMMING_MODE	'p'
#define MODEL_READING_MODE	'm'
#define ENCRYPTING_MODE		'e'
#define BLOCK_READING_MODE	MAKE_KEY_CODE('b','r')
#define BLOCK_WRITING_MODE	MAKE_KEY_CODE('b','w')

/*
	Smartkey NEW commands
*/
#define SERIAL_NUMBER_READING_MODE 'n'
#define FIX_READING_MODE 'x'
#define EXT_MODEL_READING_MODE 'h'
#define FAIL_COUNTER_READING_MODE 'a'

/*
	Legacy commands
*/
#define DEACTIVATE_ACCESS_MODE	MAKE_KEY_CODE('d','d')
#define ACTIVATE_ACCESS_MODE	MAKE_KEY_CODE('d','a')
#define ANTIHACKER_MODE		't'

/*
	Smartkey models
*/
#define SKEY_NONE	'0'		/* No Smartkey */
#define SKEY_FX		'1'		/* Smartkey mod. FX */
#define SKEY_PR		'2'		/* Smartkey mod. PR */
#define SKEY_EP		'3'		/* Smartkey mod. EP */
#define SKEY_NET_5	'4'		/* Smartkey mod. NET 5 users */
#define SKEY_NET_10	'5'		/* Smartkey mod. NET 10 users */
#define SKEY_NET_25	'6'		/* Smartkey mod. NET 25 users */
#define SKEY_NET_50	'7'		/* Smartkey mod. NET 50 users */
#define SKEY_NET_NL	'8'		/* Smartkey mod. NET no limit */
#define SKEY_SP		'9'		/* Smartkey mod. SP */
#define SKEY_NET	'A'		/* Smartkey mod. NET */
#define SKEY_SB		'B'		/* Smartkey mod. SB */
#define SKEY_WI		'C'		/* Smartkey mod. WI */

/*
	Return codes
*/
#define ST_OK			0	/* No errors */
#define ST_NONE_KEY		-1	/* No Smartkey present */
#define ST_SYNT_ERR		-2	/* Syntax error	*/
#define ST_LABEL_FAILED 	-3	/* Uncorrect label */
#define ST_PW_DATA_FAILED	-4	/* Uncorrect password or data */
#define ST_EXEC_ERROR		-16	/* Max exec reached */
#define ST_HW_FAILURE		-20	/* Smartkey damaged */

/*
	Field length
*/
#define LABEL_LENGTH		16
#define PASSWORD_LENGTH		16
#define DATA_LENGTH		64
#define EXTENDED_DATA_LENGTH	352
#define SCRAMBLE_LENGTH		8

/*
	Communication structure definition
*/

#if defined(WIN32)
#pragma pack(1)
#endif

typedef struct smartkey {
	short lpt;
	short command;
	unsigned char label[LABEL_LENGTH];
	unsigned char password[PASSWORD_LENGTH];
	unsigned char data[DATA_LENGTH];
	short fail_counter;
	short status;
	unsigned char ext_data[EXTENDED_DATA_LENGTH];
} SKEY_DATA;

#if defined(WIN32)
#pragma pack()
#endif

/*
	short msclink(SKEY_DATA* key);
*/
short __cdecl msclink(SKEY_DATA * key);

#ifdef __cplusplus
}
#endif

#endif
