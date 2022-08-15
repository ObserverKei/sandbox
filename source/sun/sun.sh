#!/bin/bash

#souece ./material.sh

__fn_sun_license()
{
	if [ `h_sun_self shell_name` == ${0##*/} ]; then
		echo 1
		return
	fi

	echo 0
}

__fn_sun_sleep()
{
	sleep `h_sun_self sleep_time`
}

h_material_self()
{
	case $1 in
		*) echo;;
	esac
}

__fn_sun_search_material()
{
	(:)
}

__fn_sun_radiation_external()
{
	(:)
}

__fn_sun_radiation()
{
	`h_sun_self fn_search_material`
	`h_sun_self fn_radiation_external`
}

__fn_sun_cul_material_quality()
{
	(:)
}

__fn_sun_cul_material_inertia()
{
	(:)
}

__fn_sun_gravity_radiation()
{
	(:)
}

__fn_sun_gravity()
{
	`h_sun_self fn_search_material`
	`h_sun_self fn_cul_material_quality`
	`h_sun_self fn_cul_material_inertia`
	`h_sun_self fn_gravity_radiation`
}

__fn_sun_start()
{
	`h_sun_self fn_sleep`
	`h_sun_self fn_gravity`
	`h_sun_self fn_radiation`
}

__fn_sun_init()
{
	if [ 0 -eq $(`h_sun_self fn_license`) ]; then
		echo 0
		return
	fi
	if [ -n "`h_sun_self init_flag`" ]; then
		echo "$0 init_failed(`h_sun_self init_flag`)." >&2
		exit 1
	fi

	basedir=`pwd`/
	pushd `h_sun_self space_path` > /dev/null 2>&1

	__sun_init_flag="done"

	echo 1
}

h_sun_self()
{
	local __sun_space_path=${basedir}space
	local __sun_core_path=${basedir}sun_core
	local __sun_sleep_time=1
	local __sun_shell_name="sun.sh"

	case $1 in
		init_flag) echo $__sun_init_flag;;
		space_path) echo $__sun_space_path;;
		sleep_time) echo $__sun_sleep_time;;
		shell_name) echo $__sun_shell_name;;

		fn_init) echo __fn_sun_init;;
		fn_sleep) echo __fn_sun_sleep;;
		fn_license) echo __fn_sun_license;;
		fn_start) echo __fn_sun_start;;
		fn_gravity) echo __fn_sun_gravity;;
		fn_radiation) echo __fn_sun_radiation;;
		fn_search_material) echo __fn_sun_search_material;;
		fn_cul_material_quality) echo __fn_sun_cul_material_quality;;
		fn_cul_material_inertia) echo __fn_sun_cul_material_inertia;;
		fn_gravity_radiation) echo __fn_sun_gravity_radiation;;
		fn_radiation_external) echo __fn_sun_radiation_external;;
		fn_*) echo "$0($LINENO): h_sun_self($1) failed" >&2 && echo "exit 1";;
		*) echo "$0($LINENO): h_sun_self($1) failed" >&2;;
	esac
}


[ 0 -ne $(`h_sun_self fn_init`) ] && while :; do `h_sun_self fn_start`; done
