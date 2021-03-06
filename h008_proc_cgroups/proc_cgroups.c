/***********************************************
 * module : proc_cgroups
 *
 * Wang Long (wanglong@laoqinren.net)
 **********************************************/
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/cgroup.h>
#include <linux/kallsyms.h>


static int __init proc_cgroups_init(void)
{
	struct cgroup_subsys **sub = (struct cgroup_subsys **)kallsyms_lookup_name("subsys");
	int i;

	printk(KERN_ALERT "[Hello] proc_cgroups \n");
	printk("CGROUP_BUILTIN_SUBSYS_COUNT = %d\n", CGROUP_BUILTIN_SUBSYS_COUNT);
	printk("CGROUP_SUBSYS_COUNT = %d\n\n", CGROUP_SUBSYS_COUNT);
	printk("hierarchy  subsys_id num_cgroups enabled used_id  early_init ctype       name base_cftype == base_cfset->cftype\n");
	for (i = 0; i < CGROUP_SUBSYS_COUNT; i++) {
		struct cgroup_subsys *ss = sub[i];
		if (ss == NULL)
			continue;
		printk("[%d]%d\t\t%d\t%d\t%d\t%d\t%d\t%s\t\t%s\t%s\n", i,
			ss->root->hierarchy_id,
			ss->subsys_id,
			ss->root->number_of_cgroups, !ss->disabled,
			ss->use_id ? 1 : 0,
			ss->early_init, ss->base_cftypes->name, ss->name,
			ss->base_cftypes == ss->base_cftset.cfts ? "equal" : "not equal");
	}

	return 0;
}

static void __exit proc_cgroups_exit(void)
{
	printk(KERN_ALERT "[Goodbye] proc_cgroups\n");
}

module_init(proc_cgroups_init);
module_exit(proc_cgroups_exit);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("datawolf");
