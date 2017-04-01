/*
 * Copyright (C) 2016 i.Dark_Templar <darktemplar@dark-templar-archives.net>
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

#ifndef DT_COMMAND_H
#define DT_COMMAND_H

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct dt_command
{
	char *cmd;
	size_t args_count;
	char **args;
} dt_command_t;

/* NOTE: functions dt_validate_command and dt_parse_command require to have at least one full command in buffer. */
int dt_validate_command(const char *buffer);
dt_command_t* dt_parse_command(const char *buffer);
void dt_free_command(dt_command_t *cmd);

#ifdef __cplusplus
}
#endif

#endif /* DT_COMMAND_H */
