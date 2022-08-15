#!/bin/bash

fn_cat_check_update()
{
	if [ ! -f "$(h_cat_self cat_update_shell_file)" ]; then
		echo 0
		return 0
	fi
	
	echo `du -k $(h_cat_self cat_update_shell_file) | awk '{print $1}'`
}

fn_cat_update()
{
	pushd ${g_cat_cutdir}
	/bin/bash -x `h_cat_self cat_update_shell_file`
	/bin/bash ${g_cat_cutdir}${g_cat_core_name} &
	mv -f `h_cat_self cat_update_shell_file` `h_cat_self cat_update_shell_file`.`date +%Y%m%d_%H%M%S`.bak
	echo "update success"
	exit 0
}

fn_cat_sleep()
{
	sleep `h_cat_self cat_sleep_time`
}

fn_cat_see()
{
	ls > `h_cat_self cat_see_log`
}

h_cat_self()
{
	local __cat_core_path=${g_cat_cutdir}cat_core
	local __cat_space_path=${g_cat_cutdir}space
	local __cat_see_log=$__cat_core_path/sandbox_see.log
	local __cat_update_shell_file=$__cat_core_path/update.sh
	local __cat_sleep_time=1
	
	local __fn_cat_check_update=fn_cat_check_update
	local __fn_cat_update=fn_cat_update
	local __fn_cat_core_start=fn_cat_core_start
	local __fn_cat_sleep=fn_cat_sleep
	local __fn_cat_see=fn_cat_see
	
	case $1 in
		cat_core_path) echo $__cat_core_path;;
		cat_space_path) echo $__cat_space_path;;
		cat_update_shell_file) echo $__cat_update_shell_file;;
		cat_see_log) echo $__cat_see_log;;
		cat_sleep_time) echo $__cat_sleep_time;;
		
		fn_cat_core_start) echo $__fn_cat_core_start;;
		fn_cat_check_update) echo $__fn_cat_check_update;;
		fn_cat_update) echo $__fn_cat_update;;
		fn_cat_sleep) echo $__fn_cat_sleep;;
		fn_cat_see) echo $__fn_cat_see;;
		*) echo ;;
	esac
}

fn_cat_core_start()
{
	`h_cat_self fn_cat_sleep`
	`h_cat_self fn_cat_see`
	[ 0 -ne $(`h_cat_self fn_cat_check_update`) ] && `h_cat_self fn_cat_update`
}

g_cat_cutdir=`pwd`/
g_cat_core_name=cat.sh

mkdir -p `h_cat_self cat_core_path` > /dev/null 2>&1

pushd `h_cat_self cat_space_path` > /dev/null 2>&1


while :; do `h_cat_self fn_cat_core_start`; done
