#!/usr/bin/python

import os

from resource_management.libraries.script.script import Script
from resource_management.libraries.functions import format
from resource_management.libraries.functions.default import default
from resource_management.libraries.functions.get_not_managed_resources import get_not_managed_resources


config = Script.get_config()
tmp_dir = Script.get_tmp_dir()

# cgroup mount point
cgroup_home="/usr/ndp/data/"
cgroup_root="/usr/ndp/data/cgroup"
resource_isolation_data_dir="/usr/ndp/data/resource-isolation"



# get which cgroup subsystem need to be mounted
open_resource_isolation_service = config['configurations']['resource-isolation-env']['open_resource_isolation_service']
resource_isolation_policy = config['configurations']['resource-isolation-env']['resource_isolation_policy']
cpu_cpuaact_subsystem_mount_same_dir = config['configurations']['resource-isolation-env']['cpu_cpuaact_subsystem_mount_same_dir']
using_cpu_subsys = config['configurations']['resource-isolation-env']['using_cpu_subsys']
using_cpuacct_subsys = config['configurations']['resource-isolation-env']['using_cpuacct_subsys']
just_support_cpu_shares = config['configurations']['resource-isolation-env']['just_support_cpu_shares']
using_memory_subsys = config['configurations']['resource-isolation-env']['using_memory_subsys']
using_cpuset_subsys = config['configurations']['resource-isolation-env']['using_cpuset_subsys']
using_blkio_subsys = config['configurations']['resource-isolation-env']['using_blkio_subsys']
just_support_blkio_shares = config['configurations']['resource-isolation-env']['just_support_blkio_shares']
net_subsystem_mount_same_dir = config['configurations']['resource-isolation-env']['net_subsystem_mount_same_dir']
using_net_cls_subsys = config['configurations']['resource-isolation-env']['using_net_cls_subsys']
using_net_prio_subsys = config['configurations']['resource-isolation-env']['using_net_prio_subsys']

# the total number of resource isolation group 
max_group_num = 10
group_num = int(config['configurations']['resource-isolation-env']['resource_isolation_group_num'])
group_num = min(max_group_num, group_num)


# bash script files
mount_cgroup_subsys = format("{tmp_dir}/mount_cgroup_subsys.sh")
umount_cgroup_subsys = format("{resource_isolation_data_dir}/umount_cgroup_subsys.sh")


# resource isolation service pid file
resource_isolation_pid_path = "/var/run/resource-isolation"
resource_isolation_pid_file = os.path.join(resource_isolation_pid_path, 'resource-isolation.pid')


update_service_pid_script_dir = os.path.join(resource_isolation_data_dir, 'update_service_pid_script')


