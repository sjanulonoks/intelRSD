/**
 * Copyright (c)  2015, Intel Corporation.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *   http://www.apache.org/licenses/LICENSE-2.0
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "libredfish/msg_reg.h"
#include "libjson/json.h"

#define MSG_REG_FILE_NAME	"../MR.json"
#define MSG_REG_DEFINE		"../../../src/include/libredfish/mr_def.h"

char *mr_def_header[] = {
	"/*This is a generated file: DO NOT EDIT!",
	"  Generated by \"util/mrgenfile\"*/",
	"#ifndef __MR_DEF__",
	"#define __MR_DEF__",
	"\n"
};

char *mr_def_tail[] = {
	"\n",
	"#endif"
};

#define RF_PRE_FIX "RF_PRE_FIX_INFO"
#define RF_PRE_VER "RF_PRE_VER_INFO"

void writeFile(FILE *def_file, char **data, int len)
{
	int index  = 0;

	for (index = 0; index < len; index++) {
		if(fwrite(data[index], 1, strlen(data[index]), def_file) == 0)
			return;
		if(fwrite("\n", 1, 1, def_file) == 0)
			return;
	}
}

void write_msg_reg_info(FILE *def_file, struct message_registry *data)
{
	int index  = 0;
	char buf[768] = {0};
	struct mr_message *pmsg = NULL;

	pmsg = data->msg_header;
	while (pmsg) {
		memset(buf, 0, 256);
		sprintf(buf, "#define %s		0x%08X			/* %s*/\n",
				pmsg->msg_sn_str, pmsg->msg_sn, pmsg->desc);
		if(fwrite(buf, 1, strlen(buf), def_file) == 0)
			return;
		pmsg = pmsg->pnext;
	}
}

void write_msg_id(FILE *def_file, struct message_registry *data)
{
	int index = 0;
	char buf[768] = {0};

	memset(buf, 0, 256);
	sprintf(buf, "#define %s		\"%s\"\n", RF_PRE_FIX, data->prefix);
	if(fwrite(buf, 1, strlen(buf), def_file) == 0)
		return;
	sprintf(buf, "#define %s		\"%s\"\n", RF_PRE_VER, data->ver);
	if(fwrite(buf, 1, strlen(buf), def_file) == 0)
		return;
}

int main(int argc, char **argv)
{
	int  ret = 0;
	FILE *msg_reg_def_file = fopen(MSG_REG_DEFINE, "w");

	if (msg_reg_def_file  == NULL)
		return -1;

	ret = msg_reg_init(MSG_REG_FILE_NAME);
	if (ret != RF_SUCCESS) {
		printf("Call msg_reg_init failed.\n");
		return 0;
	}

	struct message_registry *data = rf_get_msg_reg();

	writeFile(msg_reg_def_file, mr_def_header, sizeof(mr_def_header)/sizeof(char *));
	write_msg_reg_info(msg_reg_def_file, data);
	write_msg_id(msg_reg_def_file, data);
	writeFile(msg_reg_def_file, mr_def_tail, sizeof(mr_def_tail)/sizeof(char *));

	fclose(msg_reg_def_file);

	return 0;
}
