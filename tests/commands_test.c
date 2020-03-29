/*
 * Copyright (C) 2016-2020 i.Dark_Templar <darktemplar@dark-templar-archives.net>
 *
 * This file is part of DT Command.
 *
 * DT Command is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * DT Command is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with DT Command.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#include <stdlib.h>
#include <string.h>
#include <dt-command.h>
#include "tests/dt_tests.h"

void print_command(dt_command_t *cmd)
{
	size_t i;

	printf("command: %s\n", cmd->cmd);

	for (i = 0; i < cmd->args_count; ++i)
	{
		if (cmd->args[i] != NULL)
		{
			printf("arg %zu: \"%s\"\n", i+1, cmd->args[i]);
		}
		else
		{
			printf("arg %zu: nil\n", i+1);
		}
	}
}

void print_and_free(dt_command_t *cmd, const char *name)
{
	printf("test: %s\n", name);

	if (cmd != NULL)
	{
		print_command(cmd);
		dt_free_command(cmd);
	}
	else
	{
		printf("result: NULL\n");
	}

	printf("\n");
}

int main(int argc, char **argv)
{
	const char *cmd1 = "cmd()\n";
	const char *cmd2 = "cmd2(4 arg1, 4 arg2, 4 arg3)\n";
	const char *cmd3 = "cmd3(3 arg1, 4 arg2, 4 arg3)\n";
	const char *cmd4 = "cmd4(4 arg1 4 arg2, 4 arg3)\n";
	const char *cmd5 = "cmd5(4 arg1)\n";
	const char *cmd6 = "cmd_6(4 arg1)\n";
	const char *cmd7 = "cmd_7(0)\n";
	const char *cmd8 = "cmd_8(-1)\n";
	const char *cmd9 = "cmd_9(4 arg1, -1, 4 arg3)\n";
	const char *cmd10 = "cmd10(-1 4 arg3)\n";
	const char *cmd11 = "(4 arg1)\n";
	const char *cmd12 = "cmd(4 arg1, 0, -1, 3 arg, 5 arg\"2)\n";
	const char *cmd13 = "cmd(args)\n";
	const char *cmd14 = "cmd(\"args\")\n";
	const char *cmd15 = "(4arg12)\n";

	dt_command_t *cmd1_res;
	dt_command_t *cmd2_res;
	dt_command_t *cmd3_res;
	dt_command_t *cmd4_res;
	dt_command_t *cmd5_res;
	dt_command_t *cmd6_res;
	dt_command_t *cmd7_res;
	dt_command_t *cmd8_res;
	dt_command_t *cmd9_res;
	dt_command_t *cmd10_res;
	dt_command_t *cmd11_res;
	dt_command_t *cmd12_res;
	dt_command_t *cmd13_res;
	dt_command_t *cmd14_res;
	dt_command_t *cmd15_res;

	tests_init();

	(void)argc;
	(void)argv;

	test_compare((cmd1_res  = dt_parse_command(cmd1))  != NULL);
	test_compare((cmd2_res  = dt_parse_command(cmd2))  != NULL);
	test_compare((cmd3_res  = dt_parse_command(cmd3))  == NULL);
	test_compare((cmd4_res  = dt_parse_command(cmd4))  == NULL);
	test_compare((cmd5_res  = dt_parse_command(cmd5))  != NULL);
	test_compare((cmd6_res  = dt_parse_command(cmd6))  != NULL);
	test_compare((cmd7_res  = dt_parse_command(cmd7))  != NULL);
	test_compare((cmd8_res  = dt_parse_command(cmd8))  != NULL);
	test_compare((cmd9_res  = dt_parse_command(cmd9))  != NULL);
	test_compare((cmd10_res = dt_parse_command(cmd10)) == NULL);
	test_compare((cmd11_res = dt_parse_command(cmd11)) == NULL);
	test_compare((cmd12_res = dt_parse_command(cmd12)) != NULL);
	test_compare((cmd13_res = dt_parse_command(cmd13)) == NULL);
	test_compare((cmd14_res = dt_parse_command(cmd14)) == NULL);
	test_compare((cmd15_res = dt_parse_command(cmd15)) == NULL);

	print_and_free(cmd1_res,  "test 1");
	print_and_free(cmd2_res,  "test 2");
	print_and_free(cmd3_res,  "test 3");
	print_and_free(cmd4_res,  "test 4");
	print_and_free(cmd5_res,  "test 5");
	print_and_free(cmd6_res,  "test 6");
	print_and_free(cmd7_res,  "test 7");
	print_and_free(cmd8_res,  "test 8");
	print_and_free(cmd9_res,  "test 9");
	print_and_free(cmd10_res, "test 10");
	print_and_free(cmd11_res, "test 11");
	print_and_free(cmd12_res, "test 12");
	print_and_free(cmd13_res, "test 13");
	print_and_free(cmd14_res, "test 14");
	print_and_free(cmd15_res, "test 15");

	return tests_result();
}
