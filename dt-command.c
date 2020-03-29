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

#include <dt-command.h>

#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>

int dt_validate_command(const char *buffer)
{
	const char *cur;
	int i;
	int field_len;

	if (buffer == NULL)
	{
		return 0;
	}

	cur = buffer;
	i   = 0;

	for (;;)
	{
		if ((!isalnum(*cur)) && ((*cur) != '_'))
		{
			if (((*cur) == '(') && (i != 0))
			{
				break;
			}
			else
			{
				return 0;
			}
		}

		++i;
		++cur;
	}

	++cur;

	if (((*cur) == ')') && ((*(cur+1)) == '\n'))
	{
		return 1;
	}

	for (;;)
	{
		if (isdigit(*cur))
		{
			field_len = 0;

			for ( ; isdigit(*cur); ++cur)
			{
				if (field_len >= (INT_MAX / 10))
				{
					return 0;
				}

				field_len = (field_len * 10) + ((*cur) - '0');
			}

			if (field_len != 0)
			{
				if ((*cur) != ' ')
				{
					return 0;
				}

				++cur;

				for (i = 0; i < field_len; ++i, ++cur)
				{
					if (*cur == 0)
					{
						return 0;
					}
				}
			}
		}
		else if (((*cur) == '-') && ((*(cur+1)) == '1'))
		{
			cur += 2;
		}
		else
		{
			return 0;
		}

		if (((*cur) != ',') || ((*(cur+1)) != ' '))
		{
			break;
		}

		cur += 2;
	}

	if (((*cur) == ')') && ((*(cur+1)) == '\n'))
	{
		return 1;
	}

	return 0;
}

dt_command_t* dt_parse_command(const char *buffer)
{
	const char *cur;
	const char *start;
	dt_command_t *result;
	int i;
	int field_len;
	char *tmp_str;
	char **tmp;

	if (buffer == NULL)
	{
		goto parse_command_error_1;
	}

	result = (dt_command_t*) malloc(sizeof(dt_command_t));
	if (result == NULL)
	{
		goto parse_command_error_1;
	}

	result->cmd        = NULL;
	result->args_count = 0;
	result->args       = NULL;

	cur = buffer;
	i   = 0;

	for (;;)
	{
		if ((!isalnum(*cur)) && ((*cur) != '_'))
		{
			if (((*cur) == '(') && (i != 0))
			{
				break;
			}
			else
			{
				goto parse_command_error_2;
			}
		}

		++i;
		++cur;
	}

	result->cmd = (char*) malloc((i+1)*sizeof(char));
	if (result->cmd == NULL)
	{
		goto parse_command_error_2;
	}

	memcpy(result->cmd, buffer, i);
	result->cmd[i] = 0;

	++cur;

	if (((*cur) == ')') && ((*(cur+1)) == '\n'))
	{
		return result;
	}

	for (;;)
	{
		if (isdigit(*cur))
		{
			field_len = 0;

			for ( ; isdigit(*cur); ++cur)
			{
				if (field_len >= (INT_MAX / 10))
				{
					goto parse_command_error_2;
				}

				field_len = (field_len * 10) + ((*cur) - '0');
			}


			if (field_len != 0)
			{
				if ((*cur) != ' ')
				{
					goto parse_command_error_2;
				}

				++cur;

				start = cur;

				for (i = 0; i < field_len; ++i, ++cur)
				{
					if (*cur == 0)
					{
						goto parse_command_error_2;
					}
				}
			}

			tmp_str = (char*) malloc((field_len+1)*sizeof(char));
			if (tmp_str == NULL)
			{
				goto parse_command_error_2;
			}

			tmp = (char**) realloc(result->args, (result->args_count+1)*sizeof(char*));
			if (tmp == NULL)
			{
				free(tmp_str);
				goto parse_command_error_2;
			}

			result->args = tmp;

			if (field_len != 0)
			{
				memcpy(tmp_str, start, field_len);
			}

			tmp_str[field_len] = 0;
			result->args[result->args_count] = tmp_str;
			++(result->args_count);
		}
		else if (((*cur) == '-') && ((*(cur+1)) == '1'))
		{
			tmp = (char**) realloc(result->args, (result->args_count+1)*sizeof(char*));
			if (tmp == NULL)
			{
				goto parse_command_error_2;
			}

			result->args = tmp;
			result->args[result->args_count] = NULL;
			++(result->args_count);

			cur += 2;
		}
		else
		{
			goto parse_command_error_2;
		}

		if (((*cur) != ',') || ((*(cur+1)) != ' '))
		{
			break;
		}

		cur += 2;
	}

	if (((*cur) == ')') && ((*(cur+1)) == '\n'))
	{
		return result;
	}

parse_command_error_2:
	dt_free_command(result);

parse_command_error_1:
	return NULL;
}

void dt_free_command(dt_command_t *cmd)
{
	size_t i;

	if (cmd != NULL)
	{
		if (cmd->cmd != NULL)
		{
			free(cmd->cmd);
		}

		if (cmd->args != NULL)
		{
			for (i = 0; i < cmd->args_count; ++i)
			{
				if (cmd->args[i] != NULL)
				{
					free(cmd->args[i]);
				}
			}

			free(cmd->args);
		}

		free(cmd);
	}
}
